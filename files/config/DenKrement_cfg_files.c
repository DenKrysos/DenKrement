/*
 * DenKrement_cfg_files.c
 *
 *  Created on: 25.08.2017
 *      Author: Dennis Krummacker
 */



#define DENKREMENT_CFG_FILES_C
#define NO_DENKREMENT_CFG_FILES_C_C_FUNCTIONS


//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//--------  Preamble, Inclusions  ------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//==================================================================================================//
// At first include this ----------------------------------------------------------
//---------------------------------------------------------------------------------
#include <global/global_settings.h>
#include "./global/global_variables.h"
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
#include <errno.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
#include "DenKrement_cfg_files.h"
//---------------------------------------------------------------------------------
#include "DenKr_essentials/PreC/DenKr_PreC.h"
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/DenKr_errno.h"
#include "DenKr_essentials/Program_Files/P_Files_Path.h"
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






int cfg_file__main__create_default(){

}

int cfg_file__main__read_complete(){

}

int cfg_file__main__write_value(){

}

int cfg_file__main__read_value(){

}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//====================================================================================================
//----  cfg_file_create_default()  -----------------------------------------------------------------------------
//====================================================================================================
// The "Wrapper-Macro", i.e. the one you should finally use, can be found inside the "[...]_cfg_files.h"
#define CREATE__CONFIG_FILE_CREATE_DEFAULT(APPENDIX,FILE_DEFINE,ARG_PATH) CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME_DECLARE(APPENDIX,ARG_PATH){ \
	int err=0; \
	 \
	FILE *cfgf=NULL; \
	 \
	{ \
		char *LastSlash; \
		for(LastSlash=path;*LastSlash!='\0';LastSlash++){} \
		for(;*LastSlash!='/';LastSlash--){} \
		/* Something like a to play safe mechanism: */ \
		/* We don't want to accidently create a disorder, while unwittingly mixing unmatching */ \
		/*		"target cfg file / file_define" and "path" */ \
		/* I.e. this passage here brings us on the safe side against programming errors. */ \
		/* Only after that passed check, we do even create the folder path. */ \
		char MacroPath[] = ARRAY_ENTRY(FILE_DEFINE, DENKREMENT_CFG_FILE_NAMES); \
		char *AfterLastSlashMacro; \
		for(AfterLastSlashMacro=MacroPath+sizeof(MacroPath)-1;(*AfterLastSlashMacro!='/')&&(AfterLastSlashMacro>=MacroPath);AfterLastSlashMacro--){} \
		AfterLastSlashMacro++; \
		if(strcmp(LastSlash+1,AfterLastSlashMacro)){ \
			printf("Passed File-Define: \t\t\t\"%s\"\nand File-Name from passed path: \t\"%s\"    doesn't match.\nSeems to be a Programming-Bug. I prefer to stay on the safe side and don't do further Operations, i.e. don't try to create a default config-file.\n\t(Function: "STRINGIFY(CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(APPENDIX,ARG_PATH))")\n", AfterLastSlashMacro, LastSlash+1); \
			return MAIN_ERR_BUG; \
		} \
		/* - - - - - - - - - - - - - - - - - - - - - -*/ \
		char cfg_file_dir[LastSlash-path+2]; \
		memcpy(cfg_file_dir,path,LastSlash-path+1); \
		cfg_file_dir[LastSlash-path+1]='\0'; \
		/*printf("dir: %s\n",cfg_file_dir);*/ \
		CREATE_COMPLETE_FOLDER_PATH(cfg_file_dir); \
	} \
	cfgf=NULL; \
	cfgf = fopen(path, "r"); \
    if (cfgf) { \
    	printfc(yellow,"OPERATION BLOCKED:"); \
    	printf(" File already exists: \"%s\". Won't create a Default One.\n\n",ARRAY_ENTRY(FILE_DEFINE, DENKREMENT_CFG_FILE_NAMES)); \
    	fclose(cfgf); \
    	return FILE_ERR_ALREADY_EXISTS; \
	}else{ \
		switch(errno){ \
		case ENOENT: /*File doesn't exist. Very fine, this is the way we want to go.*/ \
			cfgf = fopen(path, "w"); \
			if (!cfgf) { \
				switch(errno){ \
					case EACCES: \
						printf("\tERROR: Couldn't create cfg-File!:\n\t%s\n\t\tReason:Permission denied!\n",path); \
						return FILE_ERR_PERMISSION_DENIED; \
					break; \
					case ENOENT:/* There shouldn't be any possibility left to fall into this case... */ \
						/* printf("\tERROR: Cfg-File doesn't exist!\n"); */ \
						/* printf("\tCreating new one:\n\t\twhile setting every Entry to auto...\n"); */ \
					/* break;*/ \
						return OPERATION_ERR_NEVER_HAPPEN; \
					default: \
						fprintf(stderr, "Ups, seems like we've encountered a case, which isn't caught yet :o("); \
						return MAIN_ERR_FUNC_INCOMPLETE; \
					break; \
				} \
			} \
			break; \
		default: \
			printfc(red,"BUG (Incompleteness):"); \
			printf(" Encountered a case which isn't properly implemented yet (errno: %d). At Default-cfg-File Creation.\n",errno); \
			return MAIN_ERR_FUNC_INCOMPLETE; \
		break; \
		} \
	} \
	printf("Created Default Config-File:\n\t%s\n",path); \
		 \
	SWITCH( \
		EQUAL(FILE_DEFINE,DENKREMENT_CFG_FILE_IDX_MAIN), \
			; \
			, \
		EQUAL(FILE_DEFINE,DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER), \
			char dnsserveraddrip4[]="172.10.0.100"; \
			DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_STR("DNSServerAddrIP4",dnsserveraddrip4); \
			char sdnctrldns[] = "sdncontroller.cocos.de"; \
			DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_STR("SDNControllerAddrDNS",sdnctrldns); \
			DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_INT("SDNControllerPort",8080); \
			DENKR_ESSENTIALS_CFG_FILE_VALUE_WRITE_DEFAULT_INT("SDNControllerPort_DEFAULT",6633); \
			, \
		/* Default: */ \
			; \
	) \
	 \
	fclose(cfgf); \
	/*TODO: fclose err-handling*/ \
	printf("\t...and filled with data.\n\n"); \
	return err; \
}

