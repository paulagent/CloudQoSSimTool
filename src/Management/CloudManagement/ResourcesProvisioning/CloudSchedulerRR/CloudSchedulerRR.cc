//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "CloudSchedulerRR.h"

Define_Module(CloudSchedulerRR);

//-------------------Scheduling metods.------------------------------------



void CloudSchedulerRR::initialize() {

    AbstractCloudManager::initialize();
    minimum_percent_storageNode_free = 0.0;

    maximum_number_of_processes_per_node = par("numberOfVMperNode");
    currentNodeIndex = 0;
    currentNodeType = 0;
}

//-------------------Scheduling metods.------------------------------------

void CloudSchedulerRR::setupScheduler() {

    minimum_percent_storageNode_free =
            par("minimum_percent_storageNode_free").doubleValue();


    AllocationManagement::setupStorageNodes();


}

void CloudSchedulerRR::schedule() {
    //Define ...
    vector<AbstractNode*> selectedNodes;
    vector<VM*> attendedRequest_vms;
    NodeVL* node;
    Machine* machine;
    AbstractRequest* req;
    StorageRequest* req_st;
    RequestVM* req_vm;
    string uid;
    string nodeState;

    bool notEnoughResources;
    bool requestErased;
    int j;

    // Init ..

    notEnoughResources = false;
    requestErased = false;

    req = NULL;
    selectedNodes.clear();
    attendedRequest_vms.clear();
    j = 0;

    // Begin
    // Schedule..
    cout<<endl;
    cout << "------------------------------------------SCHEDULE------------------------------------------"<<endl;
    if (schedulerBlock()) {

        req = getRequestByIndex(j);
        // Start with the vm allocation

        //  while ((j < (numPendingRequests())) && (req != NULL)){
        while ((j < (numPendingRequests()))) {
            // uvic:
            if (req == NULL) {
                cout << "Method[CLOUD_SCHEDULER_RR]: -------> req == NULL"<<endl;
                eraseRequest(req);
                requestErased = true;
            }
            //uvic
              printf("\n Method[CLOUD_SCHEDULER_RR]: ------->numPendingRequests------> %d \n", numPendingRequests());
              printf("\n Method[CLOUD_SCHEDULER_RR]: ------->userid------> %d \n", req->getUid());
              printf("\n Method[CLOUD_SCHEDULER_RR]: ------->REQUEST TYPE: %d \n", req->getOperation());
              printf("\n Method[CLOUD_SCHEDULER_RR]: -------> inside request loop\n");

            req_st = dynamic_cast<StorageRequest*>(req);
            req_vm = dynamic_cast<RequestVM*>(req);

            if (req_st != NULL) {
                cout << "Method[CLOUD_SCHEDULER_RR]: -------> req_st is not NULL!" << endl;
                machine = getNodeByIndex(req_st->getNodeSetId(),
                        req_st->getNodeId(), false);
             //   cout << "Method[CLOUD_SCHEDULER_RR]: ------->Storagenode-----------> "<< machine->getFullName()<<endl;

                node = check_and_cast<NodeVL*>(machine);

                // Analyzes and create the connections vector in req_st depending on the selected fs
                // This method will invoke selectStorageNodes
                //TODO: Return the st_req and analyzes the error at sched
              //  cout << "Method[CLOUD_SCHEDULER_RR]: ------->Storagenode----------->req--------> "<< req->getOperation()<<endl;

                AbstractDCManager::userStorageRequest(req_st, node);
                eraseRequest(req_st);
                //uvic:
                requestErased = true;
                //uvic

            } else if (req_vm != NULL) {
                cout << "Method[CLOUD_SCHEDULER_RR]: -------> req_vm is not NULL!" << endl;
                if (req->getOperation() == REQUEST_START_VM) {
                     printf("\n Method[CLOUD_SCHEDULER_RR]: -------> REQUEST_START_VM\n");
                    notEnoughResources = request_start_vm(req_vm);
                    if (!notEnoughResources) {
                        eraseRequest(req);
                        requestErased = true;
                    }

                }

                else if (req->getOperation() == REQUEST_FREE_RESOURCES) {
                    printf("\n Method[CLOUD_SCHEDULER_RR]: -------> REQUEST_FREE_RESOURCES\n");
                    request_shutdown_vm(req_vm);
                    eraseRequest(req);
                    requestErased = true;
                }

             else if (req->getOperation() == REQUEST_ABANDON_SYSTEM) {
                  printf("\n Method[CLOUD_SCHEDULER_RR]: -------> REQUEST_ABANDON_SYSTEM\n");
                // To perform management operations..
                AbstractUser* user;
                AbstractCloudUser* cl_user;

                user = getUserById(req->getUid());

                cl_user = check_and_cast<AbstractCloudUser*>(user);
                cl_user->deleteAllVMs();
                user->callFinish();
                deleteUser(req->getUid());
                eraseRequest(req);
                requestErased = true;
            }

             else if (req->getOperation() == REQUEST_UNFREEZE_VM) {
                 printf("\n Method[CLOUD_SCHEDULER_RR]: -------> REQUEST_UNFREEZE_VM\n");
                 notEnoughResources = request_unfreez_vm(req_vm);
                 if (!notEnoughResources) {
                     eraseRequest(req);
                     requestErased = true;
                 }

             }
             else if (req->getOperation() == REQUEST_START_DOCKER_CONTAINER) {
                             printf("\n Method[CLOUD_SCHEDULER_RR]: -------> REQUEST_START_DOCKER_CONTAINER\n");
                             notEnoughResources = request_start_docker_container(req_vm);
                             if (!notEnoughResources) {
                                 eraseRequest(req);
                                 requestErased = true;
                             }

                         }


             else {
                throw cRuntimeError(
                        "Error: Operation unknown for CloudScheduler__RR\n");
            }
            }
            if (!requestErased) {
                j++;

            }
            requestErased = false;
            req = getRequestByIndex(j);

        }
        cout<<endl;
        cout<< "-----------------------------------------END SCHEDULE --------------------------------------"<<endl;
        schedulerUnblock();
    }

}

