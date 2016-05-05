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

import icancloud.src.Architecture.Node.Node.Node;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.nodes.ethernet.EtherSwitch;
import inet.nodes.inet.Router;
import inet.transport.tcp.TCP;
import inet.util.NetAnimTrace;
import ned.DatarateChannel;
import icancloud.src.Management.CloudManagement.ResourcesProvisioning.**.*;
import icancloud.src.Management.NetworkManager.NetworkManager;
import icancloud.src.Management.Topology.Topology;
import icancloud.src.Management.NetworkManager.NetworkManager;
import icancloud.src.Users.UserGenerator.UserGenerator;
import icancloud.src.Virtualization.VirtualMachines.SetDefinition.VmSet;
//
// TODO Auto-generated network
//
channel Channel_1_TCP1 extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;// RackChannelBandwidth
    ber = 0.0;
    per = 0.0;
}

channel Channel_0_TCP1 extends DatarateChannel
{
    delay = 1.25E-4us;
    datarate = 10Gbps;
    ber = 0.0;
    per = 0.0;
}
network TCP_test1
{
    @display("bgb=765,419");
    submodules:
        etherSwitch: EtherSwitch {
            @display("p=270,127");
        }
        etherSwitch1: EtherSwitch {
            @display("p=557,127");
        }
        client[2]: Node {
            @display("p=171,251");
        }
        server[2]: Node {
            @display("p=625,251");
        }
        router: Router {
            @display("p=372,41");
        }
           manager: CloudSchedulerRR {
            parameters:
                numberOfPFSRemoteServers = 2;
                remote_storage_VMs_per_node = 2;
                minimum_percent_storageNode_free = 0.15;
                virtualIPsBasis = "10.0.0.1";
                @display("p=350,170");
        }
         vmSet: VmSet;
        topology: Topology;
        iPv4NetworkConfigurator: IPv4NetworkConfigurator {
            parameters:
                config = xml("<config><interface hosts='**' address='192.168.x.x' netmask='255.x.x.x'/></config>");
                @display("p=171,344");
        }
        netAnimTrace: NetAnimTrace {
            @display("p=507,312");
        }


        userGenerator: UserGenerator {
            parameters:
                numCells = 1;
                @display("p=295,266");
        }


        networkManager: NetworkManager {


            @display("p=84,65");
        }
    connections allowunconnected:
        //  client.ethg++ <--> etherSwitch.ethg++;
        etherSwitch.ethg++ <--> router.ethg++;
        router.ethg++ <--> etherSwitch1.ethg++;
        //  etherSwitch1.ethg++ <--> server.ethg++;
        for i=0..1 {
            client[i].ethg++ <--> Channel_0_TCP <--> etherSwitch.ethg++;

            server[i].ethg++ <--> Channel_1_TCP <--> etherSwitch1.ethg++;
        }
}
