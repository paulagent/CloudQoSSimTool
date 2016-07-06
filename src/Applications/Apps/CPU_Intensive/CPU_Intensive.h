#ifndef __CPU_INTENSIVE_H_
#define __CPU_INTENSIVE_H_

#include <omnetpp.h>
#include "UserJob.h"

#include "TCPSocket.h"
#include "IPvXAddressResolver.h"
#include "TCPSocketMap.h"
#include "NetworkService.h"
#include "icancloud_Message.h"

/**
 * @class CPU_Intensive CPU_Intensive.h "CPU_Intensive.h"
 *
 * Example of a sequential application without traces.
 * This application alternates I/O operations with CPU.
 *
 * This module needs the following NED parameters:
 *
 * - startDelay (Starting delay time)
 * 
 * @author Alberto N&uacute;&ntilde;ez Covarrubias
 * @date 2009-03-13
 *
 * @author updated to iCanCloud by Gabriel González Castañé
 * @date 2013-12-17
 *
 */
class CPU_Intensive : public UserJob{

    //changes for TCP
    struct icancloud_TCP_Client_Connector{
            TCPSocket *socket;
            cPacket *msg;
        };
        typedef struct icancloud_TCP_Client_Connector clientTCP_Connector;

    struct icancloud_TCP_Server_Connector{
                int port;
                int appIndex;
            };
            typedef struct icancloud_TCP_Server_Connector serverTCP_Connector; //changes for TCP end

	
	protected:

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

		/** Simulation Starting timestamp */
		simtime_t simStartTime;

		/** Simulation Ending timestamp */
		simtime_t simEndTime;
		
		/** Running starting timestamp */
		time_t runStartTime;

		/** Running ending timestamp */
		time_t runEndTime;		
				
		/** Call Starting timestamp (IO) */
		simtime_t startServiceIO;
		
		/** Call Ending timestamp (IO) */
		simtime_t endServiceIO;
		
		/** Call Starting timestamp (CPU) */
		simtime_t startServiceCPU;
		
		/** Call Ending timestamp (CPU) */
		simtime_t endServiceCPU;
		
		/** Spent time in CPU system */
		simtime_t total_service_CPU;
		
		/** Spent time in IO system */
		simtime_t total_service_IO;
				
		/** Execute CPU */
		bool executeCPU;
		
		/** Execute read operation */
		bool executeRead;
				
		/** Execute write operation */
		bool executeWrite;
		
		/** Read Offset */
		int readOffset;

		/** Write Offset */
		int writeOffset;
				
								
		
	   /**
		* Destructor
		*/
		~CPU_Intensive();

	   /**
 		*  Module initialization.
 		*/
	    virtual void initialize();

	   /**
 		* Module ending.
 		*/
	    virtual void finish();

        /**
         * Start the app execution.
         */
        virtual void startExecution ();

	   /**
		* Process a self message.
		* @param msg Self message.
		*/
		void processSelfMessage (cMessage *msg);

	   /**
		* Process a request message.
		* @param sm Request message.
		*/
		void processRequestMessage (icancloud_Message *sm);

		/**
		* Process a message from the cloudManager or the scheduler...
		* @param sm message.
		*/
		void processSchedulingMessage (cMessage *msg);

	   /**
		* Process a response message.
		* @param sm Request message.
		*/
		void processResponseMessage (icancloud_Message *sm);


		void changeState(string newState);

		//changes for tcp
        /** Client connections vector*/
        vector <clientTCP_Connector> connections;

        /** Socket map to manage TCP sockets*/
        TCPSocketMap socketMap;

        /** Pointer to NetworkService object */
        NetworkService *networkService;

        /** Local IP */
        string localIP;

        /** Output gate to TCP */
        cGate* outGate_TCP; //changes tcp

	public:

        //new functions for tcp
		void createConnection(icancloud_Message *sm);

		void sendPacketToServer(icancloud_Message *sm);

		int searchConnectionByConnId(int connId);

		void closeConnection(icancloud_Message *sm);


	private:			    

	   /**
		* Method that creates and sends a new I/O request.
		* @param executeRead Executes a read operation
		* @param executeWrite Executes a write operation
		*/
		void executeIOrequest(bool executeRead, bool executeWrite);		

	   /**
		* Method that creates and sends a CPU request.
		*/
		void executeCPUrequest();

	   /**
		* Print results.
		*/
		void printResults();

};

#endif
