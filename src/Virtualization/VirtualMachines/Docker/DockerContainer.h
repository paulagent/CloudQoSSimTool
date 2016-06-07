/*
 * DockerContainer.h
 *
 *  Created on: May 30, 2016
 *      Author: binggao
 */

#ifndef DockerContainer_H_
#define DockerContainer_H_

#include <omnetpp.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdexcept>
#include <math.h>
#include "stdio.h"
#include "stdlib.h"
#include "ICCLog.h"
#include "Memoization_uthash.h"

class DockerContainer: public cSimpleModule {

public:
    DockerContainer();
    ~DockerContainer();
    void initialize(string image, string name,int id);
    int id;
    string image;
    string name;
    clock_t createdTime;
    int status;  // running 1 / exited 0

protected:
    virtual void handleMessage(cMessage* msg);
    virtual void finish(){};
    void stopDockerContainer (string containerID);
    void startDockerContainer(string imagesID,string VMID);
    /**
           * Start the container application execution.
           */
   virtual void startExecution ();
};

#endif /* DockerContainer */