CREATE__CONFIG_FILE_CREATE_DEFAULT(DENKREMENT_CFG_FILE_IDX_MAIN,DENKREMENT_CFG_FILE_IDX_MAIN,char* path)
CREATE__CONFIG_FILE_CREATE_DEFAULT(DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER,DENKREMENT_CFG_FILE_IDX_SDN_CONTROLLER,char* path)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------
//====================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////////





//int cfg_file__sdn_ctrl__read_complete(){
//	//TODO: currently testing section
//	int err=0;
//
//
//	FILE *cfgf; \
//
//
//	cfgf = fopen(cfg_file, "r"); \
//	if (!cfgf) { \
//		char cfg_file_dir[strlen(ProgPath)+strlen(ABSINT_CFG_FILE_PATH_PREFIX)+1]; \
//		switch(errno) { \
//			case EACCES: \
//				printf("\tERROR: Couldn't open cfg-File!\n\t\tReason:Permission denied!\n"); \
//			break; \
//			case ENOENT: \
//				cfg_file__sdn_ctrl__create_default();
//
//
//				printf("\tERROR: Cfg-File doesn't exist!\n"); \
//				printf("\tCreating new one:\n\t\twhile setting every Entry to auto...\n"); \
//				/*NOT Exclude the preceding '/' from the folder-path*/ \
//				memcpy(cfg_file_dir,ProgPath,strlen(ProgPath)); \
//				memcpy(cfg_file_dir+strlen(ProgPath),ABSINT_CFG_FILE_PATH_PREFIX,strlen(ABSINT_CFG_FILE_PATH_PREFIX)); \
//				cfg_file_dir[sizeof(cfg_file_dir)-1]='\0'; \
//				/*Check the complete Path and eventually create the folders*/ \
//				CREATE_COMPLETE_FOLDER_PATH(cfg_file_dir); \
//				cfgf = fopen(cfg_file, "w+"); \
//				if(!cfgf){ \
//					printf("\t\tERROR: Couldn't create new cfg-file!\n"); \
//					return FILE_ERR_PERMISSION_DENIED; \
//				} \
//				printf("\t\tSetting up config-file with:\n"); \
//				fclose(cfgf); \
//				printf("\t\t...created cfg-file successfully!\n"); \
//				printfc(red,"\tProgram is now exiting!\n"); \
//				printfc(red,"\t\t-->"); \
//				printfc(yellow," -->\n"); \
//				printfc(yellow,"\tPlease configure the cfg-file and start again!\n"); \
//				printf("Exit.\n"); \
//				exit(0); \
//			break; \
//			default: \
//				fprintf(stderr, "Ups, seems like we've encountered a case, which isn't caught yet :o("); \
//				return MAIN_ERR_FUNC_INCOMPLETE; \
//			break; \
//		} \
//
//
//	FILE *cfgf;
//
//	char *testpt=NULL;
//	struct in_addr sdn_ctrl_addr_ip4;
//	DENKR_ESSENTIALS_CFG_FILE_READ_PROCESSING_BRACES(
//		DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_INT("test",err),
//		DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_BUF("test3",testpt),
//		DENKR_ESSENTIALS_CFG_FILE_VALUE_READ_IP4_ADDR("test3",&sdn_ctrl_addr_ip4)
//	);
//
//	if (fclose(cfgf)) { \
//    	printf("NOTICE: Config-File couldn't be closed successfully!"); \
//    } else { \
//    	printf("...config-file read successfully!\n"); \
//    } \
//
//	return err;
//}

int cfg_file__sdn_ctrl__write_value(){

}

