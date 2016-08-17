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

package icancloud.simulations.TCP_test;
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



//
// TODO Auto-generated network
//
channel Channel_0 extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;
    ber = 0.0;
    per = 0.0;
}

channel Channel_1 extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;
    ber = 0.0;
    per = 0.0;
}

channel RackChannel_0 extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;// RackChannelBandwidth
    ber = 0.0;
    per = 0.0;
}


//        channel Channel_0 extends DatarateChannel
//        {
//            datarate = Channel_0_datarate;
//            delay = Channel_0_delay;
//            per = Channel_0_per;
//            ber = Channel_0_ber;
//        }
//        channel Channel_1 extends DatarateChannel
//        {
//            datarate = Channel_1_datarate;
//            delay = Channel_1_delay;
//            per = Channel_1_per;
//            ber = Channel_1_ber;
//        }
//        channel RackChannel_0 extends DatarateChannel
//        {
//            datarate = RackChannel_0_datarate;
//            delay = RackChannel_0_delay;
//            per = RackChannel_0_per;
//            ber = RackChannel_0_ber;
//        }

network TCP_test
{
    parameters:

        // Channel 1 parameters (to be redefined in .ini file)
//        double Channel_0_datarate @unit(bps) = default(10Gbps);
//        double Channel_0_delay @unit(s) = default(1.25E-4us);
//        double Channel_0_per = default(0);
//        double Channel_0_ber = default(0);
//
//        // Channel 2 parameters (to be redefined in .ini file)
//        double Channel_1_datarate @unit(bps) = default(10Gbps);
//        double Channel_1_delay @unit(s) = default(1.25E-4us);
//        double Channel_1_per = default(0);
//        double Channel_1_ber = default(0);
//
//        // Channel 3 parameters (to be redefined in .ini file)
//        double RackChannel_0_datarate @unit(bps) = default(10Gbps);
//        double RackChannel_0_delay @unit(s) = default(1.25E-4us);
//        double RackChannel_0_per = default(0);
//        double RackChannel_0_ber = default(0);
    
    @display("bgb=721,443");
    
        
        submodules:


        // ---------------------------------------------------------------
        //   Network configurator
        // ---------------------------------------------------------------
        configurator: IPv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='**' address='192.168.x.x' netmask='255.x.x.x'/></config>");
                @display("p=519,37");
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
                @display("p=473,142");
        }

        // ---------------------------------------------------------------
        //   Definition of user generator
        // ---------------------------------------------------------------
        userGenerator: UserGenerator {
            parameters:
                numCells = 1;
                @display("p=537,223");
        }

        // ---------------------------------------------------------------
        //   Definition of switches
        // ---------------------------------------------------------------
        switch_0: EtherSwitch {
            @display("p=232,297");
        }
        rackSwitch_0: EtherSwitch {
            @display("p=232,204");
        }

        // ---------------------------------------------------------------
        //   Definition of Computing Nodes
        // ---------------------------------------------------------------
        // ---------------------------------------------------------------
        //   Definition of Storage Nodes
        // ---------------------------------------------------------------
        server1: NodeVL {
            @display("p=105,377");
        }
        server2: NodeVL {
            @display("p=367,377");
        }
        //------------------------------------------------------
        // Modules that defines the topology and the set of VMs 
        //------------------------------------------------------
        vmSet: VmSet {
            @display("p=458,291");
        }
        topology: Topology;
        // ---------------------------------------------------------------
        //   Definition of Racks
        // ---------------------------------------------------------------
        client1[1]: NodeVL {

            @display("p=56,119");
        }
        client2[1]: NodeVL {

            @display("p=133,55");
        }
        client3[1]: NodeVL {

            @display("p=257,55");
        }
        client4[1]: NodeVL {

            @display("p=351,119");
        }
//        netAnimTrace: NetAnimTrace {
//            parameters:
//                @display("p=413,67");
//        }
        controller: HttpController {
            parameters:
                @display("p=622,161;i=block/cogwheel_s");
        }

    connections allowunconnected:
        rackSwitch_0.ethg++ <--> RackChannel_0 <--> client1[0].ethg++;
        rackSwitch_0.ethg++ <--> RackChannel_0 <--> client2[0].ethg++;
        rackSwitch_0.ethg++ <--> RackChannel_0 <--> client3[0].ethg++;
        rackSwitch_0.ethg++ <--> RackChannel_0 <--> client4[0].ethg++;

        rackSwitch_0.ethg++ <--> Channel_0 <--> switch_0.ethg++;
        switch_0.ethg++ <--> Channel_1 <--> server1.ethg++;
        switch_0.ethg++ <--> Channel_1 <--> server2.ethg++; 
}
