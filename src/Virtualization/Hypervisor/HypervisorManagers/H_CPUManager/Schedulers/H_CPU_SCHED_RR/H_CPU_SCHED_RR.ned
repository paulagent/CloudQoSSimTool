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

package icancloud.src.Virtualization.Hypervisor.HypervisorManagers.H_CPUManager.Schedulers.H_CPU_SCHED_RR;
import icancloud.src.Virtualization.Hypervisor.HypervisorManagers.H_CPUManager.IH_CPUManager;

simple H_CPU_SCHED_RR like IH_CPUManager
{
    parameters:
        int numCPUs;
        double computingOverhead = default(0);
        double timeslice = default(2);
    gates:
        input fromVMCPU[];
        output toVMCPU[];

        input fromNodeCPU[numCPUs];
        output toNodeCPU[numCPUs];
}
