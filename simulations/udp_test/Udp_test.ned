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

package icancloud.simulations.udp_test;

import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;

import inet.nodes.inet.Router;
import inet.nodes.inet.StandardHost;
import ned.DatarateChannel;

network Udp_test
{
    @display("bgb=504,295");
    types:
        channel Channel extends DatarateChannel
        {
            datarate = 100Mbps;
            delay = 0.1us;
        }

    submodules:
        configurator: IPv4NetworkConfigurator {
            parameters:
                @display("p=40,40");
        }

        server: StandardHost {
            parameters:
                @display("p=339,50;i=device/pc2");
        }

        router: Router {
            parameters:
                @display("p=276,135");
        }

        client1: StandardHost {
            parameters:
                @display("p=40,160;i=device/pc3");
        }
        client2: StandardHost {
            parameters:
                @display("p=339,265;i=device/pc3");
        }

    connections:
        server.ethg++ <--> Channel <--> router.ethg++;
        client1.ethg++ <--> Channel <--> router.ethg++;
        client2.ethg++ <--> Channel <--> router.ethg++;
}
