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

package icancloud.src.Virtualization.VirtualMachines.VMRequestManager.ResourcesProvisioning.DockerSchedulerRR;

//
// Module that is the core of a cloud manager scheduler
//
// The vmImages are the different virtual machines that the scheduler offers to the users
//
// @authors Gabriel Gonz&aacute;lez Casta&ntilde;&eacute
// @date 2014-12-11
// disabled print energy part by default value to false
//@author bing gao
//@date 2016-04-14


import icancloud.src.Virtualization.VirtualMachines.VMRequestManager.ResourcesProvisioning.DockerManagerScheduler;


module DockerSchedulerRR extends DockerManagerScheduler
{
    parameters:		
        
        @class(DockerSchedulerRR);
        @display("i=msg/job");
}

