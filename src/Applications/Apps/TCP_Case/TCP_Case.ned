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

package icancloud.src.Applications.Apps.TCP_Case;

//import inet.applications.IAPP;
import icancloud.src.Applications.Apps.IAPP;

simple TCP_Case like IAPP
{
    parameters:
        // General parameters
        string 			localAddress = default(""); // may be left empty ("")
        int 			localPort = default(-1); // port number to listen on
        string 			connectAddress = default("");  // server address (may be symbolic)
        int 			connectPort = default(1000); // port number to connect to
        string 			dataTransferMode @enum("bytecount","object","bytestream") = default("bytecount");
        volatile double video_startTime @unit(s) = default(1s); // time first session begins
        double 			stopTime @unit(s) = default(0);  // time of finish sending, 0 means infinity
        volatile int 	requestLength @unit(B) = default(200B); // length of a request
        volatile double reconnectInterval @unit(s) = default(10s);  // if connection breaks, waits this much before trying to reconnect
        
        // Adaptive Video parameters
        string 			video_packet_size_per_second @units(kbps)= default("1000 1500 2000 4000 8000 12000"); // how many kbits are required for 1 second of video for each representation (quality levels)
        int 			manifest_size @units(byte) = default(100000);
        int 			video_buffer_max_length @units(s) = default(10); // buffer max length in seconds
        int 			video_duration @units(s) = default(30); // video length in seconds
        
        // General statistics
        @display("i=block/app");
        @signal[sentPk](type=cPacket);
        @signal[rcvdPk](type=cPacket);
        @signal[connect](type=long);  // 1 for open, -1 for close
        @statistic[rcvdPk](title="packets received"; source=rcvdPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[sentPk](title="packets sent"; source=sentPk; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="messageAge(rcvdPk)"; unit=s; record=histogram,vector; interpolationmode=none);
        @statistic[numActiveSessions](title="number of active sessions"; source="sum(connect)"; record=max,timeavg,vector; interpolationmode=sample-hold);
        @statistic[numSessions](title="total number of sessions"; source="sum(connect+1)/2"; record=last);
        
        // Adaptive Video statistics
        @signal[DASHBufferLength](type="int");
        @statistic[DASHBufferLength](title="Video buffer length (in seconds)"; record=vector);
        @signal[DASHQualityLevel](type="int");
        @statistic[DASHQualityLevel](title="Requested quality level"; record=vector);
        @signal[DASHVideoPlaybackPointer](type="int");
        @statistic[DASHVideoPlaybackPointer](title="Video playback pointer"; record=vector);
        @signal[DASHVideoPlaybackStatus](type="bool");
        @statistic[DASHVideoPlaybackStatus](title="Video playback status (playing=1, buffering=0)"; record=vector);
        
    gates:
       // input tcpIn @labels(TCPCommand/up);
      //  output tcpOut @labels(TCPCommand/down);
        input fromOS @loose;
        output toOS @loose;
}

