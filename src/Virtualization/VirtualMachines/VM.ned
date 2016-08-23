//
// This class defines a generic Virtual Machine
//
// A virtual machie is defined to iCanCloud simulator as a type of machine without physical resources.
// The physical resources are managed by hypervisor and the virtual machine is linked to the hypervisor in order
// to perform those tasks.
// The main parameters that define a virtual machine are:
//		- numCores
//		- memorySize_MB
//		- storageSize_GB
//
// @author Gabriel Gonz&aacute;lez Casta&ntilde;&eacute
// @date 2012-10-23
//

package icancloud.src.Virtualization.VirtualMachines;

import icancloud.src.Virtualization.VirtualMachines.IVM;
import inet.applications.ITCPApp;
import inet.applications.tcpapp.TCPSessionApp;


module VM like IVM
{
    parameters:

        int numCores;												// Number of CPUs
        double memorySize_MB;										// Amount of memory in MiB
        int storageSize_GB;											// Amount of storage in GiB

        int numStorageSystems = default(1);							// Number of Block Servers     
        int numNetworkInterfaces = default(1);						// Number of network interfaces

        string hostName = default("");								// Node's hostname
        string osModuleType = default("VmOperatingSystemModule");  	// Operating System Module type            	
        string cpuModuleType = default("CPU_Module");				// CPU Module type               

        string ip = default("");								    // VM IP
        bool IPForward = default(false);							// IP Forward
        int namid = default(-1);									// Nam ID
        string routingFile = default("");							// Routing File
   //     int numTcpApps = default(1);

        @dynamic(true);
        @class("VM");
        @display("i=old/telnet;bgb=520,405");

    gates:
        //Storage system
        input fromNodeStorageSystem[numStorageSystems] @loose;
        output toNodeStorageSystem[numStorageSystems] @loose;

        //cpu        
        input fromNodeCPU[numCores] @loose;
        output toNodeCPU[numCores] @loose;

		//memory
        input fromNodeMemoryI @loose;
        input fromNodeMemoryO @loose;
        output toNodeMemoryI @loose;
        output toNodeMemoryO @loose;

        // network 
        input fromNodeNet @loose;
        output toNodeNet @loose;

        // to docker
        input fromDaemon @loose;
        output toDaemon @loose;

    submodules:

       
    connections allowunconnected:
}
