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

package icancloud.simulations.TCP_IP;
import ned.DatarateChannel;
import inet.nodes.ethernet.EtherSwitch;
import icancloud.src.Architecture.Node.NodeVL.NodeVL;
import icancloud.src.Management.CloudManagement.ResourcesProvisioning.**.*;

import icancloud.src.Management.Topology.Topology;
import icancloud.src.Management.NetworkManager.NetworkManager;
import icancloud.src.Users.UserGenerator.UserGenerator;
import icancloud.src.Virtualization.VirtualMachines.SetDefinition.VmSet;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;

//
// TODO Auto-generated network

channel Channel_0_Cloud_A extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;
    ber = 0.0;
    per = 0.0;
}

channel Channel_1_Cloud_A extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;
    ber = 0.0;
    per = 0.0;
}

channel RackChannel_0_Cloud_A extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;// RackChannelBandwidth
    ber = 0.0;
    per = 0.0;
}


network TCP_IP
{
    submodules:


        // ---------------------------------------------------------------
        //   Network configurator
        // ---------------------------------------------------------------
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='**' address='192.168.x.x' netmask='255.x.x.x'/></config>");
        }

        // ---------------------------------------------------------------
        //    Network Manager
        // ---------------------------------------------------------------
        networkManager: NetworkManager {
            @display("p=458,56");
        }
        // ---------------------------------------------------------------
        //   Definition of cloud scheduler
        // ---------------------------------------------------------------
        manager: CloudSchedulerFCFS {
            parameters:
                numberOfPFSRemoteServers = 2;
                remote_storage_VMs_per_node = 2;
                minimum_percent_storageNode_free = 0.15;
                virtualIPsBasis = "10.0.0.1";
        }

        // ---------------------------------------------------------------
        //   Definition of user generator
        // ---------------------------------------------------------------
        userGenerator: UserGenerator {
            parameters:
                numCells = 1;
        }

        // ---------------------------------------------------------------
        //   Definition of switches
        // ---------------------------------------------------------------
        switch_0: EtherSwitch;
        rackSwitch_0: EtherSwitch;
        // ---------------------------------------------------------------
        //   Definition of Computing Nodes
        // ---------------------------------------------------------------
        // ---------------------------------------------------------------
        //   Definition of Storage Nodes
        // ---------------------------------------------------------------
        ns_0_NodeStorage_C: NodeVL;
        //------------------------------------------------------
        // Modules that defines the topology and the set of VMs 
        //------------------------------------------------------
        vmSet: VmSet;
        topology: Topology;
        rc_0_Rack_A_16[16]: NodeVL {
            @display("p=88,56");
        }
        rc_1_Rack_A_16[16]: NodeVL {
            @display("p=253,56");
        }
    // ---------------------------------------------------------------
    //   Connections section
    // ---------------------------------------------------------------
    connections allowunconnected:

        // Connections for rack rc_0_Rack_A_16
        for i=0..15 {
            rc_0_Rack_A_16[i].ethg++ <--> RackChannel_0_Cloud_A <--> rackSwitch_0.ethg++;
        }
        for i=0..15 {
            rc_1_Rack_A_16[i].ethg++ <--> RackChannel_0_Cloud_A <--> rackSwitch_0.ethg++;
        }
        rackSwitch_0.ethg++ <--> Channel_0_Cloud_A <--> switch_0.ethg++;
        ns_0_NodeStorage_C.ethg++ <--> Channel_1_Cloud_A <--> switch_0.ethg++;
}

