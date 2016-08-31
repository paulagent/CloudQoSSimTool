#include "VMSyscallManager.h"

Define_Module (VMSyscallManager);


VMSyscallManager::~VMSyscallManager(){
	
}

void VMSyscallManager::initialize(){

        mControllerPtr = dynamic_cast<VmMsgController*> (this->getParentModule()->getSubmodule("vmMsgController"));

        // Init the super-class
        AbstractSyscallManager::initialize();
}

void VMSyscallManager::finish(){

	// Finish the super-class
    AbstractSyscallManager::finish();
}

void VMSyscallManager::processRequestMessage (icancloud_Message *sm){

	// if the msg comes from the node, the vmID has not setted by the msg controller
	// it will be marked as node, to the hypervisor
	int id;
	id = sm->getUid();
	int operation;

	if (id == -1) throw cRuntimeError("processRequestMessage of VMSyscallManager-> message without id\n");

	operation = sm->getOperation();

	// Msg cames from Network
	if (sm->getArrivalGate() == fromNetGate){

        icancloud_MPI_Message_Base* msg_mpi;
        bool found = false;
        msg_mpi = dynamic_cast<icancloud_MPI_Message_Base*> (sm);

        if (msg_mpi == NULL){
            sendRequestMessage (sm, toAppGates->getGate(sm->getNextModuleIndex()));
        } else {
            for (cModule::SubmoduleIterator i(getParentModule()); !i.end() && !found; i++)
                 {
                     cModule* currentApp = i();

                     if (strcmp(currentApp->getFullName(), "app" ) == 0) // if submod() is in the same vector as this module
                     {

                         if (currentApp->hasPar("myRank")){

                             int currentRank = currentApp->par("myRank");

                             if ((int)msg_mpi->getDestRank() == currentRank){

                                 for (int j = 0; (j < (int)processesRunning.size()) && !found;j++){
                                     if ((*(processesRunning.begin() + j)) -> process->getId() == currentApp->getId()){
                                         sendRequestMessage(sm, toAppGates->getGate((*(processesRunning.begin() + j))->toGateIdx));
                                         found = true;
                                     }
                                 }
                             }
                         }
                     }
                }
        }
	}
	
	// Msg cames from CPU
	else if (sm->getArrivalGate() == fromCPUGate){		
		showErrorMessage ("This module cannot receive request messages from CPU!!!");
	}
	
	
	// Msg cames from Memory
	else if (sm->getArrivalGate() == fromMemoryGate){
			
		sendRequestMessage (sm, toAppGates->getGate(sm->getNextModuleIndex()));
	}	
	
	// Msg cames from applications
	else{
		
		// I/O operation?
		if ((operation == SM_OPEN_FILE)   	 	 	  ||
			(operation == SM_CLOSE_FILE)  	  		  ||
			(operation == SM_READ_FILE)   			  ||
			(operation == SM_WRITE_FILE)  			  ||
			(operation == SM_CREATE_FILE) 	 		  ||
			(operation == SM_DELETE_FILE) 			  ||
			(operation == SM_SET_HBS_TO_REMOTE)		  ||
			(operation == SM_DELETE_USER_FS) 	 		  ||
			(operation == SM_NOTIFY_USER_FS_DELETED) 	  ||
			(operation == SM_NOTIFY_PRELOAD_FINALIZATION)){

				// Remote operation? to NET
				if (sm->getRemoteOperation()){
					sendRequestMessage (sm, toNetGate);
				}
				
				// Local operation? to local FS
				else{
                    sendRequestMessage (sm, toMemoryGate);
				}
		// Set ior, a new vm is being allocated ..
		} else if(operation == SM_SET_IOR){
			icancloud_App_IO_Message* sm_io;

			sm_io = check_and_cast<icancloud_App_IO_Message*>(sm);

			// Dup and send the request to create the vm into the local net manager
			icancloud_App_NET_Message* sm_net;

			sm_net = new icancloud_App_NET_Message();
			sm_net->setUid(sm->getUid());
			sm_net->setPid(sm->getPid());
			sm_net->setOperation(sm->getOperation());
			sm_net->setLocalIP(sm_io->getNfs_destAddress());

			sendRequestMessage (sm_net, toNetGate);

			// Send request to create the ior in the fs
			sm_io->setNfs_destAddress(NULL);
			sendRequestMessage (sm_io, toMemoryGate);

		}
		
		// MPI operation?
		else if ((operation == MPI_SEND) ||
				 (operation == MPI_RECV) ||
				 (operation == MPI_BARRIER_UP)   ||
				 (operation == MPI_BARRIER_DOWN) ||
				 (operation == MPI_BCAST)   ||
				 (operation == MPI_SCATTER) ||
				 (operation == MPI_GATHER)){
			
			sendRequestMessage (sm, toNetGate);
		}
		
		
		// CPU operation?
		else if (operation == SM_CPU_EXEC) {

			sendRequestMessage (sm, toCPUGate);			
		}

		// MEM operation?
		else if ((operation == SM_MEM_ALLOCATE) || (operation == SM_MEM_RELEASE)){

			sendRequestMessage (sm, toMemoryGate);			
		}


		// Net operation?		
		else if ((operation == SM_CREATE_CONNECTION) || (operation == SM_LISTEN_CONNECTION) ||
				(operation == SM_SEND_DATA_NET)){

			sendRequestMessage (sm, toNetGate);			
		}			

		else if ((operation == SM_CHANGE_DISK_STATE) || (operation == SM_CHANGE_CPU_STATE)|| (operation == SM_CHANGE_MEMORY_STATE) || (operation == SM_CHANGE_NET_STATE)){
		    delete(sm);
		}

		// Unknown operation! -> Error!!!
		else
			showErrorMessage ("Unknown operation:%i %s",sm->getOperation(), sm->operationToString().c_str());
	}

}