int cfg_file__sdn_ctrl__read_value__int(){

}








int check_cfg_files_presence(char** filesv, int filesc, char* returned_missing){
	// Pass the files as a char filesv[][], like the common argv, argc
	int err=0;
	int i;
	FILE *cfgf=NULL;

	for(i=0;i<filesc;i++){
		cfgf = fopen(filesv[i], "r");
	    if(cfgf){
	    	//File Present, no Error, everything fine.
	    	fclose(cfgf);
	    	returned_missing[i]=1;
	    	continue;
		}else{
			switch(errno){
			case ENOENT:
				//File doesn't exist. No 'real error'. Just one of the two actual results, this function want to deliver back.
				returned_missing[i]=0;
				err=MAX(err,1);
				break;
			case EACCES:
				returned_missing[i]=EACCES;
				err=MAX(err,2);
				break;
			default:
				returned_missing[i]=errno;
				err=MAX(err,2);
				break;
			break;
			}
		}
	}

	return err;
}





int cfg_files_init_and_default(char** cfg_files_argv){
	int err=0;
	int i=0;

    //----  Check for Presence and eventually create Default one.
    //--------------------------------------------------------------------------------------------------//
	err=0;
	{
		//Rehash an Array, pointing to the Default-Creation-Functions
		//  Be sure, that all this Indices match right
		//    - Defined Files/Paths inside files/config/DenKrement_cfg_files.h
		//    - Populated Full-Path Entries inside the cfg_files_v above
		//    - Indices, automatically originated, through the Function-Creation for the Default-File-Creation Functions
		//    - Function Pointer Entries inside the now created Array
		int (*cfg_file_default_creation_functions[DENKREMENT_CFG_FILES_QUANTITY])(char* path);
			#define POPULATE_DEF_FUNC_ARR(i, _) \
				cfg_file_default_creation_functions[i]=_CREATE__CONFIG_FILE_CREATE_DEFAULT__FUNCNAME(i);
		EVAL(REPEAT(DENKREMENT_CFG_FILES_QUANTITY, POPULATE_DEF_FUNC_ARR, _))
			#undef POPULATE_DEF_FUNC_ARR
	    //--------------------------------------------------------------------------------------------------//
		char returned_missing[DENKREMENT_CFG_FILES_QUANTITY];
		err=check_cfg_files_presence((char **)cfg_files_argv, DENKREMENT_CFG_FILES_QUANTITY,returned_missing);
		switch(err){
		case 0://Everything fine. Files were present, no errors.
			break;
		case 1:
			;
			int err_overall=0;
			for(i=0;i<DENKREMENT_CFG_FILES_QUANTITY;i++){
				if(!returned_missing[i]){
					err=(*cfg_file_default_creation_functions[i])(cfg_files_argv[i]);
					err_overall=MAX(err_overall,err);
					switch(err){
					case 0:
						//Splendit!
						break;
					case FILE_ERR_PERMISSION_DENIED:
						printfc(red,"ERROR:");
						printf(" Access-Permission denied, while Default-File-Creation of: %s\n",cfg_files_argv[i]);
						return FILE_ERR_PERMISSION_DENIED;
						break;
					default:
						printfc(red,"BUG (Incompleteness):");
						printf(" Encountered a case which isn't properly implemented yet (Internal Error-Code:%d | errno: %d). After Default-cfg-File Creation.\n",err,errno);
						return MAIN_ERR_FUNC_INCOMPLETE;
						break;
					}
				}
			}
			if(!err_overall){
				printfc(yellow,"HINT:");
				printf(" Missing config-File(s) was/were created successfully. Thus exiting. You can adjust the mentioned Files (see above) and restart.\n");
				exit(MAIN_ERR_NONE);
			}else{
				printfc(red,"Unexpected BUG:");printf(" We shouldn't have been able to fall into this case o.O. SHUTDOWN! Reboot and all is good! HELP!\n");
				exit(MAIN_ERR_BUG);
			}
			break;
		case 2://check errno
			for(i=0;i<DENKREMENT_CFG_FILES_QUANTITY;i++){
				switch(returned_missing[i]){
				case EACCES:
					printf("Access-Permission to Config-File denied, while Presence-Checking: %s.\n",cfg_files_argv[i]);
					break;
				default:
					printf("Error (%d) while Presence-Checking Cfg-File: %s.\n",returned_missing[i],cfg_files_argv[i]);
					break;
				}
				printfc(red,"Error.");printf(" Exit...\n");
				exit(MAIN_ERR_STD);
			}
			printfc(red,"ERROR:");
			printf(" Bad Err at config-File 'Presence Checking'/'Default-Creation'. See above. Exit.\n");
			break;
		default:
			printfc(red,"BUG:");
			printf(" Unexpected error-Code at checking of config-File Presence.\n");
			break;
		}
	}
	return err;
}








#undef DENKREMENT_CFG_FILES_C
#undef NO_DENKREMENT_CFG_FILES_C_C_FUNCTIONS
