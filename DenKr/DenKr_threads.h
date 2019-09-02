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


//Explanation:
//Inside "plugins/export/plugins_DenKr_essentials__common.h" the List of predefined Plugin-roles is defined (mandatory plugins that are supposed to be existent, actually intended to be required; handled differently and separately from generic plugins)
//First, this List becomes prefixed with "DenKrement_Thread__"
//Then, this is inserted into the enum of all Thread Indices of DenKrement
//INFO:
// Similar procedure as explained for the predefined Plugin Roles.
// Inside "DenKr_essentials/threads_codeGeneration.h" are some fine Macros defined, which automatically generate code, based on the defined "predefined Roles".
// So these macros are work tightly intertwined with the stuff from "src/plugins/export/plugins_DenKr_essentials__common.h" & "src/plugins/export/plugins_export.h".
// Amongst others, it creates an enumeration containing the Thread-IDs   »typedef enum DenKrement_Thread_IDC_t{ [...] }DenKrement_Thread_IDC;«

//USAGE:
// Here you define your additional intrinsic Threads, which are in use for your Main-Application (excluding the »main()« itself)
//   This might be for example a Thread for your GUI (Graphical User Interface) or a thread for the Context-Broker from DenKr_essentials
// With "DenKr_Thread_ENTRIES_Prefix" you can define an optional Prefix, which will be literally attached to every label defined in "DenKr_Thread_ENTRIES"
//   Just leave it blank (i.e. "#define DenKr_Thread_ENTRIES_Prefix" with nothing else in the Line), if you don't want to attach a common Phrase.


//DenKrement specific Comment/Info (i.e. not about DenKr_essentials):
//  DENKREMENT_THREAD__CONTEXT_BROKER: /*A Thread/module called 'CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON' for allowing external running Python Scripts to connect to the Context Broker is done in Form of a predefined Plugin*/



//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----------------------------------------------------------------------------------------------------
//----  Intrinsic Threads  ---------------------------------------------------------------------------
//----  (The definition of the Threads, that are running directly inside the Main-Program)  ----------
//----  (I.e. ones specific for DenKrement, and not via Plugins)  ------------------------------------
//----------------------------------------------------------------------------------------------------
//====================================================================================================
#define DenKr_Thread_ENTRIES_Prefix DENKREMENT_THREAD

#define DenKr_Thread_ENTRIES\
	GUI,\
	CONTEXT_BROKER




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




//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----  Include this at the very last  ---------------------------------------------------------------
//----  (Include&Define Order matters here)  ---------------------------------------------------------
#include "DenKr_essentials/threads_codeGeneration.h"
//----------------------------------------------------------------------------------------------------
//====================================================================================================



#endif /* DENKREMENT_THREADS_H */
