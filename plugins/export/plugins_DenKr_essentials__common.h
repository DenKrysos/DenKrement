/*
 * DenKrement_plugins.h
 *
 *  Created on: 26.07.2017
 *      Author: Dennis Krummacker
 */

#ifndef PLUGINS__EXPORT__PLUGINS_DENKR_ESSENTIALS__COMMON_H
#define PLUGINS__EXPORT__PLUGINS_DENKR_ESSENTIALS__COMMON_H







//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//==================================================================================================//
//--------------------------------------------------------------------------------------------------//
//----  This section contains essential stuff for the !!! DenKr_essentials !!! Library  ------------//
//----  It's Values are needed by the DL_Libs Part  ------------------------------------------------//
//----  So you better use it as a Template  --------------------------------------------------------//
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//

#define DenKr_plugin_roles_ENTRIES \
	DenKr_plugin_role__Context_Broker__External_Connector_Python,\
	DenKr_plugin_role__SDN_link_monitoring,\
	DenKr_plugin_role__network_topology_discovery,\
	DenKr_plugin_role__QoS,\
	DenKr_plugin_role__SDN_topology_adjust

typedef enum DenKr_plugin_roles_t{
	//===================================================================
	//Define your own predefined Roles here (i.e. replace the ones here)
	DenKr_plugin_roles_ENTRIES,
	//===================================================================
	DenKr_plugin_role__MAX,
	DenKr_plugin_role__generic,
			//Reworked: Don't need this anymore:
			//	DenKr_plugin_role__undefined,
			//	DenKr_plugin_role__generic,
			//		DenKr_plugin_role__general = DenKr_plugin_role__generic,
			//		DenKr_plugin_role__extension = DenKr_plugin_role__generic,
			//		DenKr_plugin_role__not_predefined = DenKr_plugin_role__generic,
			//	//-------------------------------------------------------------------
			//	DenKr_plugin_role__MAX,
			//	DenKr_plugin_role__MAX_Excluding_generic = DenKr_plugin_role__MAX - 1,
			//	DenKr_plugin_role__MAX_predefined = DenKr_plugin_role__MAX_Excluding_generic - 1,
			//	DenKr_plugin_role__MAX_Dummy //to restore the Highest Value
}DenKr_plugin_roles;
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

//////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------//
//==================================================================================================//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////










#endif /* PLUGINS__EXPORT__PLUGINS_DENKR_ESSENTIALS__COMMON_H */
