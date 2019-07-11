/*
 * DenKrement_funny.c
 *
 *  Created on: 04.09.2017
 *      Author: Dennis Krummacker
 */


#define DENKREMENT_FUNNY_C
#define NO_DENKREMENT_FUNNY_C_C_FUNCTIONS



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
#include <errno.h>
#include <string.h>
//==================================================================================================//
//==================================================================================================//
//==================================================================================================//
//Then include own Headers  -------------------------------------------------------
//   Format: Use "NAME" for them  -------------------------------------------------
//#include "DenKrement_cfg_files.h"
//---------------------------------------------------------------------------------
#include "DenKr_essentials/PreC/DenKr_PreC.h"
#include "DenKr_essentials/auxiliary.h"
#include "DenKr_essentials/DenKr_errno.h"
#include "DenKr_essentials/Terminal/ascii.h"
#include "DenKr_essentials/Terminal/ansi.h"
//==================================================================================================//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//








int Cmd_Line_Mux_funny(int argc, char **argv){
	int err=0;
	int argc_proc=argc; char **argv_proc=argv;
	int i;

#define print_invalid_arguments__funny(WRONG_AFTER) \
		printfc(red,"ERROR:");printf(" Invalid arguments after \"DenKrement funny\" with:\n\t"); \
		for(i=0;i<argc;i++) \
			printf(" %s", *(argv+i)); \
		printf("\n"); \
		printf("Wrong after \""WRONG_AFTER"\".\n"); \
		puts("");

#define print_few_arguments__funny(WRONG_AFTER) \
		printfc(red,"ERROR:");printf(" Too few arguments to bring the funny stuff to work...\n\t"); \
		for(i=0;i<argc;i++) \
			printf(" %s", *(argv+i)); \
		printf("\n"); \
		printf("Too few after: \""WRONG_AFTER"\".\n"); \
		puts("");

#define print_valid_arguments__funny \
		printfc(blue,"INFO:");printf(" Valid arguments for DenKrement funny are:\n"); \
		printf("\tprint\n"); \
		printf("\t\tpokemon\n"); \
		printf("\t\t\tstarter\n"); \
		printf("\t\t\t\t1stGen\n"); \
		printf("\t\t\tbulbasaur \t(Alternative: bisasam)\n"); \
		printf("\t\t\t\t(standalone)\n"); \
		printf("\t\t\t\tansi \t(same as \"standalone\")\n"); \
		printf("\t\t\t\tascii\n"); \
		printf("\t\t\t\tascii_color\n"); \
		puts("");

	if(argc_proc>0){
		if(strcmp(*argv_proc, "print") == 0){
			argc_proc--;argv_proc++;
			if(argc_proc>0){
				if(strcmp(*argv_proc, "pokemon") == 0){
					argc_proc--;argv_proc++;
					if(argc_proc>0){
						if(strcmp(*argv_proc, "starter") == 0){
							argc_proc--;argv_proc++;
							if(argc_proc>0){
								if(strcmp(*argv_proc, "1stGen") == 0){
									print_ANSI_Pokemon_Starter_1st_Gen_8Bit();
									return 0;
								}else{
									print_invalid_arguments__funny("print pokemon starter")
									return MAIN_ERR_BAD_CMDLINE;
								}
							}else{
								print_few_arguments__funny("print pokemon starter")
								return MAIN_ERR_FEW_CMDS;
							}
						}else if((strcmp(*argv_proc, "bulbasaur") == 0) || (strcmp(*argv_proc, "bisasam") == 0)){
							argc_proc--;argv_proc++;
							if(argc_proc>0){
								if(strcmp(*argv_proc, "ansi") == 0){
									print_ANSI_Pokemon_Bulbasaur();
									return 0;
								}else if(strcmp(*argv_proc, "ascii") == 0){
									print_ASCII_Pokemon_Bulbasaur_monochrom();
									return 0;
								}else if(strcmp(*argv_proc, "ascii_color") == 0){
									print_ASCII_ANSI_Pokemon_Bulbasaur();
									return 0;
								}else{
									print_invalid_arguments__funny("print pokemon bulbasaur")
									return MAIN_ERR_BAD_CMDLINE;
								}
							}else{
								print_ANSI_Pokemon_Bulbasaur();
								return 0;
							}
						}else{
							print_invalid_arguments__funny("print pokemon")
							return MAIN_ERR_BAD_CMDLINE;
						}
					}else{
						print_few_arguments__funny("print pokemon")
						return MAIN_ERR_FEW_CMDS;
					}
				}else{
					print_invalid_arguments__funny("print")
					return MAIN_ERR_BAD_CMDLINE;
				}
			}else{
				print_few_arguments__funny("print")
				return MAIN_ERR_FEW_CMDS;
			}
		}else{
			print_invalid_arguments__funny("funny")
			print_valid_arguments__funny
			return MAIN_ERR_BAD_CMDLINE;
		}
	}else{
		print_few_arguments__funny("funny")
		print_valid_arguments__funny
		return MAIN_ERR_FEW_CMDS;
	}

#undef print_invalid_arguments__funny
#undef print_few_arguments__funny
#undef print_valid_arguments__funny
	return err;
}







#undef DENKREMENT_FUNNY_C
#undef NO_DENKREMENT_FUNNY_C_C_FUNCTIONS
