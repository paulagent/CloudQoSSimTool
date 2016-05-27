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

package icancloud.simulations.Final_TCP;
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
import inet.util.NetAnimTrace;
import inet.world.httptools.HttpController;
import inet.nodes.inet.Router;



//
// TODO Auto-generated network
//
network Final_TCP
{
    parameters:

        // Channel 1 parameters (to be redefined in .ini file)
        double C1_datarate @unit(bps) = default(2Mbps);
        double C1_delay @unit(s) = default(0.1us);
        double C1_per = default(0);
        double C1_ber = default(0);

        // Channel 2 parameters (to be redefined in .ini file)
        double C2_datarate @unit(bps) = default(4Mbps);
        double C2_delay @unit(s) = default(0.1us);
        double C2_per = default(0);
        double C2_ber = default(0);

        // Channel 3 parameters (to be redefined in .ini file)
        double C3_datarate @unit(bps) = default(4Mbps);
        double C3_delay @unit(s) = default(0.1us);
        double C3_per = default(0);
        double C3_ber = default(0);

        @display("bgb=802,414");
    types:
        channel C1 extends DatarateChannel
        {
            datarate = C1_datarate;
            delay = C1_delay;
            per = C1_per;
            ber = C1_ber;
        }
        channel C2 extends DatarateChannel
        {
            datarate = C2_datarate;
            delay = C2_delay;
            per = C2_per;
            ber = C2_ber;
        }
        channel C3 extends DatarateChannel
        {
            datarate = C3_datarate;
            delay = C3_delay;
            per = C3_per;
            ber = C3_ber;
        }




    // -------------------------------------------------------
    //   Definition of main modules
    // -------------------------------------------------------
    submodules:


        // ---------------------------------------------------------------
        //   Network configurator
        // ---------------------------------------------------------------
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='**' address='192.168.x.x' netmask='255.x.x.x'/></config>");
                @display("p=495,67");
        }
        netAnimTrace: NetAnimTrace {
            parameters:
                @display("p=250,34");
        }
        controller: HttpController {
            parameters:
                @display("p=320,34;i=block/cogwheel_s");
        }


        // ---------------------------------------------------------------
        //    Network Manager
        // ---------------------------------------------------------------
        networkManager: NetworkManager;
        // ---------------------------------------------------------------
        //   Definition of cloud scheduler
        // ---------------------------------------------------------------
        manager: CloudSchedulerRR {
            parameters:
                numberOfPFSRemoteServers = 2;
                remote_storage_VMs_per_node = 2;
                minimum_percent_storageNode_free = 0.15;
                virtualIPsBasis = "10.0.0.1";
                @display("p=397,164");
        }

        // ---------------------------------------------------------------
        //   Definition of user generator
        // ---------------------------------------------------------------
        userGenerator: UserGenerator {
            parameters:
                numCells = 1;
                @display("p=397,277");
        }

        // ---------------------------------------------------------------
        //   Definition of switches
        // ---------------------------------------------------------------
        switch_0: EtherSwitch;
        rackSwitch_0: EtherSwitch {
            @display("p=241,117");
        }

        // ---------------------------------------------------------------
        //   Definition of Computing Nodes
        // ---------------------------------------------------------------
        // ---------------------------------------------------------------
        //   Definition of Storage Nodes
        // ---------------------------------------------------------------
        server1: NodeVL {
            @display("p=165,251");
        }
        server2: NodeVL {
            @display("p=330,230");
        }
        //------------------------------------------------------
        // Modules that defines the topology and the set of VMs 
        //------------------------------------------------------
        vmSet: VmSet;
        topology: Topology;
        // ---------------------------------------------------------------
        //   Definition of Racks
        // ---------------------------------------------------------------
        client1[1]: NodeVL {

            @display("p=279,45");
        }
        client2[1]: NodeVL {

            @display("p=128,31");
        }
        client3[1]: NodeVL {

            @display("p=78,118");
        }

        router1: Router {
            parameters:
                @display("p=144,174");
        }
    // ---------------------------------------------------------------
    //   Connections section
    // ---------------------------------------------------------------
    connections allowunconnected:

        // Connections for rack rc_0_Rack_A_16
        //   for i=0..5 {
        client1[0].ethg++ <--> C1 <--> rackSwitch_0.ethg++;
        client2[0].ethg++ <--> C1 <--> rackSwitch_0.ethg++;
        client3[0].ethg++ <--> C1 <--> rackSwitch_0.ethg++;
    //    }

		rackSwitch_0.ethg++ <--> C2 <--> router1.ethg++;
		router1.ethg++ <--> C2 <--> switch_0.ethg++;
        
        server1.ethg++ <--> C3 <--> switch_0.ethg++;
        server2.ethg++ <--> C3 <--> switch_0.ethg++;

}


