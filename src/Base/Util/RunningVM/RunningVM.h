#ifndef __RUNNINGVM_H_
#define __RUNNINGVM_H_

#include <omnetpp.h>
#include <string.h>
#include "VM.h"

/**
 * @class ResourcesMeter ResourcesMeter.h "ResourcesMeter.h"
 *
 * This module performs measures of resources like RAM, CPU, etc...
 *
 * @author Alberto N&uacute;&ntilde;ez Covarrubias
 * @date 02-10-2007
 */
class RunningVM{
public:
    int user;
   // VM* vm;
    vector<VM*> vmID;
    clock_t start_time;
    clock_t end_time;
    void initialize();

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
