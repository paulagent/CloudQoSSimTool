//
// Module interface that represents a cloud scheduler
//
// @authors Gabriel Gonz&aacute;lez Casta&ntilde;&eacute
// @date 2014-12-11

package icancloud.src.Virtualization.VirtualMachines.VMRequestManager.ResourcesProvisioning;

moduleinterface IDockerScheduler
{
   parameters:
        
		string virtualIPsBasis; 					// The virtual ip that the cloud will give to the VMs. It will be increased by 1 each new VM.					           
		double timeToStart; 						// The time that cloud waits until it starts
       
        int timeBetweenScheduleEvents_s;			// Time until the scheduler is activated again 
        double timeBetweenLogResults_s;				// Time between all data center is checked extracting the energy measurements.
    
       
        int numberOfDockerperVM;						// The maximum number of virtual machines into a node
      
}