AbstractNode* CloudSchedulerRR::selectNode(AbstractRequest* req) {
    if (DEBUG_CLOUD_SCHED) printf("\n Method[SCHEDULER_ROUNDROBIN]: -------> select_nodes\n");

    // Define ..
    AbstractNode* node;
    int vmCPU;
    int vmMemory;
    elementType* el;
    RequestVM* reqVm;
    int positionInitial;
    int setInitial;
    bool found;
    int numProcesses;

    // Cast
    reqVm = dynamic_cast<RequestVM*>(req);
    if (reqVm == NULL)
        throw cRuntimeError(
                "AbstractCloudManager::selectNode->Error : reqVM is NULL. Casting the request\n");

    // Init ..
    node = NULL;
    el = reqVm->getSingleRequestType();
    //     el= reqVm->get
    vmCPU = el->getNumCores();
    vmMemory = el->getMemorySize();
    setInitial = currentNodeType;
    positionInitial = currentNodeIndex;
    if (DEBUG_CLOUD_SCHED) printf("\n Method[SCHEDULER_ROUNDROBIN]:currentNodeIndex :  ------->   %d \n", currentNodeIndex);

    found = false;

    // Begin ..

    // select the node

    //       positionInitial = currentNodeIndex;
    while (!found) {  // it continues until found is FALSE
                      //DANGER: INFINITE LOOP
         if (DEBUG_CLOUD_SCHED) printf("\n Method[SCHEDULER_ROUNDROBIN]:In Searching Loop \n");



         positionInitial = currentNodeIndex;
        //    if (setInitial)
      //      printf("\n Method[SCHEDULER_ROUNDROBIN]: setInitial------>%d \n", setInitial);

     //         printf("\n Method[SCHEDULER_ROUNDROBIN]: positionInitial------>%d \n", positionInitial);

        node = getNodeByIndex(setInitial, positionInitial);

          printf("\n Method[SCHEDULER_ROUNDROBIN]: After getNodeByIndex: ------>%s \n", node->getFullName());
          printf("\n Method[SCHEDULER_ROUNDROBIN]: Free Memory: ------>%f \n", node->getFreeMemory());
          printf("\n Method[SCHEDULER_ROUNDROBIN]: vmMemory: ------>%d \n", vmMemory);
          printf("\n Method[SCHEDULER_ROUNDROBIN]: Number of Cores: ------>%d \n", node->getNumCores());
          printf("\n Method[SCHEDULER_ROUNDROBIN]: vmCPU: ------>%d \n", vmCPU);

        if ((node->getFreeMemory() >= vmMemory)
                && (node->getNumCores() >= vmCPU)) {
            //printf("\n Method[SCHEDULER_ROUNDROBIN]: INSIDE IF PART -----> Really assign a node");

            NodeVL* node_vl = check_and_cast<NodeVL*>(node);
            numProcesses = node_vl->getNumOfLinkedVMs();
            if (numProcesses < maximum_number_of_processes_per_node) {
                node = check_and_cast<Node*>(node_vl);
                found = true;
            }


        }

        currentNodeIndex++;
       //   printf("\n Method[SCHEDULER_ROUNDROBIN]:getSetSize(setInitial)------>%d \n",getSetSize(setInitial));
            printf("\n Method[SCHEDULER_ROUNDROBIN]: currentNodeIndex 222------>%d \n", currentNodeIndex);


        if ((unsigned int) currentNodeIndex
                > ((unsigned int) getSetSize(setInitial) - 1)) {
            setInitial++;
            currentNodeIndex = 0;
     //      printf("\n Method[SCHEDULER_ROUNDROBIN]:INSIDE IF PART: SetInitial,currentNodeIndex ------>%d, %d \n",setInitial,currentNodeIndex);

            if (setInitial < getMapSize()) {
                currentNodeType = setInitial;
            } else {
                currentNodeType = 0;

            }
        // The algorithm has travel by all the values and it not reach a solution. So, the node is null.
        //  if ((positionInitial == currentNodeIndex) && (currentNodeType == setInitial)){
        if ((positionInitial >= currentNodeIndex) && (!found)) {

           // node= scheduleRR();
         //   NodeVL* node_vl2;
            node=scheduleRR();
            while (node!=NULL && (!found))
            {
                if ((node->getFreeMemory() >= vmMemory)
                                && (node->getNumCores() >= vmCPU)) {
                            printf("\n Method[SCHEDULER_ROUNDROBIN]: INSIDE IF PART -----> Really assign a node");

                            NodeVL* node_vl = check_and_cast<NodeVL*>(node);

                            numProcesses = node_vl->getNumOfLinkedVMs();
                            if (numProcesses < maximum_number_of_processes_per_node) {
                                node = check_and_cast<Node*>(node_vl);
                                found = true;
                            }


                        }
                else
                            {
                                node=scheduleRR();

                            }
            }
            if (node==NULL)
            {
            //   printf( "The algorithm has travel by all the values and it not reach a solution. So, the node is null.");
               found = true;

            }
        }

    }

    if (node!=NULL)
        {cout<<"Method[SCHEDULER_ROUNDROBIN]: selectednode is:------>"      << node->getFullName()<< endl;}
    else {
        printf( "The algorithm has travel by all the values and it not reach a solution. So, the node is null.");
        }
    }
    return node;

}

