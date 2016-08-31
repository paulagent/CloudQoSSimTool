// Module that represents a Generic Network Service.
//
// @author Alberto N&uacute;&ntilde;ez Covarrubias
// @date 2010-11-30

package icancloud.src.Virtualization.Hypervisor.HypervisorManagers.H_NetworkManager.NetworkServices;

moduleinterface INetworkService

{
    parameters:
        string localIP;						// Local IP address

    gates:
        input fromNetManager;				// Input gate from Service Redirector
        input fromNetTCP;	
        input fromTCPapp;				// Input gate from Network (TCP)

        output toNetManager;				// Output gate to Service Redirector
        output toNetTCP;
        output toTCPapp;					// Output gate to Network (TCP)

}
