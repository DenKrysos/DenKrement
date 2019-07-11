/*
 * DenKrement_cfg_files.h
 *
 *  Created on: 25.08.2017
 *      Author: Dennis Krummacker
 */

#ifndef FILES_CONFIG_DENKREMENT_CFG_FILES_H
#define FILES_CONFIG_DENKREMENT_CFG_FILES_H





//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
//#include <global/global_settings.h>
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
#include <stdio.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//---------------------------------------------------------------------------------
//#include "DenKr_essentials/PreC/DenKr_PreC.h"
//#include "DenKr_essentials/DenKr_errno.h"
//#include "DenKr_essentials/Program_Files/P_Files_Path.h"
#include "DenKr_essentials/Program_Files/control_cfg_file.h"
//#include "auxiliary.h"
//#include "function_creator.h"
//#include "getRealTime.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//



// Info about Path/File Naming Conventions:
//   Found inside "DenKr_essentials/Program_Files/P_Files_Path.h"






//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Definitions  -------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   General Definitions - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKREMENT_CFG_FILES_PATH_PREFIX "cfg/" // EVERY cfg-file path becomes preceded with this
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - -   The config-Files    - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKREMENT_CFG_FILE_MAIN						"DenKrement.cfg"
#define DENKREMENT_CFG_FILE_IDX_MAIN					0
#define DENKREMENT_CFG_FILE_SDN_CONTROLLER				"SDN/SDN_Controller.cfg"
#define DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER			INC(DENKREMENT_CFG_FILE_IDX_MAIN)
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKREMENT_CFG_FILE_NAMES ( \
									DENKREMENT_CFG_FILE_MAIN, \
									DENKREMENT_CFG_FILE_SDN_CONTROLLER \
								  )
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define DENKREMENT_CFG_FILES_QUANTITY					INC(DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER)
#define DENKREMENT_CFG_FILES_ARRAY_SIZE ( \
											DENKREMENT_CFG_FILES_QUANTITY * sizeof(uintptr_t) + \
											(DENKREMENT_CFG_FILES_QUANTITY * sizeof(DENKREMENT_CFG_FILES_PATH_PREFIX)) - DENKREMENT_CFG_FILES_QUANTITY + \
											sizeof(DENKREMENT_CFG_FILE_MAIN) + \
											sizeof(DENKREMENT_CFG_FILE_SDN_CONTROLLER) \
										)
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////







//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//---------   (Assume this section as something like a)   ------------------------------------------//
//----  ***  DenKrement_cfg_files__function_creator_funcname.h  ***  -------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
// #ifdef REMAINDER_C
//////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(APPENDIX)                      cfg_file_create_default_ ## APPENDIX
#define CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(APPENDIX,ARG_PATH)              _CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(APPENDIX)(ARG_PATH)
#define CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME_DECLARE(APPENDIX,ARG_PATH)      int CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(APPENDIX,ARG_PATH)
//////////////////////////////////////////////////////////////////////////////////////////////////////
// #endif
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----  cfg_file_create_default()  -------------------------------------------------------------------
//------  (Wrapper Macro)  ---------------------------------------------------------------------------
//====================================================================================================
#define cfg_file_create_default(FILE_DEFINE,ARG_PATH) \
		SWITCH( \
			EQUAL(FILE_DEFINE,DENKREMENT_CFG_FILE_IDX_MAIN), \
				CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(FILE_DEFINE,ARG_PATH) \
				, \
			EQUAL(FILE_DEFINE,DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER), \
				CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(FILE_DEFINE,ARG_PATH) \
				, \
			/* Default: */ \
				; \
		)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////









//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//---------   Outplaced Macro, just for cosmetic Reason   ------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
    //----  Setting up nicely accessible Config-File Names
    //----       As Full-Paths
    //--------------------------------------------------------------------------------------------------//
	// Creates an Array-Array ( [][] ) holding the Config Files. After this you can use it like argv
	//     with the Indices from DenKrement_cfg_files.h
	// cfg_files_v[DENKREMENT_CFG_FILE_IDX_MAIN] gives a string (i.e. a char* to a Null-terminated char-Array)
	//     -> "/etc/DenKrement/cfg/DenKrement.cfg"
