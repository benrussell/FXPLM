/*
 * FXPLM - A re-impl of the X-Plane XPLM layer.
 * Copyright (C) 2024-2026 Ben Russell - br@x-plugins.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

//
//  XPLMPlugin.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "XPLMPlugin.h"

#include <cstring>
#include <iostream>

#include "glue_Plugin.hpp"
#include "XPLM.h"


namespace XPHost {
    extern std::vector<Plugin*> m_vecPlugins;
}


void XPLMEnableFeature( const char* feature_name ){

//    if( strcmp(feature_name, "XPLM_USE_NATIVE_PATHS") != 0 ){
//        // mute the native paths request as thats all we support
//        std::cout << "FXPLM/ XPLMEnableFeature(["<< feature_name <<"]): NOP\n";
//    }

	FXPLM_DebugLogHeader("XPLMEnableFeature");

    if( global_target_plugin ){
		global_target_plugin->m_mapFeatureFlags[ feature_name ] = 1;

		if( strcmp(feature_name, "XPLM_USE_NATIVE_PATHS") != 0 ){
        	// mute the native paths request as thats all we support
	        std::cout << " ["<< feature_name <<"]: Set. (DOES NOTHING)\n";
    	}else{
			std::cout << " ["<< feature_name <<"]: Set.\n";
		}

	}else{
    	throw std::runtime_error("FXPLM/ XPLMEnableFeature/ no target plugin.");
    }

}



int XPLMGetMyID( void ){

	FXPLM_DebugLogHeader("XPLMGetMyID");
	std::cout << "ret:" << global_target_plugin->m_plugin_id << "\n";

    return global_target_plugin->m_plugin_id;
}

void XPLMGetPluginInfo(
    int pluginId,
    char* outName,
    char* outFilePath,
    char* outSignature,
    char* outDescription
){

	FXPLM_DebugLogHeader("XPLMGetPluginInfo");
	std::cout << " id:" << pluginId;

    const int targetId = pluginId;
    if ( targetId > XPHost::m_vecPlugins.size() ) {
        std::cout << " *** targetId " << targetId << " is out of bounds. ***\n";
        throw std::runtime_error("XPLMGetPluginInfo: targetId is out of bounds.");
    }
    auto plugin = XPHost::m_vecPlugins[targetId];
    
    
    if( outName ){
        std::cout << " / ret name:[" << plugin->m_pluginName << "]";
        snprintf(outName,256,
            "%s",
            plugin->m_pluginName.c_str()
        );
    }

    if( outFilePath ){
        std::cout << " / ret file_path:[" << plugin->m_pluginFilename << "]";
        snprintf(outFilePath,256,
            "%s",
            plugin->m_pluginFilename.c_str()
        );
    }

    if( outSignature ){
        std::cout << " / ret sig:[" << plugin->m_pluginSig << "]";
        snprintf(outSignature,256,
            "%s",
            plugin->m_pluginSig.c_str()
        );
    }

    if( outDescription ){
        std::cout << " / ret desc:[" << plugin->m_pluginDesc << "]";
        snprintf(outDescription,256,
            "%s",
            plugin->m_pluginDesc.c_str()
        );
    }

	std::cout << " \n";
}





XPLM_API int        XPLMCountPlugins(void) {
    return XPHost::m_vecPlugins.size();
}



XPLM_API int XPLMIsPluginEnabled( XPLMPluginID plugin_id ) {
//    FXPLM_DebugLogHeader("XPLMIsPluginEnabled");
//    std::cout << " plugin_id:" << plugin_id << "\n";

    if ( plugin_id == 0 ) {
        // host is always enabled.
        return 1;
    }

    size_t target_id = plugin_id;
    if( target_id >= XPHost::m_vecPlugins.size() ){
        std::cerr << "XPLMIsPluginEnabled:  target_id out of range: " << target_id << "\n";
        return 0;
    }
    auto target = XPHost::m_vecPlugins[target_id];

    return target->m_plugin_is_enabled;

}



XPLM_API int        XPLMEnablePlugin(
                         XPLMPluginID         inPluginID) {

    size_t target_id = inPluginID;
    if( target_id >= XPHost::m_vecPlugins.size() ){
        std::cerr << "XPLMEnablePlugin:  target_id out of range: " << target_id << "\n";
        return 0;
    }
    auto target = XPHost::m_vecPlugins[target_id];

    return target->call_enable();

}

XPLM_API void       XPLMDisablePlugin(
                         XPLMPluginID         inPluginID) {
    size_t target_id = inPluginID;
    if( target_id >= XPHost::m_vecPlugins.size() ){
        std::cerr << "XPLMDisablePlugin:  target_id out of range: " << target_id << "\n";
        return;
    }
    auto target = XPHost::m_vecPlugins[target_id];

    target->call_disable();

}

XPLM_API void       XPLMReloadPlugins(void) {
    std::cerr<<"FXPLM/ NOP/ XPLMReloadPlugins()\n";
}



XPLM_API int        XPLMIsFeatureEnabled(
                         const char *         inFeature) {


	if( global_target_plugin ){
		const auto& flags = global_target_plugin->m_mapFeatureFlags;

		auto it = flags.find(inFeature);
		if( it != flags.end() ){
			//found it
//			std::cout << "FXPLM/ XPLMIsFeatureEnabled(["<< inFeature <<"]): Enabled.\n";
			return 1;
		}else{
			//did not find it
			std::cout << "FXPLM/ XPLMIsFeatureEnabled(["<< inFeature <<"]): Disabled.\n";
			return 0;
		}

	}else{
		throw std::runtime_error("FXPLM/ XPLMIsFeatureEnabled/ no target plugin.");
	}

}




XPLM_API XPLMPluginID XPLMFindPluginByPath(
                         const char *         inPath) {
    std::cout<<"FXPLM/ NOP/ XPLMFindPluginByPath(["<< inPath <<"])\n";
    return 1;
}


XPLM_API XPLMPluginID XPLMGetNthPlugin(
                         int                  inIndex) {
    std::cout<<"FXPLM/ XPLMGetNthPlugin(["<< inIndex <<"])\n";
    return inIndex;
}