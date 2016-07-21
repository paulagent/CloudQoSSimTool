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

package icancloud.src.Virtualization.VirtualMachines.SetDefinition;

import icancloud.src.Applications.Apps.AppBase;

module DockerImage
{
    parameters:
        string id;					// Identification
        int numCores;				// Number of cores
        double memorySize_MB;		// Amount of memory (in MiB) of VM
        double storageSize_GB;		// Amount of storage size (in GiB) of VM  

}