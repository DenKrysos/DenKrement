/*
 * DenKrement_threads.h
 *
 *  Created on: 21.08.2017
 *      Author: Dennis Krummacker
 */

#ifndef DENKREMENT_THREADS_H
#define DENKREMENT_THREADS_H




//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
//#include "./global/global_settings.h"
//#include "./global/global_variables.h"
// Need this for e.g. some really fundamental Program Basics (if any)  ------------
//---------------------------------------------------------------------------------
//#include "DenKrement_base.h"
// Then better start with this  ---------------------------------------------------
//---------------------------------------------------------------------------------
//#include "DenKrement.h"
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Just to nicely keep order:  -----------------------------------------------------
//   First include the System / Third-Party Headers  ------------------------------
//   Format: Use <NAME> for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include ""
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#include "DenKr_essentials/PreC/DenKr_PreC.h"
//#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/multi_threading.h"
#if defined(DENKR_ESSENTIALS__DL_LIBS__NONE)
#elif defined(DENKR_ESSENTIALS__DL_LIBS__MAIN_APP)
	#include "plugins/export/plugins_DenKr_essentials__common.h"
#elif defined(DENKR_ESSENTIALS__DL_LIBS__PLUGIN_PREDEFINED)
	//Be cautious with the Resource-Linking (Eclipse) and include-paths (compiler arguments), when compiling a Plugin with set global Value
	#include "plugins_DenKr_essentials__common.h"
#elif defined(DENKR_ESSENTIALS__DL_LIBS__PLUGIN_GENERIC)
	//Generic Plugins/Modules at least need to know the "generic"-role and stuff like the working-modes
	#include "plugins_DenKr_essentials__common.h"
#else
	#pragma error "ERROR: Define either DENKR_ESSENTIALS__DL_LIBS__MAIN_APP or DENKR_ESSENTIALS__DL_LIBS__PLUGIN inside <global/global_settings.h>"
	ERROR"ERROR: Define either DENKR_ESSENTIALS__DL_LIBS__MAIN_APP or DENKR_ESSENTIALS__DL_LIBS__PLUGIN inside <global/global_settings.h>"
#endif
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//

//TODO: Frameworkarize this better. Define a std-path under which such a File should reside and define a naming convention that is more directed towards DenKr_ instead of DenKrement.
//  Then outsource parts of this into DenKr_essentials, just like done (or also to be done yet? -.-) for the Predefined Plugin Roles
//  Then change the include path into the "multi_threading.h" to this new file(s) (Currently there is this one here inlcuded)







//Explanation:
//Inside "plugins/export/plugins_DenKr_essentials__common.h" the List of predefined Plugin-roles is defined (mandatory plugins that are supposed to be existent, actually intended to be required; handled differently and separately from generic plugins)
//First, this List becomes prefixed with "DenKrement_Thread__"
//Then, this is inserted into the enum of all Thread Indices of DenKrement

//Append the Prefix
#define DENKREMENT_THREAD_CONCAT_PREFIX_(ARG) DenKrement_Thread__ ## ARG
#define DenKrement_Thread_Plugin_ENTRIES_ CALL_MACRO_X_FOR_EACH__LIST(DENKREMENT_THREAD_CONCAT_PREFIX_,DenKr_plugin_roles_ENTRIES)
//A little Trick, which automagically decides, if a trailing comma is necessary
#define DenKrement_Thread_Plugin_ENTRIES__appendCOMMA DenKrement_Thread_Plugin_ENTRIES_,
#define DenKrement_Thread_Plugin_ENTRIES__ \
		IF(EQUAL(COUNT_VARARGS(DenKr_plugin_roles_ENTRIES),0))(\
		)IF(NOT_EQUAL(COUNT_VARARGS(DenKr_plugin_roles_ENTRIES),0))(\
			DenKrement_Thread_Plugin_ENTRIES__appendCOMMA\
		)

typedef enum DenKrement_Thread_IDC_t{
	//Own Threads of DenKrement. Fixed. Straightly included in DenKrement itself
	DENKREMENT_THREAD__MAIN=0,
	DENKREMENT_THREAD__GUI,
	DENKREMENT_THREAD__CONTEXT_BROKER,//A Thread/module called 'CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON' for allowing external running Python Scripts to connect to the Context Broker is done in Form of a predefined Plugin
	//===================================================================
	//predefined Plugin Roles are automatically filled in here
	DenKrement_Thread_Plugin_ENTRIES__
	//===================================================================
	//Use this at initialization of the Array: (This is a quantity, the above are IDs)
	DENKREMENT_THREADS__MAX_PREDEF,
	//===================================================================
	DENKREMENT_THREADS__SHMEM_MAX = DENKREMENT_THREADS__MAX_PREDEF
}DenKrement_Thread_IDC;






//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//----  ShMem Msg Types  -----------------------------------------------------------------------------
//----  (Additional Types to the ones defined from DenKr_essentials already)  ------------------------
//----  (I.e. ones specific for DenKrement)  ---------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//====================================================================================================
#define SHMEM_MSG_TYPE__SDN_CTRL__DISCONNECTED                 INC(SHMEM_MSG_TYPE__RESERVED_END)
#define SHMEM_MSG_TYPE__SDN_CTRL__RECONNECT_SUCCESS            INC(SHMEM_MSG_TYPE__SDN_CTRL__DISCONNECTED)
#define SHMEM_MSG_TYPE__GET_DPIDS                              INC(SHMEM_MSG_TYPE__SDN_CTRL__RECONNECT_SUCCESS)
#define SHMEM_MSG_TYPE__GET_SWITCHES                           INC(SHMEM_MSG_TYPE__GET_DPIDS)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////





#endif /* DENKREMENT_THREADS_H */
