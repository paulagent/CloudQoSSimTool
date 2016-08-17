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

#include "VmMsgController.h"
#include "AbstractCloudManager.h"

Define_Module(VmMsgController);

VmMsgController::~VmMsgController() {
    // TODO Auto-generated destructor stub
}

void VmMsgController::blockMessages() {
    migrateActive = true;
}

void VmMsgController::activateMessages() {
    migrateActive = false;
    flushPendingMessages();
}

bool VmMsgController::migrationPrepared() {
    return ((pendingCPUMsg == 0) && (pendingIOMsg == 0) && (pendingNetMsg == 0)
            && (pendingMemoryMsg == 0));
}

void VmMsgController::initialize() {
//cout << " VmMsgController::initialize()"<<endl;
    icancloud_Base::initialize();

    std::ostringstream osStream;

    migrateActive = false;
    pendingMessages.clear();
    pendingCPUMsg = 0;
    pendingNetMsg = 0;
    pendingMemoryMsg = 0;
    pendingIOMsg = 0;
    uId = -1;
    pId = -1;

    // Init state to idle!

    fromOSApps = new cGateManager(this);
    toOSApps = new cGateManager(this);
    fromApps = new cGateManager(this);
    toApps = new cGateManager(this);

}

void VmMsgController::finish() {

}

void VmMsgController::processSelfMessage(cMessage *msg) {
    delete (msg);
    //cout << "VmMsgController::processSelfMessage" << endl;

    std::ostringstream msgLine;
    msgLine << "Unknown self message [" << msg->getName() << "]";
    throw cRuntimeError(msgLine.str().c_str());
}

void VmMsgController::processRequestMessage(icancloud_Message *msg) {

    icancloud_App_NET_Message *sm_net;
    int operation;
    cout << "VmMsgController::processRequestMessage:    " <<msg->getFullName()<< endl;
    int Pid, Uid;
    Pid=msg->getPid();
    Uid = msg->getUid();
    cout << "PiD----->"<< Pid << endl;

    cout << "UiD----->"<< Uid << endl;
    if (Uid==-1 )
    {
        delete (msg);
    }
    else
    {
    sm_net = dynamic_cast<icancloud_App_NET_Message *>(msg);

    operation = msg->getOperation();

    cout << "operation-->" << operation << endl;

    if (operation == SM_STOP_AND_DOWN_VM) {

        if (!migrateActive) {
            blockMessages();
            sm_net->setIsResponse(true);
            migration_msg = msg;

            if (migrationPrepared()) {
                notifyVMPreparedToMigrate();
            }

        } else {
            delete (msg);
        }

    }

    else if (((int) msg->getOperation()) == SM_VM_ACTIVATION) {

        finishMigration();
        delete (msg);
    }

    else {

        // Set the id of the message (the vm id)
        msg->setPid(pId);
        msg->setUid(uId);

        // Set as application id the arrival gate id (unique per job).
        if ((sm_net != NULL) && (sm_net->getCommId() != -1)) {
            cout << "run this part" <<endl;
            insertCommId(uId, pId, msg->getCommId(), msg->getId());
       //     cout << "VmMsgController::processRequestMessage:  insertCommId   " << endl;
        }

        if (migrateActive) {
            pushMessage(msg);
        } else {

            // If msg arrive from OS
            if (msg->arrivedOn("fromOSApps")) {

                sendRequestMessage(msg,
                        toApps->getGate(msg->getArrivalGate()->getIndex()));
            }

            else if (msg->arrivedOn("fromApps")) {

                updateCounters(msg, 1);
cout << "VmMsgController::processRequestMessage--->fromApps--getIndex " <<msg->getArrivalGate()->getIndex() <<endl;
                msg->setCommId(msg->getArrivalGate()->getIndex());

                if (sm_net != NULL) {
                    // If the message is a net message and the destination user is null
                    if (sm_net->getVirtual_user() == -1) {
                        // Filter the name of the user
                        sm_net->setVirtual_user(msg->getUid());
                    }

                    sm_net->setVirtual_destinationIP(sm_net->getDestinationIP());
                    sm_net->setVirtual_destinationPort(sm_net->getDestinationPort());
                    sm_net->setVirtual_localIP(sm_net->getLocalIP());
                    sm_net->setVirtual_localPort(sm_net->getLocalPort());
                }
                cout << "msg->arrivedOn(\"fromApps\") -->gate id  is "<< msg->getCommId() << endl;
               // cout << "msg->arrivedOn(\"fromApps\") -->gate nameis "
              //          << toOSApps->getGate(msg->getCommId())->getFullName()
              //          << endl;
                sendRequestMessage(msg, toOSApps->getGate(msg->getCommId()));
            }

        }
    }


    }
}