vector<AbstractNode*> CloudSchedulerRR::selectStorageNodes(
        AbstractRequest* st_req) {

    // if (DEBUG_CLOUD_SCHED) printf("\n Method[SCHEDULER_RR]: -------> selectStorageNode\n");

    // Define ..
    int numNodesFs;
    int i, j;
    vector<int> selected_nodes;
    vector<AbstractNode*> nodes;
    AbstractNode* node;
    int diskCapacity;
    int diskFree;
    StorageRequest* streq;

    // Initialize ..
    selected_nodes.clear();
    nodes.clear();
    streq = dynamic_cast<StorageRequest*>(st_req);
    if (streq == NULL)
        throw cRuntimeError(
                "CloudSchedulerRR::selectStorageNodes ->can not cast to storage request\n");

    // Select the number of nodes depending of the type of filesystem
    if (strcmp(streq->getFsType().c_str(), FS_NFS) == 0) {
        numNodesFs = 1;
    } else if (strcmp(streq->getFsType().c_str(), FS_PFS) == 0) {
        numNodesFs = numberOfPFSRemoteServers;
    }

    if (numNodesFs > getStorageNodesSize())
        throw cRuntimeError(
                "[CloudSchedulerRR::selectStorageNodes] -> Trying to instantiate a file system that requires more disks than nodes.. (actually 1 disk device per node) ..\n");

    // Select the nodes

    i = 0;

    for (j = 0;
            (j < AllocationManagement::getStorageNodesSize())
                    && (i < numNodesFs); j++) {

        node = AllocationManagement::getStorageNode(j);
        diskFree = node->getFreeStorage();
        diskCapacity = node->getStorageCapacity();

        if (diskFree >= (diskCapacity * minimum_percent_storageNode_free)) {
            i++;
            selected_nodes.push_back(j);
            nodes.push_back(node);
        }

    }

    if (i != numNodesFs) {
        nodes.clear();
    }

    // It is needed to update the structures ..
    if (selected_nodes.size() != 0)
        updateVmManagementStructures(selected_nodes, st_req->getPid(),
                st_req->getUid());

    return nodes;

}

