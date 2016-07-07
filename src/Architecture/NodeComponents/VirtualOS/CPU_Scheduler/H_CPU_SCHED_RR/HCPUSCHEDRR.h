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

#ifndef HCPUSCHEDRR_H_
#define HCPUSCHEDRR_H_

#include "H_CPUManager_Base.h"
class H_CPU_SCHED_RR : public H_CPUManager_Base{

    protected:

    /** Array to show the ID of VM executing in the core 'i'*/
    vector<int> vmIDs;

    /** Queue of messages trying to access to a core */
    vector<icancloud_Message*> coreQueue;



public:
    H_CPU_SCHED_RR();
    virtual ~H_CPU_SCHED_RR();

    /*
        * Module initialization
        */
       void initialize();

       /*
        * Module finalization
        */
       void finish();

       /*
        * Scheduler RR
        */
       void schedulingCPU(icancloud_Message *msg);

       /**
       * Process a response message.
       * @param sm Request message.
       */
       void processHardwareResponse(icancloud_Message *msg);






};

#endif /* HCPUSCHEDRR_H_ */
