/*
 * DenKrement_plugins.h
 *
 *  Created on: 26.07.2017
 *      Author: Dennis Krummacker
 */

#ifndef PLUGINS__EXPORT__PLUGINS_EXPORT_H
#define PLUGINS__EXPORT__PLUGINS_EXPORT_H












//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Further Descriptions and Ressources for predefined Roles  ----------------------------------//
//----  The Resources has to be #included by the plugins  ------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   DenKrement_plugin_predefined__connect_external_Python   - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Working-Type: Thread (DenKr_plugin_working_type__thread)
//
// The Thread is started with this:
struct ContextBroker_connect_external_Python_ThreadArgPassing {
	ThreadManager* thrall;//The ThreadManager. Contains the two Arrays: pthread* allThreads: Mainly to start the listen thread inside. DenKr_ThreadSpawned* runningThreads: Passed to record the Listening-Thread as running;
	PluginManager* plugman;
	struct ShMemHeader *shmem_headers;//An Array
	DenKr_essentials_ThreadID ownID;
	DenKr_essentials_ThreadID mainThreadID;
	void* ContextBrokerInterface;
};

#define CONTEXTBROKER_connect_external_Python_START_THREAD \
		if( FLAG_CHECK(((plugman->predef)[DenKr_plugin_role__Context_Broker__External_Connector_Python]).flags,DENKR_PLUGINS_ROLE_FLAG__ROLE_DEFINED) ){ \
			if(((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type == DenKr_plugin_working_type__thread){ \
				DENKR_START_THREAD_PATTERN(false,\
											((plugman->predef)[DenKr_plugin_role__Context_Broker__External_Connector_Python]).hook,\
											DENKREMENT_THREAD__CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON,\
											PTHREAD_CREATE_JOINABLE,\
												struct ContextBroker_connect_external_Python_ThreadArgPassing *ThreadArgPass;\
												\
												ThreadArgPass = malloc(sizeof(*ThreadArgPass));\
												ThreadArgPass->thrall=thrall;\
												ThreadArgPass->plugman=plugman;\
												ThreadArgPass->shmem_headers=shmem_headers;\
												ThreadArgPass->ownID=DENKREMENT_THREAD__CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON;\
												ThreadArgPass->mainThreadID=DENKREMENT_THREAD__MAIN;\
												\
												ThreadArgPass->ContextBrokerInterface=malloc(sizeof(DenKr_InfBroker_Iface_Client));\
												memset(ThreadArgPass->ContextBrokerInterface,0,sizeof(DenKr_InfBroker_Iface_Client));\
												(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->hidden).send_to_Broker=&SockToBrok;\
												(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->hidden).ownID=DENKREMENT_THREAD__CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON;\
												(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncSend).sendStr=(InfBrok_FuncSendStr)DenKr_ContextBroker_sendInfo_Str;\
												(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegConsumer).regSocket=(InfBrok_FuncRegListenMethod)DenKr_ContextBroker_register_Consumer_socket;\
												(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegConsumer).regCallback=(InfBrok_FuncRegCallback)DenKr_ContextBroker_register_Consumer_callback;\
												(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegProducer).regSocket=(InfBrok_FuncRegListenMethod)DenKr_ContextBroker_register_Producer_socket;\
												(((DenKr_InfBroker_Iface_Client*)(ThreadArgPass->ContextBrokerInterface))->FuncRegProducer).regCallback=(InfBrok_FuncRegCallback)DenKr_ContextBroker_register_Producer_callback;\
										)\
			}else{ \
				CREATE_argv_CONST(print_roles, CALL_MACRO_X_FOR_EACH__LIST(STRINGIFY,DenKr_plugin_roles_ENTRIES) ) \
				printfc(yellow,"WARNING:");printf(" Loaded Module for Role \"DenKr_plugin_role__Context_Broker__External_Connector_Python\" is not of Working-Type \"Thread\" (%d), but of \"%s\" (%d).\n",DenKr_plugin_role__SDN_link_monitoring,print_roles[((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type],((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type); \
			} \
		}else{ \
			printfc(gray,"NOTE:");printf(" No Module loaded, to attend the Role \"DenKr_plugin_role__Context_Broker__External_Connector_Python\".\n"); \
		}
// Possibilites for "setdetachstate":
//   - PTHREAD_CREATE_JOINABLE
//   - PTHREAD_CREATE_DETACHED
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   DenKr_plugin_role__SDN_link_monitoring   - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Working-Type: Thread (DenKr_plugin_working_type__thread)
//
// The Thread is started with this:
struct SDN_link_monitoring_ThreadArgPassing {
	ThreadManager* thrall;//The ThreadManager. Contains the two Arrays: pthread* allThreads: Mainly to start the listen thread inside. DenKr_ThreadSpawned* runningThreads: Passed to record the Listening-Thread as running;
	struct ShMemHeader *shmem_headers;//An Array
	DenKr_essentials_ThreadID ownID;
	DenKr_essentials_ThreadID mainThreadID;
};

#define SDN_LINK_MONITORING_START_THREAD \
		if( FLAG_CHECK(((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).flags,DENKR_PLUGINS_ROLE_FLAG__ROLE_DEFINED) ){ \
			if(((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type == DenKr_plugin_working_type__thread){ \
				DENKR_START_THREAD_PATTERN(false,\
											((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).hook,\
											DENKREMENT_THREAD__SDN_LINK_MONITORING,\
											PTHREAD_CREATE_JOINABLE,\
												struct SDN_link_monitoring_ThreadArgPassing *ThreadArgPass;\
												\
												ThreadArgPass = malloc(sizeof(*ThreadArgPass));\
												ThreadArgPass->thrall=thrall;\
												ThreadArgPass->shmem_headers=shmem_headers;\
												ThreadArgPass->ownID=DENKREMENT_THREAD__SDN_LINK_MONITORING;\
												ThreadArgPass->mainThreadID=DENKREMENT_THREAD__MAIN;\
										)\
			}else{ \
				CREATE_argv_CONST(print_roles, CALL_MACRO_X_FOR_EACH__LIST(STRINGIFY,DenKr_plugin_roles_ENTRIES) ) \
				printfc(yellow,"WARNING:");printf(" Loaded Module for Role \"DenKr_plugin_role__SDN_link_monitoring\" is not of Working-Type \"Thread\" (%d), but of \"%s\" (%d).\n",DenKr_plugin_role__SDN_link_monitoring,print_roles[((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type],((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type); \
			} \
		}else{ \
			printfc(gray,"NOTE:");printf(" No Module loaded, to attend the Role \"DenKr_plugin_role__SDN_link_monitoring\".\n"); \
		}
// Possibilites for "setdetachstate":
//   - PTHREAD_CREATE_JOINABLE
//   - PTHREAD_CREATE_DETACHED
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   DenKr_plugin_role__network_topology_discovery   - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Working-Type: Thread (DenKr_plugin_working_type__thread)
//
// The Thread is started with this:
struct network_topology_discovery_ThreadArgPassing {
	ThreadManager* thrall;//The ThreadManager. Contains the two Arrays: pthread* allThreads: Mainly to start the listen thread inside. DenKr_ThreadSpawned* runningThreads: Passed to record the Listening-Thread as running;
	struct ShMemHeader *shmem_headers;//An Array
	DenKr_essentials_ThreadID ownID;
	DenKr_essentials_ThreadID mainThreadID;
};

#define NETWORK_TOPOLOGY_DISCOVERY_START_THREAD \
		if( FLAG_CHECK(((plugman->predef)[DenKr_plugin_role__network_topology_discovery]).flags,DENKR_PLUGINS_ROLE_FLAG__ROLE_DEFINED) ){ \
			if(((plugman->predef)[DenKr_plugin_role__network_topology_discovery]).work_type == DenKr_plugin_working_type__thread){ \
				DENKR_START_THREAD_PATTERN(false,\
											((plugman->predef)[DenKr_plugin_role__network_topology_discovery]).hook,\
											DENKREMENT_THREAD__NETWORK_TOPOLOGY_DISCOVERY,\
											PTHREAD_CREATE_JOINABLE,\
												struct network_topology_discovery_ThreadArgPassing *ThreadArgPass;\
												\
												ThreadArgPass = malloc(sizeof(*ThreadArgPass));\
												ThreadArgPass->thrall=thrall;\
												ThreadArgPass->shmem_headers=shmem_headers;\
												ThreadArgPass->ownID=DENKREMENT_THREAD__NETWORK_TOPOLOGY_DISCOVERY;\
												ThreadArgPass->mainThreadID=DENKREMENT_THREAD__MAIN;\
										)\
			}else{ \
				CREATE_argv_CONST(print_roles, CALL_MACRO_X_FOR_EACH__LIST(STRINGIFY,DenKr_plugin_roles_ENTRIES) ) \
				printfc(yellow,"WARNING:");printf(" Loaded Module for Role \"DenKr_plugin_role__network_topology_discovery\" is not of Working-Type \"Thread\" (%d), but of \"%s\" (%d).\n",DenKr_plugin_role__SDN_link_monitoring,print_roles[((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type],((plugman->predef)[DenKr_plugin_role__SDN_link_monitoring]).work_type); \
			} \
		}else{ \
			printfc(gray,"NOTE:");printf(" No Module loaded, to attend the Role \"DenKr_plugin_role__network_topology_discovery\".\n"); \
		}
// Possibilites for "setdetachstate":
//   - PTHREAD_CREATE_JOINABLE
//   - PTHREAD_CREATE_DETACHED
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////









#endif /* PLUGINS__EXPORT__PLUGINS_EXPORT_H */
