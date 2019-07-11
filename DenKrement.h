#ifndef DENKREMENT_H
#define DENKREMENT_H

/*
 * Authored by
 * Dennis Krummacker (03.06.14-)
 */






#define CFG_FILE_PATH_FILE_NAME "DenKrement.cfg"
//This becomes preceded onto the StorageFilesPath string variable
#define CFG_FILE_PATH_PREFIX "config/"
//So the complete File-Path is concatenated as
//		StorageFilesPath + CFG_FILE_PATH_PREFIX + CFG_FILE_PATH_FILE_NAME
//				StorageFilesPath has a preceding '/'
//				One should specify the CFG_FILE_PATH_PREFIX including a preceding '/'

#define CFG_FILE_PATH_PREFIX_ADAPTTXPOWER "adapttxpower_"
#define LOG_FILE_PATH_PREFIX_ADAPTTXPOWER "log_adapttxpower_"


#define ETH_ALEN 6


/* libnl 1.x compatibility code */
/*
#if !defined(CONFIG_LIBNL20) && !defined(CONFIG_LIBNL30)
#define nl_sock nl_handle
#endif
*/





void ctrl_c();







#endif /* DENKREMENT_H */
