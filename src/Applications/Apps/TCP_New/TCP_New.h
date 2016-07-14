/*
 * TCP_New.h
 *
 *  Created on: Jul 13, 2016
 *      Author: nishant
 */

#ifndef TCP_NEW_H_
#define TCP_NEW_H_

#include <omnetpp.h>
#include "TCPSocket.h"
#include "IPvXAddressResolver.h"
#include "TCPSocketMap.h"
#include "NetworkService.h"
//#include "icancloud_Message.h"
#include "INETDefs.h"
#include "icancloud_App_NET_Message.h"

class NetworkService;

class TCP_New : public TCPSocket::CallbackInterface{

    struct icancloud_TCP_Client_Connector{
            TCPSocket *socket;
            cPacket *msg;
        };
        typedef struct icancloud_TCP_Client_Connector clientTCP_Connector;

protected:

        /** Client connections vector*/
        vector <clientTCP_Connector> connections;

        /** Socket map to manage TCP sockets*/
        TCPSocketMap socketMap;

        /** Pointer to NetworkService object */
        NetworkService *networkService;

        /** Local IP */
        string localIP;

        /** Output gate to TCP */
        cGate* outGate_TCP;

public:
        TCP_New(string newLocalIP, cGate* toTCP, NetworkService *netService);

        virtual ~TCP_New();

        void createConnection(icancloud_App_NET_Message *sm_net);

        void sendPacketToServer(icancloud_App_NET_Message *sm_net);

        void closeConnection(icancloud_App_NET_Message *sm_net);

        int searchConnectionByConnId(int connId);

        TCPSocket* getInvolvedSocket (cMessage *msg);

protected:

        virtual void socketEstablished(int connId, void *yourPtr);
        virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);
        virtual void socketPeerClosed(int connId, void *yourPtr);
        virtual void socketClosed(int connId, void *yourPtr);
        virtual void socketFailure(int connId, void *yourPtr, int code);
        virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status;}
};



#endif /* TCP_NEW_H_ */
