#include "CPU_Intensive.h"
#define INPUT_FILE "/input.dat"
#define OUTPUT_FILE "/output.dat"
#define MAX_FILE_SIZE 2000000000

Define_Module(CPU_Intensive);

CPU_Intensive::~CPU_Intensive(){
}


void CPU_Intensive::initialize(){

	std::ostringstream osStream;
    timeoutEvent = NULL;
    timeout = 1.0;

	// Set the moduleIdName
	osStream << "CPU_Intensive." << getId();
	moduleIdName = osStream.str();

	// Init the super-class
	UserJob::initialize();

	// App Module parameters
	startDelay = par ("startDelay");
	inputSizeMB  = par ("inputSize");
	outputSizeMB  = par ("outputSize");
	MIs  = par ("MIs");

    iterations  = par ("iterations");
    currentIteration = 1;

	// Service times
	total_service_IO = 0.0;
	total_service_CPU = 0.0;
	startServiceIO = 0.0;
	endServiceIO = 0.0;
	startServiceCPU = 0.0;
	endServiceCPU = 0.0;
	readOffset = writeOffset = 0;

	// Boolean variables
	executeCPU = executeRead = executeWrite = false;

    // Assign names to the results
    jobResults->newJobResultSet("totalIO");
    jobResults->newJobResultSet("totalCPU");
    jobResults->newJobResultSet("Real run-time");
    jobResults->newJobResultSet("Simulation time");

   // TCP_ClientSideService TCP_service = new TCP_ClientSideService();
}

