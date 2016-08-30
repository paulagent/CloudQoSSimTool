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

#ifndef ABSTRACTUSERGENERATOR_H_
#define ABSTRACTUSERGENERATOR_H_

#include "icancloud_types.h"
#include "AbstractCloudUser.h"
#include "UserJob.h"

#include "icancloud_Base.h"
#include "UserManagement.h"

class UserJob;
class UserManagement;

#define DEBUG false 

class AbstractUserGenerator : virtual public icancloud_Base{

protected:

	// Main user parameters
		string name;                                           /** id name of the users*/
		int users_created_counter;                             /** count to build the user name*/
		string behavior;                                       /** kind of user that define his behavior*/

        string distributionName;                               /** distribution which defines the user appearance at the cloud system */
        vector<double> distributionParams;

        // vm selected by user
        struct vmSelection{
            string vmtype;                          //Type VM (TypeVMID)
            int quantity;                           //Quantity
        };
        vector <vmSelection*> vmSelect;
        // vm selected by user
        struct dockerSelection{
            string dockertype;                          //Type VM (TypeVMID)
            int quantity;                           //Quantity
        };

        // Structure of docker container of a user
            vector <dockerSelection*> dockerSelect;
//
        // vm selected by user
        struct jobSelection{
            string appName;                         // Application Name
            UserJob* job;                          // Job definition
            int replicas;                           // Quantity
        };

        // Structures of jobs of user
            vector <jobSelection*> userJobSet;

            // container selected by user
               struct containerSelection{
                   string appName;                         // Application Name
                   UserJob* job;                          // Job definition
                   int replicas;                           // Quantity
               };

               // Structures of jobs of user
                   vector <containerSelection*> userContainerSet;


	// To create the remote servers
		string remoteFileSystemType;

    // Pointer to cloud manager
		UserManagement *userManagementPtr;

    // Log name
        string logName;

        bool printResults;

        /** Output File directory */
        static const string OUTPUT_DIRECTORY;



    AbstractUserGenerator();

	virtual void initialize();

   /**
	* Module ending.
	*/
	virtual void finish();

   /**
	* Process a request message.
	* @param sm Request message.
	*/
	virtual void processRequestMessage (icancloud_Message *sm){};

   /**
	* Process a response message.
	* @param sm Request message.
	*/
	virtual void processResponseMessage (icancloud_Message *sm){};

   /**
    * Get the out Gate to the module that sent <b>msg</b>.
    * @param msg Arrived message.
    * @return Gate (out) to module that sent <b>msg</b> or NULL if gate not found.
    */
    cGate* getOutGate (cMessage *msg);

  /**
   * Process a self message.
   * @param msg Self message.
   */
   virtual void processSelfMessage (cMessage *msg){};

   /*
    * If allowToExecute = true means that the execution will be performed until the last user finish
    * allowToExecute = false means that the execution has finished the time and it is forced to finish
    */
    void finalizeUserGenerator(bool allowToExecute);


    /*
       * This function will create user based on configuration. Then it will assign jobs to this user. the job number(number of
       * request) will attract from INI file (already add to userJobSet vector).
       *
       */

	void createUser ();

	double selectDistribution();

    virtual void userCreateGroups(int intervals, int nusers) = 0;

    UserJob* ConvertApptoUser(cModule* auxMod);

private:
    UserJob* cloneJob (UserJob* app, cModule* userMod, string appName);

public:
    virtual ~AbstractUserGenerator();
};

#endif /* USERGENERATOR_H_ */


