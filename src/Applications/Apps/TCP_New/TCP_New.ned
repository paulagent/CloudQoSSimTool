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

package icancloud.src.Applications.Apps.TCP_New;

import icancloud.src.Applications.Apps.IAPP;

simple TCP_New like IAPP
{
    parameters:
        string application_netType = default ("INET");
      //  string localIP;
        double startDelay;									// Starting delay time!        
        int inputSize;										// Input size of data
        int outputSize;										// Output size of data
        int MIs;											// Number of MIs to execute
        int iterations = default (0);						// Number of iterations
        @display("i=msg/job");
        
        gates:
        input fromNetManager @loose;	
        input fromNetTCP @loose;	
        input fromOS @loose;	
        
        output toNetManager @loose;	
        output toNetTCP @loose;	 
        output toOS @loose;	
        
}
