/*
 * GUI_thread.c
 *
 *  Created on: 02.10.2017
 *      Author: Dennis Krummacker
 */


#define DENKREMENT__GUI__GUI_THREAD__C
#define NO__DENKREMENT__GUI__GUI_THREAD__C__FUNCTIONS



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
#include <stdlib.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
#include "GUI/GTK+/gui_functions.h"
#include "DenKrement_threads.h"
#include "GUI/GUI_thread.h"
//---------------------------------------------------------------------------------
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/GUI/GTK+/denkr_gui_gtk_main.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//






void* DenKrement_thread_GUI(void* arg){
	#define shmem_recv_start_self ShMem_recv_start(&(shmem_headers[DENKREMENT_THREAD__GUI]))
	#define shmem_recv_finish_self ShMem_recv_finish(&(shmem_headers[DENKREMENT_THREAD__GUI]))
	#define shmem_self (shmem_headers[DENKREMENT_THREAD__GUI])
	ThreadManager* thrall = (((struct GUI_ThreadArgPassing *)arg)->thrall);
	struct ShMemHeader *shmem_headers = (((struct GUI_ThreadArgPassing *)arg)->shmem_headers);
	free(arg);
//	int err;

	//Tell Main, that i am Ready and than wait for Main, to tell me, that everyone is Ready.
	DenKr_Thread_Ready_Init(shmem_headers, DENKREMENT_THREAD__MAIN, DENKREMENT_THREAD__GUI)


	//==================================================================================================//
	//--------------------------------------------------------------------------------------------------//
	//----  Graphical User Interface (GUI)  ------------------------------------------------------------//
	//----  Start, Load Layout-File, Build, Run Main-Loop  ---------------------------------------------//
	//--------------------------------------------------------------------------------------------------//
	//==================================================================================================//
	//----------------------------------------------------------------------------------------------
	//GTK+ 3
	DenKr_essentials_GUI_gtk_main(argcg,argvg);


	ShMem_send_start(&(shmem_headers[DENKREMENT_THREAD__MAIN]), 0, SHMEM_MSG_TYPE__CANCEL_THREAD);
	FLAG_SET(shmem_headers[DENKREMENT_THREAD__MAIN].flags,SHMEM_MSG_FLAG__SRC_VALID);
	shmem_headers[DENKREMENT_THREAD__MAIN].src = DENKREMENT_THREAD__GUI;
	ShMem_send_finish(&(shmem_headers[DENKREMENT_THREAD__MAIN]));


	printfc(yellow,"IMPORTANT:");
	printf(" GUI Thread is closing.\n");

	#undef shmem_recv_start_self
	#undef shmem_recv_finish_self
	#undef shmem_self
	return NULL;
}








#undef DENKREMENT__GUI__GUI_THREAD__C
#undef NO__DENKREMENT__GUI__GUI_THREAD__C__FUNCTIONS
