/*
 * DockerContainer.cc
 *
 *  Created on: May 30, 2016
 *      Author: binggao
 */

#include "DockerContainer.h"

Define_Module(DockerContainer);

DockerContainer::DockerContainer() {
    // TODO Auto-generated constructor stub

}

DockerContainer::~DockerContainer() {
    // TODO Auto-generated destructor stub
}
void DockerContainer::initialize(string image, string name,int id)
{
    cout << "DockerContainer::initialize"<< endl;
    this->image=image;
    this->name=name;
    this->id=id;
    this->status=1;  //running
    this->createdTime=clock();
    cout << "image:" << image << "----name:"<<name <<"-----id:"<<id<<"------createdTime:"<<createdTime<<endl;
}
void DockerContainer::handleMessage(cMessage* msg){
    throw cRuntimeError ("VmImage::handleMessage->this module does not receive messages\n");
}
void DockerContainer:: stopDockerContainer (string containerID) {

}
void DockerContainer::startDockerContainer(string imagesID,string VMID){

}

void DockerContainer:: startExecution (){

}