int VMSyscallManager::createProcess(icancloud_Base* j, int uid){
    cout << "VMSyscallManager::createProcess --->before call linkNewApplication : " <<endl;
    cModule* jobAppModule;
    UserJob* job;

    job = dynamic_cast <UserJob*>(j);

    if (job == NULL) throw cRuntimeError("SyscallManager::createJob, error with dynamic casting. Entry parameter cannot cast to jobBase.\n");

    //get the app previously created
        jobAppModule = check_and_cast <cModule*> (job);
        jobAppModule->changeParentTo(getParentModule());

    //Connect the modules (app created and node selected)
        int newIndexFrom = fromAppGates->newGate("fromApps");
        int newIndexTo = toAppGates->newGate("toApps");

        mControllerPtr->linkNewApplication(jobAppModule, toAppGates->getGate(newIndexTo), fromAppGates->getGate(newIndexFrom));

        processRunning* proc;
        proc = new processRunning();
        proc->process = job;
        proc->uid = uid;
        proc->toGateIdx = newIndexTo;

        processesRunning.push_back(proc);

        return newIndexFrom;

}

void VMSyscallManager::removeProcess(int pId){

        icancloud_Base* job = deleteJobFromStructures(pId);
cout << "VMSyscallManager::removeProcess"<< endl;
        if (job != NULL){
            int position = mControllerPtr->unlinkApplication(job);
            fromAppGates->freeGate(position);
            toAppGates->freeGate(position);
        }

}

void VMSyscallManager::connectToRemoteStorage (vector<string> destinationIPs, string fsType, int localPort, int uId, int pId, string ipFrom, int jobId){
     throw cRuntimeError("VMSyscallManager::connectToRemoteStorage->trying to call this method from somewhere...\n");
}

void VMSyscallManager::createDataStorageListen (int uId, int pId){
    throw cRuntimeError("VMSyscallManager::createDataStorageListen->trying to call this method from somewhere...\n");
}

void VMSyscallManager::deleteUserFSFiles( int uId, int pId){
    throw cRuntimeError("VMSyscallManager::deleteUserFSFiles->trying to call this method from somewhere...\n");
}

void VMSyscallManager::setRemoteFiles (int uId, int pId, int spId, string ipFrom, vector<preload_T*> filesToPreload, vector<fsStructure_T*> fsPaths){
    throw cRuntimeError("VMSyscallManager::setRemoteFiles->trying to call this method from somewhere...\n");

}

void VMSyscallManager::createLocalFiles ( int uId, int pId, int spId, string ipFrom, vector<preload_T*> filesToPreload, vector<fsStructure_T*> fsPaths){
    throw cRuntimeError("VMSyscallManager::createLocalFiles->trying to call this method from somewhere...\n");
}

string VMSyscallManager::getState (){
    return state;
}

void VMSyscallManager::changeState(string newState){
    state = newState;
}

void VMSyscallManager::setManager(icancloud_Base* manager){
    user = check_and_cast<AbstractCloudUser*>(manager);
    mControllerPtr->setId(user->getUserId(), this->getParentModule()->getParentModule()->getId());
}
