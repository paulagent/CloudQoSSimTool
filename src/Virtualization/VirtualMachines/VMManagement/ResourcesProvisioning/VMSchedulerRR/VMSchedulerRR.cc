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

#include <ResourcesProvisioning/VMSchedulerRR/VMSchedulerRR.h>

VMSchedulerRR::VMSchedulerRR() {
    // TODO Auto-generated constructor stub

}

VMSchedulerRR::~VMSchedulerRR() {
    // TODO Auto-generated destructor stub
}


void VMSchedulerRR::schedule()
{
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
    //  selectedNodes.clear();
     // attendedRequest_vms.clear();
      j = 0;

      // Begin
      // Schedule..
      cout<<endl;

      cout << "------------------------------------------VIRTUAL MACHINE SCHEDULER------------------------------------------"<<endl;
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