void VmMsgController::processResponseMessage(icancloud_Message *sm) {

    // If msg arrive from OS

    updateCounters(sm, -1);
    cout << "VmMsgController::processResponseMessage" << endl;

    if (migrateActive) {
        pushMessage(sm);
        if (migrationPrepared()) {
            notifyVMPreparedToMigrate();
        }
    } else {

        icancloud_App_NET_Message *sm_net;
        sm_net = dynamic_cast<icancloud_App_NET_Message *>(sm);

        if (sm_net != NULL) {
            updateCommId(sm_net);
        }

        sendResponseMessage(sm);
    }
}

cGate* VmMsgController::getOutGate(cMessage *msg) {

    // Define ..
    cGate* return_gate;
    int i;
    bool found;
   // cout << "VmMsgController::getOutGate" << endl;

    // Initialize ..
    i = 0;
    found = false;

    // If msg arrive from OS
    if (msg->arrivedOn("fromOSApps")) {

        while ((i < gateCount()) && (!found)) {
            if (msg->arrivedOn("fromOSApps", i)) {
                return_gate = (gate("toOSApps", i));
                found = true;
            }
            i++;
        }

    }

    else if (msg->arrivedOn("fromApps")) {

        while ((i < gateCount()) && (!found)) {
            if (msg->arrivedOn("fromApps", i)) {
                return_gate = (gate("toApps", i));
                found = true;
            }
            i++;
        }

    }

    return return_gate;
}

void VmMsgController::notifyVMPreparedToMigrate() {
    sendResponseMessage(migration_msg);
}

void VmMsgController::finishMigration() {
    migrateActive = false;
    flushPendingMessages();
}

void VmMsgController::pushMessage(icancloud_Message* sm) {

    pendingMessages.insert(pendingMessages.end(), sm);

}

icancloud_Message* VmMsgController::popMessage() {
    vector<icancloud_Message*>::iterator msgIt;

    msgIt = pendingMessages.begin();
    pendingMessages.erase(msgIt);

    return (*msgIt);

}

void VmMsgController::sendPendingMessage(icancloud_Message* msg) {
    int smIndex;
    cout << "VmMsgController::sendPendingMessage" << endl;

    // The message is a Response message
    if (msg->getIsResponse()) {
        sendResponseMessage(msg);
    }

    // The message is a request message
    else {
        smIndex = msg->getArrivalGate()->getIndex();
        if (msg->arrivedOn("fromOSApps")) {
            sendRequestMessage(msg, toApps->getGate(smIndex));
        }

        else if (msg->arrivedOn("fromApps")) {
            updateCounters(msg, 1);
            cout << "msg-111111>arrivedOn(\"fromApps\")" << endl;
            sendRequestMessage(msg, toOSApps->getGate(smIndex));
        }

    }
}

void VmMsgController::flushPendingMessages() {

    // Define ..
    vector<icancloud_Message*>::iterator msgIt;

    // Extract all the messages and send to the destinations

    cout << "VmMsgController::flushPendingMessages()" << endl;

    while (!pendingMessages.empty()) {
        msgIt = pendingMessages.begin();

        sendPendingMessage((*msgIt));
        pendingMessages.erase(pendingMessages.begin());
    }

}

int VmMsgController::pendingMessagesSize() {
    return pendingMessages.size();
}

void VmMsgController::updateCounters(icancloud_Message* msg, int quantity) {
    icancloud_App_CPU_Message* cpuMsg;
    icancloud_App_IO_Message* ioMsg;
    icancloud_App_MEM_Message* memMsg;
    icancloud_App_NET_Message* netMsg;
    cout << "VmMsgController::updateCounters" << endl;

    cpuMsg = dynamic_cast<icancloud_App_CPU_Message*>(msg);
    ioMsg = dynamic_cast<icancloud_App_IO_Message*>(msg);
    memMsg = dynamic_cast<icancloud_App_MEM_Message*>(msg);
    netMsg = dynamic_cast<icancloud_App_NET_Message*>(msg);

    if (cpuMsg != NULL) {
        pendingCPUMsg += quantity;
    } else if (ioMsg != NULL) {
        pendingIOMsg += quantity;
    } else if (memMsg != NULL) {
        pendingMemoryMsg += quantity;
    } else if (netMsg != NULL) {
        pendingNetMsg += quantity;
    }
}