#define create_cfg_files_argv \
	char cfg_files_v_[DENKREMENT_CFG_FILES_ARRAY_SIZE + StorageFilesPath_length*DENKREMENT_CFG_FILES_QUANTITY]; \
	cfg_files_v[DENKREMENT_CFG_FILE_IDX_MAIN] = cfg_files_v_ + DENKREMENT_CFG_FILES_QUANTITY * sizeof(char *); \
	cfg_files_v[DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER] = ((char **)cfg_files_v)[DENKREMENT_CFG_FILE_IDX_MAIN] + sizeof(DENKREMENT_CFG_FILE_MAIN DENKREMENT_CFG_FILES_PATH_PREFIX) + StorageFilesPath_length; \
	snprintf(cfg_files_v[DENKREMENT_CFG_FILE_IDX_MAIN],sizeof(DENKREMENT_CFG_FILE_MAIN DENKREMENT_CFG_FILES_PATH_PREFIX)+StorageFilesPath_length,"%s"DENKREMENT_CFG_FILES_PATH_PREFIX DENKREMENT_CFG_FILE_MAIN,StorageFilesPath); \
	snprintf(cfg_files_v[DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER],sizeof(DENKREMENT_CFG_FILE_SDN_CONTROLLER DENKREMENT_CFG_FILES_PATH_PREFIX)+StorageFilesPath_length,"%s"DENKREMENT_CFG_FILES_PATH_PREFIX DENKREMENT_CFG_FILE_SDN_CONTROLLER,StorageFilesPath); \
	printf("\nUsed Config-Files:\n"); \
	for(i=0;i<DENKREMENT_CFG_FILES_QUANTITY;i++){ \
		printf("\t%s\n",cfg_files_v[i]); \
	} \
	puts(""); \
	cfg_files_v_gl = cfg_files_v;
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

																	//--------------------------------------------------------------------------------------------------//
																	//---------   Backup, please ignore this   ---------------------------------------------------------//
																	//--------------------------------------------------------------------------------------------------//
																			//	char cfg_files_v_[DENKREMENT_CFG_FILES_ARRAY_SIZE + StorageFilesPath_length*DENKREMENT_CFG_FILES_QUANTITY];
																			//	#define cfg_files_v ((char **)cfg_files_v_)
																			////	*((char **)(cfg_files_v+DENKREMENT_CFG_FILE_IDX_MAIN)) = cfg_files_v + DENKREMENT_CFG_FILES_QUANTITY * sizeof(char *);
																			//	cfg_files_v[DENKREMENT_CFG_FILE_IDX_MAIN] = cfg_files_v_ + DENKREMENT_CFG_FILES_QUANTITY * sizeof(char *);//This is a much cleaner notation :o/
																			//	cfg_files_v[DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER] = ((char **)cfg_files_v)[DENKREMENT_CFG_FILE_IDX_MAIN] + sizeof(DENKREMENT_CFG_FILE_MAIN DENKREMENT_CFG_FILES_PATH_PREFIX) + StorageFilesPath_length;
																			////	printf("array: %u\n%u\n%u\n",(uintptr_t)cfg_files_v,(uintptr_t)((char **)cfg_files_v)[0],(uintptr_t)((char **)cfg_files_v)[1]);
																			//	snprintf(cfg_files_v[DENKREMENT_CFG_FILE_IDX_MAIN],sizeof(DENKREMENT_CFG_FILE_MAIN DENKREMENT_CFG_FILES_PATH_PREFIX)+StorageFilesPath_length,"%s"DENKREMENT_CFG_FILES_PATH_PREFIX DENKREMENT_CFG_FILE_MAIN,StorageFilesPath);
																			//	snprintf(cfg_files_v[DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER],sizeof(DENKREMENT_CFG_FILE_SDN_CONTROLLER DENKREMENT_CFG_FILES_PATH_PREFIX)+StorageFilesPath_length,"%s"DENKREMENT_CFG_FILES_PATH_PREFIX DENKREMENT_CFG_FILE_SDN_CONTROLLER,StorageFilesPath);
																			////	printf("%s\n%s\n",((char **)cfg_files_v)[0],((char **)cfg_files_v)[1]);
																			//	printf("\nUsed Config-Files:\n");
																			//	for(i=0;i<DENKREMENT_CFG_FILES_QUANTITY;i++){
																			//		printf("\t%s\n",cfg_files_v[i]);
																			//	}
																			//	puts("");
																			//	cfg_files_v_gl = cfg_files_v;










//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  Functions to be visible outside  -----------------------------------------------------------//
//----      (external)  ----------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//----------------------------------------------------------------------------------------------------
#ifndef NO_DENKREMENT_CFG_FILES_C_C_FUNCTIONS
extern CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME_DECLARE(DENKREMENT_CFG_FILE_IDX_MAIN,char *path);
extern CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME_DECLARE(DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER,char *path);

//returned_missing: Declare a char[] (or accordingly malloced char*), respective to the number of checked Files.
//   Than pass this to the function, i.e. the start-adress or in other words the 'array-variable itself' respectively the value of the char*
//   As Array-Entries you get back a
//       '0', if File is not present
//       '1', if present.
// Afterwards you obviously have to free(), if you used char* with malloc.
//Return Values of Function:
//   0: Everything fine, no error, no missing cfg-File
//   1: No Error, but missing cfg-File(s). Look into returned_missing
//   2: Some Error occurred, The corresponding errno occured on processing a File is than delivered
//      back inside returned_missing
//      In this case the values 0, 1 are still standing for "0: Present", "1: Missing".
//      Values higher than '1' are assumed to be errno.
//           (Note: The errno '1', should be 'EPERM' on actually all Systems and this can't occur while fopen() )
//filesv: Paths shall be Full-Paths
extern int check_cfg_files_presence(char** filesv, int filesc, char* returned_missing);
extern int cfg_files_init_and_default(char** cfg_files_argv);
#endif
//----------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////




#endif /* FILES_CONFIG_DENKREMENT_CFG_FILES_H */