void CPU_Intensive::finish(){
    // Finish the super-class
   UserJob::finish();

}
//
//// create Connection method for TCP
//void CPU_Intensive::createConnection(icancloud_Message *sm){
//
//    clientTCP_Connector newConnection;
//        icancloud_App_NET_Message *sm_net;
//
//
//            // Cast to icancloud_App_NET_Message
//            sm_net = dynamic_cast<icancloud_App_NET_Message *>(sm);
//
//            // Wrong message?
//            if (sm_net == NULL)
//                networkService->showErrorMessage ("[createConnection] Error while casting to icancloud_App_NET_Message!");
//
//            // Attach the message to the corresponding connection
//            newConnection.msg = sm;
//
//            // Create the socket
//            newConnection.socket = new TCPSocket();
//            newConnection.socket->setDataTransferMode(TCP_TRANSFER_OBJECT);
//            newConnection.socket->bind(*(localIP.c_str()) ? IPvXAddress(localIP.c_str()) : IPvXAddress(), -1);
//            //newConnection.socket->setCallbackObject(this);
//            newConnection.socket->setOutputGate(outGate_TCP);
//            newConnection.socket->renewSocket();
//
//            // Add new socket to socketMap
//            socketMap.addSocket (newConnection.socket);
//
//            // Add new connection to vector
//            connections.push_back (newConnection);
//
//            // Debug...
//            if (DEBUG_TCP_Service_Client)
//                networkService->showDebugMessage ("[createConnection] local IP:%s ---> %s:%d. %s",
//                                                    localIP.c_str(),
//                                                    sm_net->getDestinationIP(),
//                                                    sm_net->getDestinationPort(),
//                                                    sm_net->contentsToString(DEBUG_TCP_Service_MSG_Client).c_str());
//
//
//            // Establish Connection
//            newConnection.socket->connect(IPvXAddressResolver().resolve(sm_net->getDestinationIP()), sm_net->getDestinationPort());
//
//}
//// Method to sendPacket to the Server Side
//void CPU_Intensive::sendPacketToServer(icancloud_Message *sm){
//    int index;
//            // Search for the connection...
//            index = searchConnectionByConnId (sm->getConnectionId());
//
//            // Connection not found?
//            if (index == NOT_FOUND)
//                networkService->showErrorMessage ("[sendPacketToServer] Socket not found!");
//
//            else{
//
//                if (DEBUG_TCP_Service_Client)
//                    networkService->showDebugMessage ("[sendPacketToServer] Sending message to %s:%d. %s",
//                                                        connections[index].socket->getRemoteAddress().str().c_str(),
//                                                        connections[index].socket->getRemotePort(),
//                                                        sm->contentsToString(DEBUG_TCP_Service_MSG_Client).c_str());
//
//                connections[index].socket->send(sm);
//            }
//}
//
////This method is used to close the TCP connection on the Client Side
//void CPU_Intensive::closeConnection(icancloud_Message *sm){
//    TCPSocket *socket;
//
//            // Search for the socket
//            socket = socketMap.findSocketFor(sm);
//
//                 if (!socket)
//                    networkService->showErrorMessage ("[closeConnection] Socket not found to send the message: %s\n", sm->contentsToString(true).c_str());
//                 else{
//
//                    if (DEBUG_TCP_Service_Client)
//                        networkService->showDebugMessage ("Closing connection %s:%d. %s",
//                                                    socket->getRemoteAddress().str().c_str(),
//                                                    socket->getRemotePort(),
//                                                    sm->contentsToString(DEBUG_TCP_Service_MSG_Client).c_str());
//                    socket->close();
//
//                    socket = socketMap.removeSocket(socket);
//
//                    delete(socket);
//                 }
//
//                 delete (sm);
//}
//
////This method is used to search the Connection by using the connection ID on the client side
//int CPU_Intensive::searchConnectionByConnId(int connId){
//    int result;
//        bool found;
//        unsigned int i;
//
//            // Init
//            found = false;
//            i = 0;
//
//                // Search for the connection...
//                while ((!found) && (i<connections.size())){
//
//                    if (connections[i].socket->getConnectionId() == connId)
//                        found = true;
//                    else
//                        i++;
//                }
//
//                // Set the result
//                if (found)
//                    result = i;
//                else
//                    result = NOT_FOUND;
//
//        return result;
//}
//
////This function is used to create a new connection on the Server Side
//void CPU_Intensive::newListenConnection(icancloud_Message *sm){
//    TCPSocket *newSocket;
//        icancloud_App_NET_Message *sm_net;
//        serverTCP_Connector newConnection;
//
//
//            // Cast to icancloud_App_NET_Message
//            sm_net = dynamic_cast<icancloud_App_NET_Message *>(sm);
//
//            // Wrong message?
//            if (sm_net == NULL)
//                networkService->showErrorMessage ("[TCP_ServerSideService::newListenConnection] Error while casting to icancloud_App_NET_Message!");
//
//            // Exists a previous connection listening at the same port
//            if (existsConnection(sm_net->getLocalPort()))
//                networkService->showErrorMessage ("[TCP_ServerSideService::newListenConnection] This connection already exists. Port:%d!", sm_net->getLocalPort());
//
//            // Connection entry
//            newConnection.port = sm_net->getLocalPort();
//            newConnection.appIndex = sm_net->getNextModuleIndex();
//            connection.push_back (newConnection);
//
//            // Create a new socket
//            newSocket = new TCPSocket();
//
//            // Listen...
//
//            newSocket->setOutputGate(outGate_TCP);
//            newSocket->setDataTransferMode(TCP_TRANSFER_OBJECT);
//            newSocket->bind(*(localIP.c_str()) ? IPvXAddress(localIP.c_str()) : IPvXAddress(), sm_net->getLocalPort());
//            //newSocket->setCallbackObject(this);
//            newSocket->listen();
//
//            // Debug...
//            if (DEBUG_TCP_Service_Server)
//                networkService->showDebugMessage ("[TCP_ServerSideService] New connection for App[%d] is listening on %s:%d",
//                                                    sm_net->getNextModuleIndex(),
//                                                    localIP.c_str(),
//                                                    sm_net->getLocalPort());
//
//            // Delete msg
//            delete (sm);
//
//}
//
////This method checks for the incoming connection arriving at the server side
//void CPU_Intensive::arrivesIncommingConnection(cMessage *msg){
//    TCPSocket *socket;
//
//            // Search an existing connection...
//            socket = socketMap.findSocketFor(msg);
//
//            // Connection does not exist. Create a new one!
//            if (!socket){
//
//                // Create a new socket
//                socket = new TCPSocket(msg);
//                socket->setOutputGate(outGate_TCP);
//                socket->setDataTransferMode(TCP_TRANSFER_OBJECT);
//                //socket->setCallbackObject(this);
//                socketMap.addSocket(socket);
//
//                if (DEBUG_TCP_Service_Server)
//                networkService->showDebugMessage ("[TCP_ServerSideService] Arrives an incoming connection from %s:%d to local connection %s:%d with connId = %d",
//                                                        socket->getRemoteAddress().str().c_str(),
//                                                        socket->getRemotePort(),
//                                                        socket->getLocalAddress().str().c_str(),
//                                                        socket->getLocalPort(),
//                                                        socket->getConnectionId());
//
//                // Process current operation!
//                socket->processMessage(msg);
//            }
//            else
//                networkService->showErrorMessage ("[TCP_ServerSideService::arrivesIncommingConnection] Connection already exists. ConnId =  %d", socket->getConnectionId());
//
//}
//
//void CPU_Intensive::socketEstablished(int connId, void *yourPtr){
//    int index;
//         icancloud_App_NET_Message *sm_net;
//
//
//            // Search for the connection...
//            index = searchConnectionByConnId (connId);
//
//            // Connection not found?
//            if (index == NOT_FOUND)
//                networkService->showErrorMessage ("[socketEstablished] Socket not found!");
//
//            // All OK!
//            else{
//
//                // Cast
//                sm_net = dynamic_cast<icancloud_App_NET_Message *>(connections[index].msg);
//
//                // Detach
//                connections[index].msg  = NULL;
//
//                // update msg status
//                sm_net->setIsResponse (true);
//                sm_net->setConnectionId (connId);
//                sm_net->setLocalIP (connections[index].socket->getLocalAddress().str().c_str());
//                sm_net->setLocalPort (connections[index].socket->getLocalPort());
//
//                // debug...
//                if (DEBUG_TCP_Service_Client)
//                    networkService->showDebugMessage ("[socketEstablished-client] %s Connection established with %s:%d",
//                                                    localIP.c_str(),
//                                                    connections[index].socket->getRemoteAddress().str().c_str(),
//                                                    connections[index].socket->getRemotePort());
//
//                // Send back the response
//                networkService->sendResponseMessage (sm_net);
//            }
//
//}
//
//void CPU_Intensive::socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent){
//    icancloud_Message *sm;
//        int index;
//
//            // Casting
//            sm = dynamic_cast<icancloud_Message *>(msg);
//
//            // Show debug?
//            if (DEBUG_TCP_Service_Client){
//
//                index = searchConnectionByConnId (connId);
//
//                // Connection not found?
//                if (index == NOT_FOUND)
//                    networkService->showErrorMessage ("[socketDataArrived] Socket not found!");
//
//                networkService->showDebugMessage ("Arrived data from %s:%d. %s",
//                                                connections[index].socket->getRemoteAddress().str().c_str(),
//                                                connections[index].socket->getRemotePort(),
//                                                sm->contentsToString(DEBUG_TCP_Service_MSG_Client).c_str());
//            }
//
//            // Send back the message...
//            networkService->sendResponseMessage (sm);
//
//}
//
//void CPU_Intensive::socketPeerClosed(int connId, void *yourPtr){
//    if (DEBUG_TCP_Service_Client)
//            networkService->showDebugMessage ("Socket Peer closed");
//}
//
//void CPU_Intensive::socketClosed(int connId, void *yourPtr){
//    if (DEBUG_TCP_Service_Client)
//            networkService->showDebugMessage ("Socket closed");
//}
//
//void CPU_Intensive::socketFailure(int connId, void *yourPtr, int code){
//    if (DEBUG_TCP_Service_Client)
//            networkService->showDebugMessage ("Socket Failure");
//
//}


