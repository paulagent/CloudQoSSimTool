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

#include "Node.h"

Define_Module(Node);

void Node::initialize(){

    printf("Node::initialize()");
    AbstractNode::initialize();
    // Initialize the state
    energyMeterPtr = NULL;

}

void Node::finish(){
    AbstractNode::finish();
}

//----------------------------------------------------------------------------------

void Node::turnOn (){

    if (equalStates(getState(),MACHINE_STATE_OFF)){

            AbstractNode::changeState(MACHINE_STATE_IDLE);
            energyMeterPtr->switchOnPSU();
    }

}

void Node::turnOff (){

    if (!equalStates(getState(), MACHINE_STATE_OFF)){
        AbstractNode::changeState(MACHINE_STATE_OFF);
        energyMeterPtr->switchOffPSU();
    }
}

void Node::initNode (){

    RoutingTable* rTable;
    string ipNode;
    string state;
    // Init ..

    try{

        //get the ip of the Node
        rTable = dynamic_cast <RoutingTable*> (getSubmodule("routingTable"));

        if (rTable == NULL) throw cRuntimeError("BaseNode::initNode -> The node %s[%i] has no assigned ip. Check if everything is correctly configured..\n", getFullName(), getIndex());

        ipNode = rTable->getRouterId().str();
        if (strcmp(ipNode.c_str(), "<unspec>") == 0){
            ipNode = "0.0.0.0";
        }
        ip = ipNode.c_str();

        par("ip").setStringValue(ip.c_str());

        // Init the parameters
        initialize();
        storageNode = par("storageNode").boolValue();
        state = par("initialState").stringValue();
        storageLocalPort = par("storage_local_port").longValue();
/*

       elementType* el;
       el= new elementType();
       el->setMemorySize(par("memorySize_MB").doubleValue());

       el->setNumCores(par("numCores"));
       el->setDiskSize(par("storageSize_GB").doubleValue());


        type=el;
*/

        cModule* mod = getSubmodule("energyMeter")->getSubmodule("meterController");

        energyMeterPtr = check_and_cast <EnergyMeterController*> (mod);
        energyMeterPtr->init();
        energyMeterPtr->registerMemorization(getParentModule()->getSubmodule("manager")->par("memorization").boolValue());
        energyMeterPtr->activateMeters();

        // initialize system apps
        int port;
         port = storageLocalPort;
        initialize_syscallManager(port);

         if (equalStates(getState(),MACHINE_STATE_OFF)) turnOff();
         else if (!equalStates(getState(),MACHINE_STATE_OFF)) turnOn();
         else throw cRuntimeError("Node::initNode ->initializing state unknown [%s]\n", state.c_str());

    }catch (exception& e){
        throw cRuntimeError("Node::initNode -> can not initialize the node module!...");
    }

}

void Node::notifyManager (icancloud_Message* msg){
    AbstractDCManager* manager;

    manager = dynamic_cast <AbstractDCManager*> (managerPtr);
    if (manager == NULL) throw cRuntimeError ("Node::notifyVMConnectionsClosed -> Manager can not be casted\n");

    manager->notifyManager(msg);
};



void Node::setManager(icancloud_Base* manager){

    managerPtr = dynamic_cast <AbstractDCManager*> (manager);
    if (managerPtr == NULL) throw cRuntimeError ("Node::notifyVMConnectionsClosed -> Manager can not be casted\n");
};




