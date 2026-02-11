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
// Created by Ben on 28/10/2025.
//

#ifndef GLUE_PLUGIN_HPP
#define GLUE_PLUGIN_HPP




#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <dlfcn.h>

#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"

#include "glue_AvionicsHost.hpp"
#include "glue_DrawCallbackHost.hpp"
#include "glue_CmdCustom.hpp"

#include "glue_WindowEx.h"

// #include "../third_party/timer/src/Timer.h"


class Plugin;
//extern Plugin* global_target_plugin;





class Plugin {
private:
	void* m_dlh;

public:
	inline static size_t plugin_id_ctr=0;

public:

	std::string m_workingFolder{};
	std::string m_workingFolder_BeforeContextSwitch{};

	std::string m_pluginName{};
	std::string m_pluginDesc{};
	std::string m_pluginSig{};

	std::string m_pluginFilename{};


	std::vector<AvionicsHost*> m_vecAvionicsHost;
	std::vector<DrawCallbackHost*> m_vecDrawCallbackHost;

	struct cb_params_t;
	std::vector<cb_params_t> m_vecFlightLoops; //FIXME should be *

	std::vector<xpCmdCustom*> m_vecCommands;
	std::vector<xp_dref*> m_vecDrefs;

	//gl texture ids
	std::vector<int> m_vecTextures;

	//XPLMEnableFeature(...)
	std::map<std::string, int> m_mapFeatureFlags;

	//XPLMCreateWindowEx
	std::vector<glue_WindowEx*> m_vecWindowHandles;




	size_t m_plugin_id;
	int m_plugin_start_ret_val=0;
	int m_plugin_enable_ret_val=0;

	bool m_plugin_is_enabled = false;



	Timer m_timer;



	explicit Plugin( std::string fname );
	~Plugin();


	std::string m_safeSig; //work around stack address ret
	const char* getSafeSig();


	void takeContext();
	void releaseContext();


	void run_flcbs();
	void flcb_set( XPLMFlightLoopID id, float interval, int rel_now );
	XPLMFlightLoopID register_flcb( XPLMCreateFlightLoop_t p );


	void send_xpl_message( int from, int message, void* param );

	void call_disable();
	int call_enable();

	int call_start( char*, char*, char* );
	void call_stop();


};





// flight loop struct
struct Plugin::cb_params_t{
	XPLMCreateFlightLoop_t params{};
	float interval_secs=0.f; //FIXME: duplicated? avail in params?
	int relative_to_now=1;

	float frames_since_last_call=0.f;

	double interval_millis=0.0;

	double m_lastTimerMillis=0.0;
	size_t m_callCounter=0;
	double m_lastDelta=0.0;

	double profile_ms=0.0;
	std::string name{};

	bool m_paused=false;
};









#endif //GLUE_PLUGIN_HPP
