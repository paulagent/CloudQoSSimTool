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

#include "DockerDaemon.h"
#include <iostream>

Define_Module(DockerDaemon);

DockerDaemon::DockerDaemon() {
    // TODO Auto-generated constructor stu
    containerSet.clear();
    cout << "DockerDaemon::DockerDaemon()"<<endl;
}

DockerDaemon::~DockerDaemon() {
    // TODO Auto-generated destructor stub
    containerSet.clear();

}
void DockerDaemon::RunDocker(string image)
{
    cout<< "DockerDaemon::RunDocker" <<endl;
    DockerContainer* dockerContainer;
    dockerContainer=new DockerContainer();
    string name;
    int id,size;
    size=100; //MB
    cout<< "DockerDaemon::RunDocker" <<endl;

    if (containerSet.empty())
    {
        id=0;
        cout<< "DockerDaemon::RunDocker------->containerSet.empty()" <<endl;

    }
    else
    {
        id= containerSet.size();
        cout<< "DockerDaemon::RunDocker------->containerSet is not empty()" <<endl;

    }
    cout<< "docker id--------->"<<id<<endl;
    name="docker";
    cout<< "docker name--------->"<<name<<endl;

    dockerContainer->initialize( image,  name,  id, size);
    containerSet.push_back(dockerContainer);
    GetMem(size);

}
void DockerDaemon::GetMem(int size)
{

}
void DockerDaemon::FreeMem(int size)
{

}
void DockerDaemon::processSelfMessage (cMessage *msg){

}

void DockerDaemon::processRequestMessage (icancloud_Message *sm){

}



void  DockerDaemon::processResponseMessage (icancloud_Message *sm){

}
