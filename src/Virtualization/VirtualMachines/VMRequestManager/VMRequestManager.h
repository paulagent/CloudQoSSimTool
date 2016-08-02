/*
 * VMRequestManager.h
 *This class is the key component of docker container scheduling function. It received request from user and dispatch
 * this request to VM which can support this request. If no VM can satisfied this request, it will trigger
 * round robin algorithm to make one of timeout container go to sleep.
 *
 *  Created on: Jun 1, 2016
 *      Author: zahra
 *    updated on: Aug 1, 2016
 *      Author: Bing
 */

#ifndef VMREQUESTMANAGER_H_
#define VMREQUESTMANAGER_H_
#include "Request.h"
#include "icancloud_Base.h"
#include "RequestVM.h"
#include <vector>
#include "RunningContainer.h"
#include <omnetpp.h>
#include "RequestsManagement.h"
#include "NetworkManager.h"
class RequestVM;

//class VMRequestManager: public icancloud_Base{

class VMRequestManager: public cSimpleModule {
protected:

    /** Bool that control if the main queue does not receive messages */
    bool schedulerQueueBlocked;

    vector<RunningContainer*> rContainer;
    /** If schedulerQueueBlocked = false, the requests are allocated in this queue */
    vector<AbstractRequest*> requestsQueue;
    /** Pointer to manage the network connections between nodes and VMs */
    NetworkManager* networkManager;

    /*************************************************************************************
     *                               Requests Management
     *************************************************************************************/
    /*
     * This method block the arrival of messages to the main queue
     */
    bool schedulerBlock();

    /*
     * This method unblock the temporal messages arrival..
     */
    bool schedulerUnblock();

    /*
     * To reinsert the request at the posiion index of the requests quetue

     void reinsertRequest (AbstractRequest* req, unsigned int index);
     */
    /*
     * Returns the set of requests from requestsQueue that id are the same as userModID
     */
    vector<AbstractRequest*> getRequestByUserID(int userModID);

    /*
     * Returns the request from requestsQueue at 'index' position
     */
    AbstractRequest* getRequestByIndex(unsigned int index);

    /*
     * Returns the size of the requests queue
     */
    int numPendingRequests();

    /*
     * Erase the request at position 'index'
     */
    void eraseRequest(unsigned int index);

    /*
     * Erase a request if compare(req, requestsQueue(i)) = true
     */
    void eraseRequest(AbstractRequest* req);

    /*****************************************************************
     *             Management of the temporal requests queue
     ****************************************************************/
    vector<AbstractRequest*> temporalRequestsQueue; /** If schedulerQueueBlocked = true, the requests are allocated in this queue */

    /*
     * This method enqueue the request at temporal requests queue if the arrival is blocked.
     *  If it is not blocked, the request will be enqueue at requests queue.
     */
    void user_request(AbstractRequest* request);

    /*
     * This method is responsible for block the requestsQueue redirecting the
     * incoming requests to the temporalQueue.
     */
    void blockArrivalRequests(bool blocked);

    /*****************************************************************
     *              Management of executing requests
     *****************************************************************/

    /*
     *  this vector allocates the pending requests that are been processed by node,
     *  such as the file storage or the fs creation.
     */
    vector<AbstractRequest*> executingRequests;

    /*
     * Insert an executing request into the vector
     */
    void insertExecutingRequest(AbstractRequest* req) {
        executingRequests.push_back(req);
    }
    ;

    /*
     * Returns the executing requests vector size
     */
    int getExecutingRequestsSize() {
        return (int) executingRequests.size();
    }
    ;

    /*
     * Returns the executing request at position given as parameter
     */
    AbstractRequest* getExecutingRequest(int index) {
        return (*(executingRequests.begin() + index));
    }
    ;

    /*
     * Erases the executing request at position given as parameter
     */
    void eraseExecutingRequest(int index) {
        executingRequests.erase(executingRequests.begin() + index);
    }
    ;

public:

    string id;

    ~VMRequestManager();
    /*
     * Module initialization
     */
    void initialize();

    /**
     * Module ending.
     */
    void finish();
    /**
         * input : None
         * output: None
         * this is the key function in the class, it will handle all the request. based on different type of
         * reqeust (aka operation) it will call different method to execute the request.
         */
    void schedule();
    /**
         * input: ReqeuestVM instance
         * output: boolean value to decide operation success or not
         * this function will start a new container based on request
         */
    bool request_start_docker_container(RequestVM* req_vm);
    /**
         * Input: ReqeuestVM instance
         * output: boolean value to decide operation success or not
         * this function will restart docker container based on request
         */
    bool request_unfreez_container(RequestVM* req_vm);

    /*********************************************************************************
     *                                      Methods
     *********************************************************************************/

    /*
     * When an user realize an request, the manager insert it into the
     * request queue waiting until it will be processed.
     */
    void userSendRequest(AbstractRequest* request);
    /**
         * input:.
         * output : None
         * this function would called by system if there is no VM can support current request. it will search
         * vector running container to find time out container, if it can located one, it will make it sleep, otherwise
         * it will tell caller there is no enough resource.
         */
    void scheduleRR(VM* vm);
};

#endif /* VMREQUESTMANAGER_H_ */

