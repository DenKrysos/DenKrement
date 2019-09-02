/*
 * Authored by
 * Dennis Krummacker (14.07.2017 - )
 */


#define NO_DENKREMENT_C_FUNCTIONS


//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
#include "./global/global_settings.h"
#include "./global/global_variables.h"
// Need this for e.g. some really fundamental Program Basics (if any)  ------------
//---------------------------------------------------------------------------------
#include "DenKrement_base.h"
// Then better start with this  ---------------------------------------------------
//---------------------------------------------------------------------------------
#include "DenKrement.h"
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Just to nicely keep order:  -----------------------------------------------------
//   First include the System / Third-Party Headers  ------------------------------
//   Format: Use <NAME> for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include <linux/if.h>
#include <net/if.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <linux/types.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#include <netlink/socket.h>
#include <pthread.h>
//#include <semaphore.h>
//#include <ncurses.h>
#include <time.h>
#include <pcap.h>
#include <signal.h>
#include <malloc.h>
#include <arpa/inet.h>

//#include <netlink/object.h>
//#include <netlink/utils.h>
//#include <netlink/socket.h>
////#include <netlink/route/link.h>
//#include <netlink/cache.h>
//#include <netlink/msg.h>
//#include <netlink/attr.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "auxiliary/support_main.h"
#include "DenKr/DenKr_threads.h"
#include "files/config/DenKrement_cfg_files.h"
#include "plugins/DenKrement_plugins.h"
#include "plugins/export/plugins_export.h"
#include "GUI/GUI_thread.h"
#include "secret/DenKrement_funny.h"
//  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/DenKr_errno.h"
#include "DenKr_essentials/multi_threading.h"
#include "DenKr_essentials/Program_Files/control_cfg_file.h"
#include "DenKr_essentials/plugins/DL_Libs.h"
#include "DenKr_essentials/Context_Broker/context_broker_thread.h"
//#include "nl80211.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//

/* Documentation:
 *   (veeeery incomplete...)
 * - The cfg-File has an entry "GUI_Thread"
 *    -> enabled  -- GUI Threads works completely
 *    -> disabled  -- It immediately terminates, i.e. it is not in use. (Starts no GTK Window at all)
 */




