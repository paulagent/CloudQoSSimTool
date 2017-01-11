#ifndef __RUNNINGVM_H_
#define __RUNNINGVM_H_

#include <omnetpp.h>
#include <string.h>
#include "VM.h"
#include "NodeVL.h"

class NodeVL;
/**

 *
 */
class RunningVM{
public:
    int userID;
    int processID;
    VM* vm;
    NodeVL* hostNodeVL;
  //  vector<VM*> vmID;
    clock_t start_time;
    clock_t end_time;
    void initialize();
    RunningVM();
    ~RunningVM();
    int getPid () {return processID; };
       /**
        * This method classifies an incoming message and invokes the corresponding method
        * to process it.
        * @ param msg Incoming message.
        */
 //       bool handleMessage (cMessage *msg);

       /**
        * Module ending.
        */
 //       void finish();
};

#endif