void CPU_Intensive::startExecution (){

    API_OS::startExecution();
    cout << " CPU_Intensive::startExecution()---simulation start>"<<endl;
    Enter_Method_Silent();
    // Create SM_WAIT_TO_EXECUTE message for delaying the execution of this application
    cMessage *waitToExecuteMsg = new cMessage (SM_WAIT_TO_EXECUTE.c_str());
    scheduleAt (simTime()+startDelay, waitToExecuteMsg);
    cout << " CPU_Intensive::startExecution()---self schedule at simTime()+startDelay time>"<<endl;
}

void CPU_Intensive::processSelfMessage (cMessage *msg){

    if (!strcmp (msg->getName(), SM_WAIT_TO_EXECUTE.c_str())){

        // Starting time...
        simStartTime = simTime();
        runStartTime = time (NULL);

        // Init...
        startServiceIO = simTime();

        executeIOrequest (false, true);

    }else

        showErrorMessage ("Unknown self message [%s]", msg->getName());

    delete (msg);
}


void CPU_Intensive::processRequestMessage (icancloud_Message *sm){

}


void CPU_Intensive::processResponseMessage (icancloud_Message *sm){

	icancloud_App_IO_Message *sm_io;
	icancloud_App_CPU_Message *sm_cpu;
	bool isError;	
	std::ostringstream osStream;
    int operation;


		// Init...
        operation = sm->getOperation ();
		sm_io = dynamic_cast<icancloud_App_IO_Message *>(sm);
		sm_cpu = dynamic_cast<icancloud_App_CPU_Message *>(sm);
		isError = false;

		
		// IO Message?
		if (sm_io != NULL){
			
			// Get time!
			endServiceIO = simTime();
			
			// Read response!
			if (operation == SM_READ_FILE){
				// All ok!
				if (sm_io->getResult() == icancloud_OK){
					executeCPU = true;					
					executeWrite = false;
					executeRead = false;
					delete (sm);
				}
				
				// File not found!
				else if (sm_io->getResult() == icancloud_FILE_NOT_FOUND){
					osStream << "File not found!";
					isError = true;
				}		
				
				// File not found!
				else if (sm_io->getResult() == icancloud_DATA_OUT_OF_BOUNDS){					
					executeCPU = true;
				}		
				
				// Unknown result!
				else{
					osStream << "Unknown result value:" << sm_io->getResult();
					isError = true;
				}		
			}
					
			
			// Write response!
			else if (operation == SM_WRITE_FILE){
				// All ok!
				if (sm_io->getResult() == icancloud_OK){
					executeCPU = false;
					executeWrite = false;
					executeRead = true;
					currentIteration++;
					delete (sm);
				}
				
				// File not found!
				else if (sm_io->getResult() == icancloud_FILE_NOT_FOUND){
					osStream << "File not found!";
					isError = true;
				}		
				
				// File not found!
				else if (sm_io->getResult() == icancloud_DISK_FULL){
					osStream << "Disk full!";
					isError = true;
				}		
				
				// Unknown result!
				else{
					osStream << "Unknown result value:" << sm_io->getResult();
					isError = true;
				}			
			}
			
			// Unknown I/O operation
			else{
				osStream << "Unknown received response message";	
				isError = true;
			}			
			
			// Increase total time for I/O
			total_service_IO += (endServiceIO - startServiceIO);				
		}
				
	
		// Response came from CPU system		
		else if (sm_cpu != NULL){
			
			// Get time!
			endServiceCPU = simTime ();
				
			// CPU!
			if (operation == SM_CPU_EXEC){
				executeCPU = false;
				executeWrite = true;
				executeRead = false;
				delete (sm);
			}
			
			// Unknown CPU operation
			else{
				osStream << "Unknown received response message";	
				isError = true;
			}			
			
			// Increase total time for I/O
			total_service_CPU += (endServiceCPU - startServiceCPU);			
		}
		
		// Wrong response message!
		else{
			
			osStream << "Unknown received response message";	
			isError = true;
		}

			// Error?
			if (isError){
				
				showErrorMessage ("Error in response message:%s. %s", 
									osStream.str().c_str(),
									sm_io->contentsToString(true).c_str());
			}
								
			// CPU?
			else if (executeCPU){
					
				// Execute CPU!
				executeCPUrequest ();								
			}
			
			// IO?
			else if ((executeRead) || (executeWrite)){

				if ((executeRead) && (currentIteration > iterations))
					printResults();
				else
					executeIOrequest(executeRead, executeWrite);
			}
				
			// Inconsistency error!		
			else
				showErrorMessage ("Inconsistency error!!!! :%s. %s", 
									osStream.str().c_str(),
									sm->contentsToString(true).c_str());	
} 


