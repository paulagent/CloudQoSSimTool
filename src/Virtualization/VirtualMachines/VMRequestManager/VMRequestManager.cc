/*
 * VMRequestManager.cc
 *
 *  Created on: Jun 1, 2016
 *      Author: zahra
 */

/*
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
 */

#include <VMRequestManager/VMRequestManager.h>
Define_Module(VMRequestManager);
/*VMRequestManager::VMRequestManager() {
 // TODO Auto-generated constructor stub

 }*/

VMRequestManager::~VMRequestManager() {
    // TODO Auto-generated destructor stub
    requestsQueue.clear();
    temporalRequestsQueue.clear();
    executingRequests.clear();
}

void VMRequestManager::initialize() {
    //  printf("\n Method[RequestsManagement::initialize]: ------->initialize \n");
    schedulerQueueBlocked = false;
    requestsQueue.clear();
    temporalRequestsQueue.clear();
    executingRequests.clear();
    //   icancloud_Base::initialize();
testnumber =42;
cout<< "VMRequestManager::initialize() testnumber  " << testnumber <<endl;
//       cModule* networkManagerMod;
//
//
//       networkManagerMod = getParentModule()->getSubmodule("networkManager");
//       networkManager = check_and_cast<NetworkManager*>(networkManagerMod);

cModule* dockerSet =getParentModule()->getSubmodule("dockerSet");
       if (dockerSet == NULL)
           throw cRuntimeError(
                    "VMRequestManager::initialize() dup-> Error during initialization. There is no dockerSet\n");

     int dockerSetSize = dockerSet->par("dockerImageQuantity").longValue();
     for (int i = 0; i < dockerSetSize; i++) {
         cModule* dockerImage = dockerSet->getSubmodule("dockerImage", i);

         // cfg->setVMType(vmImage->par("id").stringValue(),
         //         vmImage->par("numCores"),
         dockermem = dockerImage->par("memorySize_MB").doubleValue();

     }
   // cModule* Image2 = getSubmodule("vmImage");

    //    cout << "VMRequestManager::initialize()" <<dockermem <<endl;
      //  id = dockerImage->par("id").stringValue();



       cout << "VMRequestManager::initialize()--->dockermem " << dockermem
                    << endl;
        //   vmImage->par("storageSize_GB").doubleValue());
        // Parameters are correct so far
  //  }

}

void VMRequestManager::finish() {
    requestsQueue.clear();
    temporalRequestsQueue.clear();
    executingRequests.clear();
    //  icancloud_Base::initialize();
}

bool VMRequestManager::schedulerBlock() {

    bool result;

    result = true;

    if (schedulerQueueBlocked) {

        result = false;

    } else {
        blockArrivalRequests(true);
        schedulerQueueBlocked = true;
    }

    return result;

}

bool VMRequestManager::schedulerUnblock() {

     Enter_Method_Silent();

    bool result;

    result = true;

    if (schedulerQueueBlocked) {

        result = true;
        schedulerQueueBlocked = false;

    }

    blockArrivalRequests(false);
    return result;

}

// ---------------------- Interact with requests and requestsQueue ------------------------------------
void VMRequestManager::userSendRequest(AbstractRequest* request) {

    // Insert into the requestsQueue
    if (!schedulerQueueBlocked) {
        requestsQueue.push_back(request);
        cout
                << "VMRequestManager::userSendRequest --> NOT schedulerQueueBlocked --->requestsQueue.push_back(request)"
                << endl;
        schedule();

        //call schedule() in here  why?

    } else {
        temporalRequestsQueue.push_back(request);
        //   cout << "RequestsManagement::userSendRequest -->  schedulerQueueBlocked  --->temporalRequestsQueue.push_back(request);" << endl;

    }

}
/*
 void RequestsManagement::reinsertRequest(AbstractRequest* req,
 unsigned int index) {

 // Define ...
 vector<AbstractRequest*>::iterator it;

 // Insert ..
 if ((index >= 0) && (index < requestsQueue.size())) {
 if (requestsQueue.size() > 0)
 requestsQueue.insert(requestsQueue.begin() + index, req);
 } else {
 req->incrementTimesEnqueue();
 requestsQueue.push_back(req);
 }
 }
 */