vector<AbstractNode*> CloudSchedulerRR::remoteShutdown(AbstractRequest* req) {

    // Define ..
    vector<AbstractNode*> nodes;
    RequestVM* reqVm;

    // Init ..
    nodes.clear();

    // Cast
    reqVm = dynamic_cast<RequestVM*>(req);
    if (reqVm == NULL)
        throw cRuntimeError(
                "AbstractCloudManager::remoteShutdown->Error. Casting the request\n");

    // Search the user entry if exists
    int position;
    position = searchUserVMAllocation(reqVm->getUid());

    // If it exists an entry, it means that the user has remote storage
    if (position != -1)
        nodes = deleteVMfromStorageNodes(position, req->getPid());

    else
        nodes.clear();

    return nodes;

}

void CloudSchedulerRR::freeResources(int uId, int pId,
        AbstractNode* computingNode) {
//void CloudSchedulerRR::freeResources(VM* vm, AbstractNode* computingNode){

}

void CloudSchedulerRR::printEnergyValues() {



}

void CloudSchedulerRR::finalizeScheduler() {
    // Define ..

   // ostringstream data;
  //  ostringstream file;



}

int CloudSchedulerRR::selectNodeSet(string setName, int vmcpu, int vmmemory) {

    if (DEBUG_CLOUD_SCHED)
        printf("\n Method[SCHEDULER_FIFO]: -------> selectNodeSet\n");

    int bestFit;
    int acumCPU;
//  int acumVM;
    int i;
    int numTypeSize;
    int numCPUs;

    // Init ..
    bestFit = -1;
    acumCPU = 1024;
    numCPUs = -1;
    numTypeSize = getMapSize();
    //acumVM = set.begin()->getTotalMemory();

    for (i = 0; i < numTypeSize; i++) {
        numCPUs = getSetNumCores(i, false);
        if (((numCPUs - vmcpu) < acumCPU)) { //&& ((set.begin()->getTotalMemory - acumVM )  < vmmemory)){

            bestFit = i;
            acumCPU = numCPUs - vmcpu;
            //vmmemory = bestFit -> getTotalMemory - acumVM;
        }
    }

    return bestFit;

}


AbstractNode* CloudSchedulerRR:: scheduleRR(){
    int    j = 0;
     // vector<RunningVM*> runVM= AbstractCloudManager::runVM;
     printf("\n\n\n\n Method[CLOUD_SCHEDULER_RR::scheduleRR()]: -------> Before our loop\n");
                      // uvic add
                      cout << "Method[CLOUD_SCHEDULER_RR::scheduleRR()]: while loop" << AbstractCloudManager::runVM.size()<<endl;
                      while (j < int(AbstractCloudManager::runVM.size()) && AbstractCloudManager::runVM.size() !=0 ) {
                          clock_t t = clock(); // we are not sure about current time

                            printf("\n Method[CLOUD_SCHEDULER_RR::scheduleRR()]:NO_Runiing_VM -------> %ld \n", runVM.size());

                          RunningVM* vm;
                          vm = AbstractCloudManager::runVM.at(j);
                          if (t >= vm->end_time)   // we need to shutdown vm
                                  {

                              printf("\n Method[CLOUD_SCHEDULER_RR ::scheduleRR()]: -------> t is greater than  vm end_time, we need to shut down vm\n");

                              // make new request
                              AbstractRequest* new_req;
                              RequestVM* new_req_vm = new RequestVM();

                              string a = vm->vm->getFullName();
                              string delimeter = ":";
                              string token = a.substr(0, a.find(delimeter));
                              new_req_vm->setNewSelection(token.c_str(), 1);
                              new_req_vm->setPid(vm->vm->getPid());
                              new_req_vm->setUid(vm->userID);
                              new_req_vm->setFreezedVM(vm->vm);
                              new_req_vm->set_is_freezed(true);

                              // add new request to temp queue

                              new_req = dynamic_cast<AbstractRequest*>(new_req_vm);
                              new_req->setOperation(REQUEST_UNFREEZE_VM);

                              RequestsManagement::userSendRequest(new_req);

                              // Freezing VM by unlink all resources

                              AbstractNode* node;
                              node=vm->hostNodeVL;
                              cout << "hostNode----->" << vm->hostNodeVL->getFullName() << endl;;

                              AbstractCloudManager::unlinkVM(vm->hostNodeVL,vm->vm,false);

                              runVM.erase(runVM.begin() + j);
                              cout <<"CloudSchedulerRR:: scheduleRR()---->After Free Resources" << endl;


                              return node;
                          } else {
                              ++j;

                          }
                      }

                      printf("\n Method[CLOUD_SCHEDULER_RR]: -------> After our loop\n");
                      return NULL;
}