void VmMsgController::linkNewApplication(cModule* jobAppModule, cGate* scToApp,
        cGate* scFromApp) {

    // Connections to App
    cout << "VmMsgController::linkNewApplication" << endl;
    int idxToApps = toApps->newGate("toApps");
    toApps->connectOut(jobAppModule->gate("fromOS"), idxToApps);

    int idxFromApps = fromApps->newGate("fromApps");
    fromApps->connectIn(jobAppModule->gate("toOS"), idxFromApps);

    // Connections to SyscallManager
   // cout << "VmMsgController::here is problem" << endl;
    int idxToOs = toOSApps->newGate("toOSApps");
    toOSApps->connectOut(scFromApp, idxToOs);

    int idxFromOS = fromOSApps->newGate("fromOSApps");
    fromOSApps->connectIn(scToApp, idxFromOS);

}

int VmMsgController::unlinkApplication(cModule* jobAppModule) {

    int gateIdx = jobAppModule->gate("fromOS")->getPreviousGate()->getId();
    int position = toApps->searchGate(gateIdx);
    cout << "VmMsgController::unlinkApplication" << endl;

    toOSApps->freeGate(position);
    toApps->freeGate(position);

    // Connections to SyscallManager
    fromApps->freeGate(position);
    fromOSApps->freeGate(position);

    return position;

}

void VmMsgController::setId(int userId, int vmId) {
    uId = userId;
    pId = vmId;

}

void VmMsgController::insertCommId(int uId, int pId, int commId, int msgId) {

    // Define ..
    bool found;
    commIdVector* comm;
    commIdVectorInternals* internals;
    cout << "VmMsgController::insertCommId     --> " <<endl;
    // Initialize ..
    found = false;

    // Search at structure if there is an entry for the same VM
    for (int i = 0; (i < (int) commVector.size()) && (!found); i++) {

        // The VM exists
        if (((*(commVector.begin() + i))->uId == uId)
                && ((*(commVector.begin() + i))->pId == pId)) {

            // Create the new entry
            internals = new commIdVectorInternals();
            internals->msgId = msgId;
            internals->commId = commId;

            // Add the new entry to the structure
            (*(commVector.begin() + i))->internals.push_back(internals);

            found = true;      // break the loop
        }
    }

    // There is no entry for the vector..-
    if (!found) {
        // Create the general entry
        comm = new commIdVector();
        comm->uId = uId;
        comm->pId = pId;
        comm->internals.clear();

        // Create the concrete entry for the message
        internals = new commIdVectorInternals();

        internals->msgId = msgId;
        internals->commId = commId;
        comm->internals.push_back(internals);

        commVector.push_back(comm);
    }
}

void VmMsgController::updateCommId(icancloud_App_NET_Message* sm) {
    // Define ..
    bool found;
    commIdVector* comm;
    commIdVectorInternals* internals;

    // Initialize ..
    found = false;

    for (int i = 0; i < (int) commVector.size(); i++) {
        comm = (*(commVector.begin() + i));
        for (int j = 0; (j < (int) comm->internals.size()) && (!found); j++) {
            internals = (*(comm->internals.begin() + j));
        }
    }

    for (int i = 0; (i < (int) commVector.size()) && (!found); i++) {

        comm = (*(commVector.begin() + i));

        if ((sm->getUid() == comm->uId) && (sm->getPid() == comm->pId)) {

            for (int j = 0; (j < (int) comm->internals.size()) && (!found);
                    j++) {

                internals = (*(comm->internals.begin() + j));

                if (internals->msgId == sm->getId()) {
                    sm->setCommId(internals->commId);
                    comm->internals.erase(comm->internals.begin() + j);
                    found = true;
                }
            }

            if ((found) && ((int) comm->internals.size() == 0)) {
                commVector.erase(commVector.begin() + i);
            }

        }
    }
}