vector<AbstractRequest*> VMRequestManager::getRequestByUserID(int userModID) {

    //Define...
    vector<AbstractRequest*>::iterator reqIt;
    vector<AbstractRequest*> reqs;
    bool found;

    //Initialize...
    found = false;
    reqs.clear();

    //Search the job into jobsList
    for (reqIt = requestsQueue.begin(); reqIt < requestsQueue.end(); reqIt++) {

        if ((*reqIt)->getUid() == userModID) {
            reqs.push_back((*reqIt));
        }
    }

    if (!found)
        reqs.clear();

    return reqs;
}

AbstractRequest* VMRequestManager::getRequestByIndex(unsigned int index) {

    // Define ...
    AbstractRequest* req;

    // Initialize...
    req = NULL;

    if ((index >= 0) && (index < requestsQueue.size())) {

        // Obtain the request at position = index
        if (requestsQueue.size() > 0)
            req = (*(requestsQueue.begin() + index));
    }

    return req;

}

int VMRequestManager::numPendingRequests() {
//cout << "RequestsManagement::numPendingRequests" << requestsQueue.size()<<endl;
    return requestsQueue.size();

}

void VMRequestManager::eraseRequest(unsigned int index) {

    vector<AbstractRequest*>::iterator reqIt;

    if ((index >= 0) && (index < requestsQueue.size())) {

        if (requestsQueue.size() > 0) {
            reqIt = requestsQueue.begin() + index;
            requestsQueue.erase(reqIt);
        }
    } else {
        throw cRuntimeError(
                "Error in [RequestsManagement]: -------> erase_request: requestsQueue size:%i index:%i\n ",
                requestsQueue.size(), index);
    }

}

void VMRequestManager::eraseRequest(AbstractRequest* req) {

    vector<AbstractRequest*>::iterator reqIt;
    unsigned int index;
    bool found = false;
    //cout << "RequestsManagement::eraseRequest"<<endl;
    for ((index = 0); (index < requestsQueue.size()) && (!found); index++) {

        reqIt = requestsQueue.begin() + index;

        if (req->compareReq(*(reqIt))) {
            found = true;

            if (req->getOperation() == REQUEST_STORAGE) {
                insertExecutingRequest(req);
            }

            requestsQueue.erase(reqIt);

        }
    }

}

void VMRequestManager::user_request(AbstractRequest* request) {

    // Insert into the requestsQueue
    if (!schedulerQueueBlocked) {
        requestsQueue.push_back(request);
    } else {
        temporalRequestsQueue.push_back(request);
    }

}

