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


