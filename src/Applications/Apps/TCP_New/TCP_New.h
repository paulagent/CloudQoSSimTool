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
#include "icancloud_Message.h"
#include "INETDefs.h"
#include "icancloud_App_NET_Message.h"

class NetworkService;

class UserJob;

class TCP_New : public TCPSocket::CallbackInterface, public cSimpleModule{

    struct icancloud_TCP_Client_Connector{
            TCPSocket *socket;
            cPacket *msg;
        };
        typedef struct icancloud_TCP_Client_Connector clientTCP_Connector;

    struct icancloud_TCP_Server_Connector{
               int port;
               int appIndex;
           };
           typedef struct icancloud_TCP_Server_Connector serverTCP_Connector;


protected:

        /** Client connections vector*/
        vector <clientTCP_Connector> connections;

        vector <serverTCP_Connector> connection;

        /** Socket map to manage TCP sockets*/
        TCPSocketMap socketMap;

        /** Pointer to NetworkService object */
        NetworkService *networkService;

        /** Local IP */
        string localIP;

        /** Output gate to TCP */
        cGate* outGate_TCP;

        cGate* outGate_icancloudAPI;

        simtime_t simStartTime;
                simtime_t simEndTime;
                time_t runStartTime;
                time_t runEndTime;

                simtime_t startServiceCPU;
                simtime_t endServiceCPU;
                simtime_t total_service_CPU;

                simsignal_t processingTime;
                simtime_t departureTime;
                simtime_t arrivalTime;

                    /** Size of data chunk to read in each iteration */
                    int inputSizeMB;

                    /** Size of data chunk to write in each iteration */
                    int outputSizeMB;

                    /** Number of Instructions to execute */
                    int MIs;

                    /** Number of iterations */
                    unsigned int currentIteration;

                    /** Total iterations */
                    unsigned int iterations;

                    /** Starting time delay */
                    unsigned int startDelay;

        virtual void initialize();

        virtual void finish();

        virtual void startExecution();

        void processSelfMessage(cMessage *msg);

        void processRequestMessage(icancloud_App_NET_Message *sm_net);

        void processResponseMessage(icancloud_App_NET_Message *sm_net);



public:
        TCP_New(string newLocalIP, cGate* toTCP, NetworkService *netService);

        TCP_New();

        TCP_New(string newLocalIP, cGate* toTCP, cGate* toicancloudAPI, NetworkService *netService);

        virtual ~TCP_New();

        void createConnection(icancloud_Message *sm);

        void sendPacketToServer(icancloud_Message *sm);

        void closeConnection(icancloud_Message *sm);

        int searchConnectionByConnId(int connId);

        TCPSocket* getInvolvedSocket (cMessage *msg);

        void newListenConnection (icancloud_Message *sm);

        void arrivesIncommingConnection (cMessage *msg);

        void sendPacketToClient(icancloud_Message *sm);

        bool existsConnection (int port);

        int getAppIndexFromPort (int port);

        void closeConnectionReceived(cMessage *sm);


protected:

        virtual void socketEstablished(int connId, void *yourPtr);
        virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);
        virtual void socketPeerClosed(int connId, void *yourPtr);
        virtual void socketClosed(int connId, void *yourPtr);
        virtual void socketFailure(int connId, void *yourPtr, int code);
        //virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status;}
};



#endif /* TCP_NEW_H_ */
