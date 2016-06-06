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

#include <RequestsManagement.h>

RequestsManagement::~RequestsManagement() {
    requestsQueue.clear();
    temporalRequestsQueue.clear();
    executingRequests.clear();
}
/*RequestsManagement::RequestsManagement()
 {
 printf("\n Method[RequestsManagement::initialize]: ------->initialize \n");
 schedulerQueueBlocked = false;
 requestsQueue.clear();
 temporalRequestsQueue.clear();
 executingRequests.clear();
 icancloud_Base::initialize();
 }*/
void RequestsManagement::initialize() {
    //printf("\n Method[RequestsManagement::initialize]: ------->initialize \n");
    schedulerQueueBlocked = false;
    requestsQueue.clear();
    temporalRequestsQueue.clear();
    executingRequests.clear();
    icancloud_Base::initialize();
}

void RequestsManagement::finish() {
    requestsQueue.clear();
    temporalRequestsQueue.clear();
    executingRequests.clear();
    icancloud_Base::initialize();
}

bool RequestsManagement::schedulerBlock() {

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

bool RequestsManagement::schedulerUnblock() {

    Enter_Method_Silent
    ();

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
void RequestsManagement::userSendRequest(AbstractRequest* request) {

    // Insert into the requestsQueue
    if (!schedulerQueueBlocked) {
        requestsQueue.push_back(request);
         cout << "RequestsManagement::userSendRequest --> NOT schedulerQueueBlocked --->requestsQueue.push_back(request)" << endl;
    } else {
        temporalRequestsQueue.push_back(request);
          cout << "RequestsManagement::userSendRequest -->  schedulerQueueBlocked  --->temporalRequestsQueue.push_back(request);" << endl;

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
vector<AbstractRequest*> RequestsManagement::getRequestByUserID(int userModID) {

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

AbstractRequest* RequestsManagement::getRequestByIndex(unsigned int index) {

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

int RequestsManagement::numPendingRequests() {
//cout << "RequestsManagement::numPendingRequests" << requestsQueue.size()<<endl;
    return requestsQueue.size();

}

void RequestsManagement::eraseRequest(unsigned int index) {

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

void RequestsManagement::eraseRequest(AbstractRequest* req) {

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

void RequestsManagement::user_request(AbstractRequest* request) {

    // Insert into the requestsQueue
    if (!schedulerQueueBlocked) {
        requestsQueue.push_back(request);
    } else {
        temporalRequestsQueue.push_back(request);
    }

}

void RequestsManagement::blockArrivalRequests(bool blocked) {
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