void CPU_Intensive::changeState(string newState){

}


void CPU_Intensive::executeIOrequest(bool executeRead, bool executeWrite){

	// Reset timer!
	startServiceIO = simTime();

	// Executes I/O operation
	if (executeRead){
		
		if ((readOffset+(inputSizeMB*MB))>=MAX_FILE_SIZE)
			readOffset = 0;

		if (DEBUG_Application)
			showDebugMessage ("[%d/%d] Executing (Read) Offset:%d; dataSize:%d", currentIteration, iterations, readOffset,  inputSizeMB*MB);
		
		icancloud_request_read (INPUT_FILE, readOffset, inputSizeMB*MB);
		readOffset += (inputSizeMB*MB);


	}
	else{
		
		if ((writeOffset+(outputSizeMB*MB))>=MAX_FILE_SIZE)
			writeOffset = 0;

		if (DEBUG_Application)
			showDebugMessage ("[%d/%d] Executing (Write) Offset:%d; dataSize:%d", currentIteration, iterations, writeOffset,  outputSizeMB*MB);
		
		icancloud_request_write (OUTPUT_FILE, writeOffset, outputSizeMB*MB);
		writeOffset += (outputSizeMB*MB);
	}														
}


void CPU_Intensive::executeCPUrequest(){

	// Debug?
	if (DEBUG_Application)
		showDebugMessage ("[%d/%d] Executing (CPU) MIs:%d", currentIteration, iterations, MIs);

	// Reset timer!	
	startServiceCPU = simTime ();
	icancloud_request_cpu (MIs);
}


void CPU_Intensive::printResults (){

    std::ostringstream osStream;

    //Init..
        simEndTime = simTime();
        runEndTime = time (NULL);

    //Assign values to the results
        osStream <<  total_service_IO.dbl();
        jobResults->setJobResult(0, osStream.str());
        osStream.str("");

        osStream <<  total_service_CPU.dbl();
        jobResults->setJobResult(1, osStream.str());
        osStream.str("");

        osStream <<  difftime (runEndTime,runStartTime);
        jobResults->setJobResult(2, osStream.str());
        osStream.str("");

        osStream << (simEndTime - simStartTime).dbl();
        jobResults->setJobResult(3, osStream.str());

        addResults(jobResults);

    //Send results list to the cloudManager
        userPtr->notify_UserJobHasFinished(this);
}


