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
#include "time.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdexcept>
#include <math.h>
#include "stdio.h"
#include "stdlib.h"
#include "ICCLog.h"
#include "Memoization_uthash.h"
#include "Machine.h"


class DockerContainer : public Machine{

public:
    DockerContainer();
    ~DockerContainer();
    void initialize(string image, string name,string id, int siz, string fullName);
    string id;
    string image;
    string name;
    string fullname; // combination of userID:vmID:containerID
    clock_t createdTime;
    int size;
    int status;  // running 1 / exited 0

protected:
    virtual void handleMessage(cMessage* msg);
    virtual void finish(){};
 //   void stopDockerContainer (string containerID);
 //   void startDockerContainer(string imagesID,string VMID);
    /**
           * Start the container application execution.
           */
};

#endif /* DockerContainer */