void VMRequestManager::blockArrivalRequests(bool blocked) {
    // cout << "RequestsManagement::blockArrivalRequests" <<endl;

    if (!blocked) {
        //  AbstractRequest* req1= *requestsQueue.end();
        // cout << "RequestsManagement::blockArrivalRequests----> requestsQueue.size() " << requestsQueue.size() <<endl;
        //  unsigned int i=0;
        //  cout << "RequestsManagement::blockArrivalRequests----> temporalRequestsQueue.size()" <<temporalRequestsQueue.size()<<endl;
        for (std::vector<AbstractRequest*>::iterator it =
                temporalRequestsQueue.begin();
                it != temporalRequestsQueue.end(); ++it) {
            /* std::cout << *it; ... */
            //  AbstractRequest* req1 = *it;
            //     cout << "RequestsManagement::blockArrivalRequests---->from temporal: req1->getPid()" << req1->getUid() << "operation" <<req1->getOperation()  << endl;
            requestsQueue.push_back(*it);
        }

        //   while (temporalRequestsQueue.size() != 0){
        //       AbstractRequest* req_b= *requestsQueue.begin();
        //       cout << "RequestsManagement::blockArrivalRequests----> *(temporalRequestsQueue.begin()+i)" << req_b->getUid()  <<endl;
        //      requestsQueue.push_back((*temporalRequestsQueue.begin()));

        //       temporalRequestsQueue.erase(temporalRequestsQueue.begin());

        // while (i< temporalRequestsQueue.size()){

        //  requestsQueue.push_back(*(temporalRequestsQueue.begin()+i));

        //      cout << "RequestsManagement::blockArrivalRequests----> requestsQueue.size() " << requestsQueue.size() <<endl;

        //cout << "RequestsManagement::blockArrivalRequests----> req->getUid()" << req->getUid() <<endl;

        // ++i;
        //  temporalRequestsQueue.erase(temporalRequestsQueue.begin());
        // }
        temporalRequestsQueue.clear();
        //  cout << "RequestsManagement::blockArrivalRequests----> temporalRequestsQueue.size() after erase " << temporalRequestsQueue.size() <<endl;
        // for (std::vector<AbstractRequest*>::iterator it = requestsQueue.begin();
        //       it != requestsQueue.end(); ++it) {
        /* std::cout << *it; ... */
        // AbstractRequest* req = *it;
        //   cout << "RequestsManagement::blockArrivalRequests---->from requestQueue req->getUid()" << req->getUid() <<": "<< req->getPid() <<":"<< req->getOperation() <<endl;
        //  }
    }

    schedulerQueueBlocked = blocked;
}
void VMRequestManager::schedule() {
    //Define ...
    vector<AbstractNode*> selectedNodes;
    vector<VM*> attendedRequest_vms;
    //  NodeVL* node;
    //  Machine* machine;
    AbstractRequest* req;
    //   StorageRequest* req_st;
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
    //  selectedNodes.clear();
    // attendedRequest_vms.clear();
    j = 0;

    // Begin
    // Schedule..
    cout << endl;

    cout
            << "------------------------------------------VIRTUAL MACHINE SCHEDULER------------------------------------------"
            << endl;
    if (schedulerBlock()) {

        req = getRequestByIndex(j);
        // Start with the vm allocation

        //  while ((j < (numPendingRequests())) && (req != NULL)){
        while ((j < (numPendingRequests()))) {
            // uvic:
            if (req == NULL) {
                cout
                        << "Method[VMRequestManager::schedule()]: -------> req == NULL"
                        << endl;
                eraseRequest(req);
                requestErased = true;
            }
            //uvic
            printf(
                    "\n Method[VMRequestManager::schedule()]: ------->numPendingRequests------> %d \n",
                    numPendingRequests());
            printf(
                    "\n Method[VMRequestManager::schedule()]: ------->userid------> %d \n",
                    req->getUid());
            printf(
                    "\n Method[VMRequestManager::schedule()]: ------->REQUEST TYPE: %d \n",
                    req->getOperation());
            printf(
                    "\n Method[VMRequestManager::schedule()]: -------> inside request loop\n");

            req_vm = dynamic_cast<RequestVM*>(req);

            if (req_vm != NULL) {
                cout
                        << "Method[VMRequestManager::schedule()]: -------> req_vm is not NULL!"
                        << endl;
                /*      if (req->getOperation() == REQUEST_START_VM) {
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
                 else
                 */
                if (req->getOperation() == REQUEST_START_DOCKER_CONTAINER) {
                    printf(
                            "\n Method[VMRequestManager::schedule()]: -------> REQUEST_START_DOCKER_CONTAINER\n");
                    notEnoughResources = request_start_docker_container(req_vm);
                    testnumber =43;
                    if (!notEnoughResources) {
                        eraseRequest(req);
                        requestErased = true;
                    }

                } else if (req->getOperation() == REQUEST_UNFREEZE_CONTAINER) {
                    printf("\n Method[VMRequestManager::schedule()]: -------> REQUEST_UNFREEZE_CONTAINER\n");
                    notEnoughResources = request_unfreez_container(req_vm);
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
        cout << endl;
        cout
                << "-----------------------------------------END SCHEDULE --------------------------------------"
                << endl;
        schedulerUnblock();
    }

}
bool VMRequestManager::request_unfreez_container(RequestVM* req_vm){

    VM* vm;
        vm = req_vm->getVM(0);
        id = req_vm->getContainerID();
        vm->wakeup(id);
        double freem = vm->getFreeMemory();
        vm->setFreeMemory(freem + dockermem);
        return false;
}



bool VMRequestManager::request_start_docker_container(RequestVM* req_vm) {
    VM* vm;
    cout << "VMRequestManager::start_docker()--->dockermem " << dockermem
                  << endl;

    cout << "VMRequestManager::start_docker()--->test " << testnumber << endl;


    vm = req_vm->getVM(0);
    cout << " VMRequestManager::request_start_docker_container---->vm->getFullName-------->"
            << vm->getFullName() << endl;
    RunningContainer* started_Container = new RunningContainer();
    double freem = vm->getFreeMemory();
    string ip = vm->getIP();


int cores = vm->getNumCores();
cout << "VMRequestManager::request_start_docker_container getNumCores--->" <<cores <<endl;


    vm->dockerDaemon->initialize(vm);
    bool found = false;
    if (freem >= dockermem) {

        vm->setFreeMemory(freem - dockermem);
    cout << "VMRequestManager::request_start_docker_container inside if " << vm->getFreeMemory() <<endl;
        vm->dockerDaemon->startDockerContainer(id, vm->getFullName());
        found =true;
    } else {

        scheduleRR( vm);
    }
if(found) {
    clock_t now = clock();
    started_Container->start_time = now;
    started_Container->end_time = now + 200000; //clocks per secs   this should be change to parameter defined in ini file, so customer can change at anytime, not hardcode.
    started_Container->vmID = vm->getFullName();
    started_Container->containerID = vm->getFullName() + 1;//to fix this how to get container id
    rContainer.push_back(started_Container);
    cout
               << "VMRequestManager::request_start_docker_container------------------> Container has started"
               << endl;
    return false;
}
else {
    cout <<"there is no enough resources" <<endl;
    return true;
}
    // cout << vm->dockerDaemon->containerSet.end();

    return false;
}
void VMRequestManager::scheduleRR(VM* vm) {
    int j = 0;

    printf(
            "\n\n\n\n Method[VMRequestManager_SCHEDULER_RR::scheduleRR()]: -------> Before our loop\n");

    cout << "Method[VMRequestManager_SCHEDULER_RR::scheduleRR()]: while loop"
            << rContainer.size() << endl;
    while (j < int(rContainer.size()) && rContainer.size() != 0) {
        clock_t t = clock(); // we are not sure about current time

        printf(
                "\n Method[VMRequestManager_SCHEDULER_RR::scheduleRR()]:NO_Runiing_VM -------> %ld \n",
                rContainer.size());

        RunningContainer* rc;
        rc = rContainer.at(j);
        if (t >= rc->end_time)   // we need to shutdown vm
                {
            vm->sleep(rc->containerID);
            printf(
                    "\n Method[VMRequestManager_SCHEDULER_RR ::scheduleRR()]: -------> t is greater than  container end_time, we need to shut down container\n");

            // make new request


            AbstractRequest* new_req;
            RequestVM* new_req_c = new RequestVM();

            string  id= rc->container->getContainerId();

            //string id;          // string which will contain the result

           // ostringstream convert;   // stream used for the conversion

        //    convert << a;      // insert the textual representation of 'Number' in the characters in the stream

         //   id = convert.str();
         //   cout << "container full name" <<a <<endl;
        //    string delimeter = ":";
        //    string token = a.substr(0, a.find(delimeter));

            new_req_c->setPid(vm->getPid());
            new_req_c->setUid(vm->userID);
            new_req_c ->setContainerID(id);

            // add new request to temp queue

            new_req = dynamic_cast<AbstractRequest*>(new_req_c);
            new_req->setOperation(REQUEST_UNFREEZE_CONTAINER);

            //RequestsManagement::userSendRequest(new_req);

            // Freezing VM by unlink all resources

           // AbstractNode* node;
          //  node = vm->hostNodeVL;
           // cout << "hostNode----->" << vm->hostNodeVL->getFullName() << endl;


           // AbstractCloudManager::unlinkVM(vm->hostNodeVL, vm->vm, false);

            rContainer.erase(rContainer.begin() + j);
            cout << "VMRequestManager_SCHEDULER_RR:: scheduleRR()---->After Free Resources"
                    << endl;

        } else {
            ++j;

        }
    }

    printf("\n Method[VMRequestManager_SCHEDULER_RR]: -------> After our loop\n");

}

