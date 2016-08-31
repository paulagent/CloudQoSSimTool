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

package icancloud.simulations.TCP_NodeVL;
import icancloud.src.Architecture.Aggregation.Rack;
import inet.nodes.inet.Router;
import inet.world.httptools.HttpController;
import ned.DatarateChannel;
import inet.nodes.ethernet.EtherSwitch;
import icancloud.src.Architecture.Node.NodeVL.NodeVL;
import icancloud.src.Management.CloudManagement.ResourcesProvisioning.**.*;
import icancloud.src.Management.NetworkManager.NetworkManager;
import icancloud.src.Management.Topology.Topology;
import icancloud.src.Management.NetworkManager.NetworkManager;
import icancloud.src.Users.UserGenerator.UserGenerator;
import icancloud.src.Virtualization.VirtualMachines.SetDefinition.VmSet;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import icancloud.src.Architecture.Node.Node.Node;
// ---------------------------------------------------------------
//   Definition of channels
// ---------------------------------------------------------------
channel Channel_0_TCP_NodeVL extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;
    ber = 0.0;
    per = 0.0;
}

channel Channel_1_TCP_NodeVL extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;
    ber = 0.0;
    per = 0.0;
}

channel RackChannel_0_TCP_NodeVL extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;// RackChannelBandwidth
    ber = 0.0;
    per = 0.0;
}

//
// TODO Auto-generated network
//
network TCP_NodeVL
{
    @display("bgb=1010,450");
    submodules:


        // ---------------------------------------------------------------
        //   Network configurator
        // ---------------------------------------------------------------
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='*' address='192.168.3.x' netmask='255.255.x.x'/></config>");
                @display("p=689,48");
        }
        //<interface hosts='rc_0_Rack_A_16*' address='192.168.0.x' netmask='255.255.255.252'/><interface hosts='rc_0_Rack_B_16*' address='192.168.1.x' netmask='255.255.255.252'/>
        // ---------------------------------------------------------------
        //    Network Manager
        // ---------------------------------------------------------------
        networkManager: NetworkManager {
            @display("p=689,171");
        }
        // ---------------------------------------------------------------
        //   Definition of cloud scheduler
        // ---------------------------------------------------------------
        manager: CloudSchedulerRR {
            parameters:
                numberOfPFSRemoteServers = 2;
                remote_storage_VMs_per_node = 2;
                minimum_percent_storageNode_free = 0.15;
                virtualIPsBasis = "10.0.0.1";
                @display("p=558,171");
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
        //        switch_0: EtherSwitch {
        //            @display("p=198,329");
        //        }
        //        rackSwitch_0: EtherSwitch {
        //            @display("p=97,144");
        //        }
        //        rackSwitch_1: EtherSwitch {
        //            @display("p=294,144");
        //        }
        //        // ---------------------------------------------------------------
        //   Definition of Computing Nodes
        // ---------------------------------------------------------------
        // ---------------------------------------------------------------
        //   Definition of Storage Nodes
        // ---------------------------------------------------------------
        ns_0_NodeStorage_C: NodeVL {
            @display("p=188,363");
        }
        //------------------------------------------------------
        // Modules that defines the topology and the set of VMs 
        //------------------------------------------------------
        vmSet: VmSet {
            @display("p=436,357");
        }
        topology: Topology {
            @display("p=513,363");
        }
        rc_0_Rack_A_16[1]: NodeVL {
            @display("p=75,48");
        }
        rc_1_Rack_B_16[1]: NodeVL {
            @display("p=335,48");
        }
        router: Router {
            @display("p=113,171");
        }
        router1: Router {
            @display("p=249,175");
        }
        router2: Router {
            @display("p=188,261");
        }
    // ---------------------------------------------------------------
    //   Connections section
    // ---------------------------------------------------------------
    connections allowunconnected:

        // Connections for rack rc_0_Rack_A_16
        
            rc_0_Rack_A_16[0].pppg++ <--> RackChannel_0_TCP_NodeVL <--> router.pppg++;
        
        
            rc_1_Rack_B_16[0].pppg++ <--> RackChannel_0_TCP_NodeVL <--> router1.pppg++;
        

        router.pppg++ <--> Channel_0_TCP_NodeVL <--> router2.pppg++;
        router2.pppg++ <--> Channel_0_TCP_NodeVL <--> ns_0_NodeStorage_C.pppg++;
  
        router1.pppg++ <--> Channel_1_TCP_NodeVL <--> router2.pppg++;
        router2.pppg++ <--> Channel_1_TCP_NodeVL <--> ns_0_NodeStorage_C.pppg++;
}
