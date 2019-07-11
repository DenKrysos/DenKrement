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
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//






// These are used for the pthread_t - Array and also as Indices with the Shared-Memory Array
#define DENKREMENT_THREAD__GUI                                        0
#define DENKREMENT_THREAD__CONTEXT_BROKER                             INC(DENKREMENT_THREAD__GUI)
#define DENKREMENT_THREAD__CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON    INC(DENKREMENT_THREAD__CONTEXT_BROKER)
#define DENKREMENT_THREAD__SDN_CTRL_COM                               INC(DENKREMENT_THREAD__CONTEXT_BROKER__EXTERN_CONNECTOR_PYTHON)
#define DENKREMENT_THREAD__SDN_CTRL_COM_LISTEN                        INC(DENKREMENT_THREAD__SDN_CTRL_COM)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKREMENT_THREAD__SDN_LINK_MONITORING               INC(DENKREMENT_THREAD__SDN_CTRL_COM_LISTEN)
#define DENKREMENT_THREAD__NETWORK_TOPOLOGY_DISCOVERY        INC(DENKREMENT_THREAD__SDN_LINK_MONITORING)
//Use this at initialization of the Array: (This is a quantity, the above are IDs)
#define DENKREMENT_THREADS__MAX_PREDEF                       INC(DENKREMENT_THREAD__NETWORK_TOPOLOGY_DISCOVERY)

//This is especially done to be able to differentiate the Array for pthread_t Handling-IDs
// and the Array to store the Shared-Memory Headers in.
//Because the pthread_t Array doesn't need an Entry for the 'main', the basic Program-Thread.
//But the ShMem-Array can/could hold a ShMem-Header for communication with this.
#define DENKREMENT_THREAD__MAIN                              DENKREMENT_THREADS__MAX_PREDEF
#define DENKREMENT_THREADS__SHMEM_MAX                        INC(DENKREMENT_THREAD__MAIN)






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