//int main(int argc, char *argv[]) {
int main(int argc, char **argv) {
//	system("reset");
//	system("clear");
	int err=0;
	int i;

		//	//Just funny, not really of any use: ;oP
		//	#include <DenKr_essentials/Terminal/ascii.h>
		//	#include <DenKr_essentials/Terminal/ansi.h>
		//	print_ANSI_Pokemon_Starter_1st_Gen_8Bit();
		//	print_ASCII_Pokemon_Bulbasaur_monochrom();
		//	print_ASCII_ANSI_Pokemon_Bulbasaur();
		//	print_ANSI_Pokemon_Bulbasaur();
		//	exit(1);

	// Set Signal Handler for the User-desired Exit Ctrl-C
	signal(SIGINT, sig_handler_ctrl_c);





	//==================================================================================================//
	//----  "Special" (not production grade) Section, for Demonstration of the Framework  --------------//
	//-- In other words: This shit here can be safely deleted, in case you are changing the Setup
	//==================================================================================================//
	//For Demonstration-purpose of the ability to pass "additional/optional" arguments to Plugins with 'predefined roles', besides the every time passed default ones.
	//  This one's for the Example Plugin "Some_Dummy"
	int testaddArg = 3;
	//====================================================================================================
	//====================================================================================================





	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  As a funny startup.  -----------------------------------------------------------------------//
	//----  Really totally not of any use...  ----------------------------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	{
		CREATE_argv(printf_bulb,"print","pokemon","bulbasaur");
		CREATE_argv(printf_starter,"print","pokemon","starter","1stGen");
		printf("\nOK, at first, here you have Bulbausaur...\n");
		err=Cmd_Line_Mux_funny(3,printf_bulb);
		printf("\nAnd the other starters as well...\n");
		err=Cmd_Line_Mux_funny(4,printf_starter);
		printf("Fine... Now we can start:\n");
		system("clear");
	}





	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Initialization of the DenKr_essentials-Library  --------------------------------------------//
	//----  Enables some Paths, Checks System-Endianess, Terminal ANSI-Escape  -------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	DenKr_essentials_Init(argc, argv);
	#ifdef DENKR_ESSENTIALS_AUXILIARY_H
		printfc(yellow,"Program Name:\n");printf("%s\n",ProgramName);
		printfc(yellow,"Program Path (executable):");printf(" (length: %d)\n%s\n",ProgPath_length,ProgPath);
		printfc(yellow,"Storage Files Path (cfg, log, etc.):\n");printf("%s\n",StorageFilesPath);
	#endif
	printf("\n");





	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Start of the Command-Line Multiplexing  ----------------------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//For now just to intercept some stuff "not really for valuable use", but just additional funny stuff
	//Maybe later on can be extended and the other Code will be integrated; certainly not.
	#ifdef SECRET_DENKREMENT_FUNNY_H
		int argc_proc=argc-1; char **argv_proc=argv+1;
		// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
		if(argc_proc>0){
			if(strcmp(*argv_proc, "funny") == 0){
				#include "secret/DenKrement_funny.h"
				err=Cmd_Line_Mux_funny(--argc_proc,++argv_proc);
				exit(err);
			}else{}
		}else{}
	#endif





	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Config-Files  ------------------------------------------------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//----  Initializes the global char [][] cfg_files_v_gl,
	//----       Checks for the Presence of Config-Files,
	//----       Eventually creates Default-Config-Files, if one doesn't already exist
	//--------------------------------------------------------------------------------------------------//
	// Creates cfg_files_v, usable like argv, with 'DENKREMENT_CFG_FILES_QUANTITY' as max Value
	#define cfg_files_v ((char **)cfg_files_v_)
	create_cfg_files_argv
	//--------------------------------------------------------------------------------------------------//
	// Presence Checking and eventually Default-Creation
	cfg_files_init_and_default(cfg_files_v);
	// Read Config Files
	struct config_main cfg_main;
	cfg_file__main__read_complete(&cfg_main, cfg_files_v);





	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Dynamically Loaded Libraries (DL Lib, DLL, DSO [Dynamic Shared Object], '.so')  ------------//
	//----  Plugins  -----------------------------------------------------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//----------------------------------------------------------------------------------------------
	// Initialize Plugin-Manager, Plugin-Handle-Manager
	// Load and Register Plugins
	PluginManager* plugman;
	PluginManager_init(&plugman);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	DL_Libs_plugins_discover_folder(plugman,ProgPath,ProgPath_length,DENKREMENT_PLUGINS_SUBFOLDER,sizeof(DENKREMENT_PLUGINS_SUBFOLDER)-1);





	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  ShMem, Inter-Thread, Thread-Handling, Synchronization  -------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//----------------------------------------------------------------------------------------------
	// Initialize Shared-Memory, Thread-Management/Synchronization-Structures, Semaphores
	#define shmem_recv_start_self ShMem_recv_start(&(shmem_headers[DENKREMENT_THREAD__MAIN]))
	#define shmem_recv_finish_self ShMem_recv_finish(&(shmem_headers[DENKREMENT_THREAD__MAIN]))
	#define shmem_self (shmem_headers[DENKREMENT_THREAD__MAIN])
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	ThreadManager* thrall;
	DenKr_ThreadManager_init(&thrall,DENKR_THREADS__MAX_PREDEF);
	//TODO: Adjust to number of loaded dynamic DLLs
	struct ShMemHeader shmem_headers[DENKR_THREADS__SHMEM_MAX+(plugman->generic_c)];
	ShMem_Array_Sem_init(shmem_headers,DENKR_THREADS__SHMEM_MAX+(plugman->generic_c));







//=======================================================================================================================================
//=======================================================================================================================================
//=======================================================================================================================================
//----------  Temporary Testing Section  --------------------------------------------------------------------------------------==========
//=======================================================================================================================================
//=======================================================================================================================================
#ifdef DEBUG //----------------------------------------------------------------------------------------------------------------==========
#ifndef RELEASE_VERSION //Just to get sure... ;o) that nothing got forgotten within the final Build  --------------------------==========
//=======================================================================================================================================



//	(*(((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).hook))((void*)12);
//long test =-1;
//printf("\n\ntest : %li\n\n", test);
//print_Bin(&test,8);
//unsigned long test2=test;
//printf("\n\ntest : %lu\n\n", test);
//print_Bin(&test2,8);

//exit(1);





//=======================================================================================================================================
#endif //----------------------------------------------------------------------------------------------------------------------==========
#endif //----------------------------------------------------------------------------------------------------------------------==========
//=======================================================================================================================================
//=======================================================================================================================================
//----------  End  -  Temporary Testing Section  ------------------------------------------------------------------------------==========
//=======================================================================================================================================
//=======================================================================================================================================
//=======================================================================================================================================







	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Threads  -----------------------------------------------------------------------------------//
	//----  Start, Init, Get-Ready, Synchronized Start-of-Work  ----------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------
	// - - - - - Start Threads - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//- - The Context-Broker / Information-Dispenser  --------------------------------------------------//
	//- -   used as central Unit, enables nice and easy Inter-Thread/Module/Program-Communication  -----//
	#define TO_DEFINE__DENKR_MAIN_THREAD_ID DENKREMENT_THREAD__MAIN
	#define TO_DEFINE__DENKR_CONTEXTBROKER_THREAD_ID DENKREMENT_THREAD__CONTEXT_BROKER
	DENKR_CONTEXTBROKER_START_THREAD
	#undef TO_DEFINE__DENKR_MAIN_THREAD_ID
	#undef TO_DEFINE__DENKR_CONTEXTBROKER_THREAD_ID
	//Via ShMem: Wait for ContextBroker to be completely initialized, i.e. ready to take registrations (hashtab & sock with mutex are initialised)
	//    Note: Two things are possible here: (1) Termination, ordered by GUI-Thread, (2) Continue, because ContextBroker is initialized.
		TryWaitForContextBrokerInitAgain:
		shmem_recv_start_self;
		switch(shmem_self.type){
		case SHMEM_MSG_TYPE__READY:
			if(FLAG_CHECK(shmem_self.flags,SHMEM_MSG_FLAG__SRC_VALID)){
				switch(shmem_self.src){
				case DENKREMENT_THREAD__CONTEXT_BROKER:
					shmem_recv_finish_self;
					break;
				default:
					//TODO: Maybe add something via the ContextBroker
					shmem_recv_finish_self;
					printfc(red,"BUG:");printf(" READY-Msg to 'Main' from other src than ContextBroker-Thread. Should not be possible to occur... Ignoring...\n\tSource was: %d.\n",shmem_self.src);
					goto TryWaitForContextBrokerInitAgain;
					break;
				}
			}
			break;
		case SHMEM_MSG_TYPE__CANCEL_THREAD:
			if(FLAG_CHECK(shmem_self.flags,SHMEM_MSG_FLAG__SRC_VALID)){
				switch(shmem_self.src){
				case DENKREMENT_THREAD__GUI:
					shmem_recv_finish_self;
					printfc(green,"KEY-Event:");printf(" Application-Termination initiated.\n");
					goto ProgramTermination;
					break;
				default:
					//TODO: Maybe add something via the ContextBroker
					shmem_recv_finish_self;
					printfc(red,"BUG:");printf(" CANCEL_THREAD-Msg to 'Main' from other src than GUI-Thread. Ignoring...\n");
					break;
				}
			}else{
				shmem_recv_finish_self;
				printfc(red,"BUG:");printf(" CANCEL_THREAD-Msg to 'Main' from unspecified source. Ignoring...\n");
			}
			break;
		default: // Programming Error
			shmem_recv_finish_self;
			printfc(red,"ERROR:");
			printf(" Program-Bug encountered. Check the ShMem-Comm-Section of the Main-Thread.\n");
			printf("\tReceived ShMem-Type: %d\n",shmem_self.type);
			exit(MAIN_ERR_BUG);
			break;
		}
	//   Register Main at ContextBroker, if desired
	DenKr_InfBroker_Iface_Client InfBrok_Iface;
	InfBrok_Iface.hidden.send_to_Broker=&SockToBrok;
	InfBrok_Iface.hidden.ownID=DENKREMENT_THREAD__MAIN;
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//- - Graphical User Interface (GUI)  --------------------------------------------------------------//
	//- -   Does all the Stuff inside the Thread: Start, Load Layout-File, Build, Run Main-Loop  -------//
	GUI_START_THREAD
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//- - Specific, predefined Roles  ------------------------------------------------------------------//
	//      - For more Info, have look into "src/plugins/export/plugins_DenKr_essentials__common.h"  &  "src/plugins/export/plugins_export.h"
	DenKr_Thread_start_predefineds__PREP_ADDARGS//This Macro creates the Variable "addarg_arr"
	DenKr_Thread_start_predefineds(plugman, thrall, DENKREMENT_THREAD__MAIN, shmem_headers, &SockToBrok, addarg_arr);
	DenKr_Thread_start_predefineds__PREP_ADDARGS_EOC
									//	CONTEXTBROKER_connect_external_Python_START_THREAD
									//	//      Link Monitoring, based on SDN Methods (imported from Plugin)
									//	SDN_LINK_MONITORING_START_THREAD
									//	//      Network Topology Discovery, using SDN (imported from Plugin)
									//	NETWORK_TOPOLOGY_DISCOVERY_START_THREAD
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//- - Start the generic Module-Threads  ------------------------------------------------------------//
	DenKr_Thread_start_generics(plugman, thrall, DENKREMENT_THREAD__MAIN, shmem_headers, &SockToBrok);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - Get Everyone Ready - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//A "Wait for Ready"-Routine.   When all Threads are implemented, it should look like:
	//  Start all Threads sequentially
	//  Wait inside a ShMem Message Queue, like common inside the Threads.  --  Maybe use temporary state-variables
	//  Every Thread sends a "Ready" Message after Initialization.  --  These could be cascaded: The former existing 'SDN-Ctrl-Thread' waits for this Message from the Listen-Thread. - Main only waits for Ready-Message from the Sending-Thread
	//  Main first continues after one Ready-Message from every Thread was received.
	//- It is done a bit more complex than just with a counter to avoid a failure like multiple Ready-Msgs from the same Thread.
	//- Something familiar is done inside the Threads as well. After the Main received a Ready from every Thread, it sends a Ready to every Thread. Every Threads waits for this Ready from the main, after it sent its own Ready.
	DenKr_Threads_Main_Ready_Init(thrall, shmem_headers, DENKREMENT_THREAD__MAIN);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -







	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  ShMem-Communication  -----------------------------------------------------------------------//
	//----  Consider this as the 'Main-Operation' of the Main-Thread  ----------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//----------------------------------------------------------------------------------------------
	while(1){
		shmem_recv_start_self;

		switch(shmem_self.type){
		case SHMEM_MSG_TYPE__CANCEL_THREAD:
			if(FLAG_CHECK(shmem_self.flags,SHMEM_MSG_FLAG__SRC_VALID)){
				switch(shmem_self.src){
				case DENKREMENT_THREAD__GUI:
					shmem_recv_finish_self;
					printfc(green,"KEY-Event:");printf(" Application-Termination initiated.\n");
					goto ProgramTermination;
					break;
				default:
					//TODO: Maybe add something via the ContextBroker
					shmem_recv_finish_self;
					printfc(red,"BUG:");printf(" CANCEL_THREAD-Msg to 'Main' from other src than GUI-Thread. Ignoring...\n");
					break;
				}
			}else{
				shmem_recv_finish_self;
				printfc(red,"BUG:");printf(" CANCEL_THREAD-Msg to 'Main' from unspecified source. Ignoring...\n");
			}
			break;
		default: // Programming Error
			shmem_recv_finish_self;
			printfc(red,"ERROR:");
			printf(" Program-Bug encountered. Check the ShMem-Comm-Section of the Main-Thread.\n");
			printf("\tReceived ShMem-Type: %d\n",shmem_self.type);
			exit(MAIN_ERR_BUG);
			break;
		}
	}
	ProgramTermination:








	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Program-Termination Sequence  --------------------------------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//Instruct the appropriate Threads to stop working and terminate
					//	//=== A Template for send a Termination-Signal via the Shared-Memory Method to a running thread (in this case a straightly included Thread, i.e. not via plugin/DLL-library)
					//	//====== Using this, a Thread obviously must implement the recognition of such messages and a proper termination Sequence. After sending this, the main should join the Thread before Main-Termination. How is shown below the Signal-Sending, or better said, far further below.
					//	//   Tell the <NAMEofIt> Thread to Terminate (and to handle the Termination of its related Listen-Thread
					//	ShMem_send_start(&(shmem_headers[DENKREMENT_THREAD__NAMEofIt]), 0, SHMEM_MSG_TYPE__CANCEL_THREAD);
					//	//-------- No content.
					//	ShMem_send_finish(&(shmem_headers[DENKREMENT_THREAD__NAMEofIt]));
	//   Tell the Context-Broker to terminate (using it's own Communication Method, instead of ShMem)
	DenKr_ContextBroker_send_onlyHeader(&InfBrok_Iface,DenKr_InfBroker_Msg_Type__Management,DenKr_InfBroker_Msg_SubType__Management_Restricted__Termination,0);
	//TODO: Termination of the connect_external_Python Module. Then uncomment the Join below
	//    Update: Tell every (running...) predefined plugin to terminate. Than add a join below. Maybe check with some communication protocol, if a predefined plugin properly implemented a termination sequence handling. If not so: Just kill the thread and termiante the main Program without join. To make it even better: Implement a timeout; if a plugin-thread has not terminated after this period: same thing, kill it and terminate. To make even this even better: Implement a "plugin-container" which runs the plugins in an own process, outside of the main program.
	//TODO: Kill the generic Modules/Threads with the "Wooden Mallet", since we cannot safely assume/control that they implement an appropriate Termination-Method/Sequence
	//      Or maybe just start them detached and terminate the main()...
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//Decided to NOT do it like this:
	// Cause that would be a bit of a waste. Main doesn't have to wait for every Thread,
	// because some Threads already wait for others.
	// So does for example the SDN-Ctrl-Communication Thread (Responsible for Sending and Connecting)
	// wait for the Receiving/Listening Thread (also spawned by it).
	//	for(i=0;i<DENKREMENT_THREADS_MAX;i++){
	//		pthread_join(allThreads[0],NULL);
	//	}
	//Join, i.e. wait for the applicable Threads to be finished.
	//   Join the SDN-Ctrl Com Thread
	pthread_join((thrall->allThreads)[DENKREMENT_THREAD__GUI],NULL);
	pthread_join((thrall->allThreads)[DENKREMENT_THREAD__CONTEXT_BROKER],NULL);
//	pthread_join((thrall->allThreads)[DENKREMENT_THREAD__CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON],NULL);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
					//	//=== Rest of Termination-Template
					//	pthread_join((thrall->allThreads)[DENKREMENT_THREAD__NAMEofIt],NULL);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	printf("\nDenKrement: Exiting with Error-Code: %d\n",err);
	pthread_exit(NULL);
	#undef shmem_recv_start_self
	#undef shmem_recv_finish_self
	#undef shmem_self

	#undef cfg_files_v

	return err;
}




#undef NO_DENKREMENT_C_FUNCTIONS
