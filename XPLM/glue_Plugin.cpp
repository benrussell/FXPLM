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
// Created by Ben on 1/11/2025.
//



#include "glue_Plugin.hpp"

#include "PluginContextGuard.h"

#include <string>
#include <dlfcn.h>
#include <filesystem>
#include <iostream>




	Plugin::Plugin( std::string fname ){
		m_plugin_id = plugin_id_ctr;

		namespace fs = std::filesystem;
		m_workingFolder = fs::current_path();

		if ( fname == "XPL_Workbench" ) {
			std::cout<<"FXPLM/ Creating XWB host app plugin instance..\n";

			m_pluginFilename = "XWB.app";

			//these are usually set by XPluginStart()
			m_pluginName = "XWB";
			m_pluginSig = "XWB.app";
			m_pluginDesc = "The host application.";

			m_timer.start();

			m_plugin_is_enabled = true;

		}else {

			m_pluginFilename = fname;

			// name, sig, desc are set by calls to XPluginStart()

			m_timer.start();

			PluginContextGuard ctx(this);

			std::cout<<"FXPLM/ calling dlopen(" << fname << ")\n";
			std::cerr<<"  cwd: [" << std::filesystem::current_path() << "]\n";
			dlerror(); //clear errors.

#define FXPLM_USE_RTLD_NLOAD_CHECK 0
#if FXPLM_USE_RTLD_NLOAD_CHECK
			//check to see if the dylib has already been loaded. macOS
			const auto test_h = dlopen(fname.c_str(), RTLD_NOLOAD);
			if ( test_h ) {
				dlclose( test_h );
				throw std::runtime_error("FXPLM/ plugin already loaded.");
			}
#else
			std::cout << "FXPLM/ FIXME: iterate plugins list and refuse double load of same file.\n";
#endif
#undef FXPLM_USE_RTLD_NLOAD_CHECK

			std::cout<<"FXPLM/ --- xpl static init / begin ---\n";
			{
				m_dlh = dlopen(fname.c_str(), RTLD_NOW | RTLD_LOCAL);
				if (m_dlh == nullptr) {
					// plugin load has failed
					throw std::runtime_error(dlerror()); //we capture this for GUI display
				}
			}
			std::cout<<"FXPLM/ --- xpl static init / end   ---\n";
			printf("FXPLM/  loaded dylib; m_dlh: %p\n", m_dlh);

		} //normal plugin filename

		plugin_id_ctr++;

	} //constructor


	Plugin::~Plugin(){
		std::cout<<"----------------------------\nFXPLM/ ["<< this->m_pluginName <<"]~Plugin()\n";

		this->call_disable();

		this->call_stop();

		for( auto host: m_vecDrawCallbackHost ){
			delete host;
		}

		for( auto host: m_vecAvionicsHost ){
			delete host;
		}


		for( auto params: m_vecWindowHandles ){
			delete params;
		}



		std::cout<<"*** FXPLM/ glue_Plugin: leaking m_vecFlightLoops\n"; //FIXME
		// for( auto flcb: m_vecFlightLoops ){
		// 	delete flcb;
		// }

		for( auto cmd: m_vecCommands ){
			delete cmd;
		}

		std::cout << "FXPLM/ Calling dlclose\n";
		printf("  m_dlh ptr: %p\n", m_dlh);
		if( dlclose( m_dlh ) != 0 ){
			std::cout << "  ~Plugin() failed to dlclose: [" << dlerror() << "] ---------------------------------------\n";
		}
		std::cerr<<"  cwd after dlclose: [" << std::filesystem::current_path() << "]\n";

	} //dtor



	void Plugin::takeContext(){

		if( (void*)this == nullptr ){
			throw std::runtime_error("Plugin::takeContext: 'this' is nullptr.");
		}

		global_target_plugin = this; // inside takeContext()
		// call_xplm_set_context( global_target_plugin );

		m_workingFolder_BeforeContextSwitch = std::filesystem::current_path();
		std::filesystem::current_path(m_workingFolder);
		// std::cout<<"***** takeCtx: " << m_workingFolder_BeforeContextSwitch << "\n";

	}


	void Plugin::releaseContext(){
		global_target_plugin = nullptr; //inside releaseContext()
		// call_xplm_set_context( global_target_plugin );

		std::filesystem::current_path(m_workingFolder_BeforeContextSwitch);
		// std::cout<<"###### release Ctx: " << m_workingFolder_BeforeContextSwitch << "\n";
	}






	void Plugin::run_flcbs(){
		if ( ! m_plugin_is_enabled ) {
			return;
		}

		PluginContextGuard ctx(this);

		auto lam_runCallbackFn = [this](cb_params_t &cb, double delta) {
			//cb.m_lastTimerMillis = now;
			cb.m_lastDelta = delta;

			auto params = cb.params;
			auto xp_delta = static_cast<float>(delta / 1000.0); //x-plane SDK specifies decimal seconds.

			const double dFLCBStart = m_timer.getElapsedTimeInMilliSec();
			const float retVal = (*params.callbackFunc)(
				xp_delta, //float; elapsed since last call
				0.0, //float; elapsed time since last flight loop  //FIXME: this needs to be fixed.
				cb.m_callCounter, //int; call counter
				params.refcon //void*; refcon
				);
			const double dFLCBStop = m_timer.getElapsedTimeInMilliSec();

			cb.profile_ms = dFLCBStop - dFLCBStart;
			//std::cout << "XDbg: retval from clcb_f: " << retVal << "\n";
			cb.interval_secs = retVal;
			cb.interval_millis = static_cast<double>(cb.interval_secs) * 1000.0;

			++cb.m_callCounter;

			//EXPERIMENTAL
			cb.m_lastTimerMillis = m_timer.getElapsedTimeInMilliSec();
		};


//		std::cout<<"plugin->run_flcbs()\n";
		for( auto& cb: m_vecFlightLoops ){
			double now = m_timer.getElapsedTimeInMilliSec();
			double delta = now - cb.m_lastTimerMillis;
//			std::cout<<"  now: " << delta << "\n";
//			std::cout<<"  delta: " << delta << "\n";
//			std::cout<<"  interval: " << cb.interval_millis << "\n";


			if( cb.interval_secs > 0.0 && ! cb.m_paused ){
				//flcb intervals are decimal seconds
				//timer data is decimal millis
				if( delta > cb.interval_millis ){
					lam_runCallbackFn( cb, delta );
				}

			}else if( cb.interval_secs < 0.0 && ! cb.m_paused ){
				//interval is in frames
				cb.frames_since_last_call -= 1.f;
				if ( cb.interval_secs <= cb.frames_since_last_call ) {
					//std::cout << "FXPLM/ flcb neg interval call..\n";
					cb.frames_since_last_call = 0.f;
					lam_runCallbackFn( cb, delta );
				}

			}else{
				//std::cout<<"cb.interval 0\n";
				// interval is set to 0, registered but not scheduled. skip.
			}

		} //loop flcb vec for this plugin

	} //run_flcbs


	void Plugin::flcb_set( XPLMFlightLoopID id, float interval, int rel_now ){
		//FIXME: why are we using offset -1 ??
		auto target = (size_t)id-1;
		// std::cout<< "FXPLM/ flcb_set: " << target << "\n";
		// std::cout<<"FXPLM/     size: "<< m_vecFlightLoops.size() << "\n";
		// std::cout<<"FXPLM/   size-1: "<< m_vecFlightLoops.size()-1 << "\n";
		if( target > m_vecFlightLoops.size()-1 ){
			std::cout<< "FXPLM/ flcb_set: invalid target\n";
			return;
		}else{
			// std::cout << "FXPLM/   flcb_set, found target\n";
			auto cb_params = m_vecFlightLoops[target];

			//std::cout << " p: " << std::to_string((size_t)&cb_params.params) << "\n";
			// printf("FXPLM/  params: %p\n", &cb_params.params);
			// std::cout << "FXPLM/    interval: " << std::to_string(cb_params.interval_secs) << "\n";
			// std::cout << "FXPLM/  rel to now: " << std::to_string(cb_params.relative_to_now) << "\n";

			cb_params.interval_secs = interval;
			cb_params.interval_millis = (double)cb_params.interval_secs * 1000.0;
			cb_params.relative_to_now = rel_now;

			// /std::cout<<"FXPLM/   push cb_params back into vec\n";
			m_vecFlightLoops[target] = cb_params;
		}

		//std::cout<<"FXPLM/ flcb_set returning..\n";
	}


	XPLMFlightLoopID Plugin::register_flcb( XPLMCreateFlightLoop_t* p ){

		//std::cout << "FXPLM/ Plugin::register_flcb:\n";
		//printf("FXPLM/  param ptr: %p\n", &p);

		//take a copy of all params
		XPLMCreateFlightLoop_t p2;
		memcpy(&p2, p, sizeof(XPLMCreateFlightLoop_t));

		cb_params_t flcb;
		flcb.params = p2;
		flcb.interval_secs=0.f;
		flcb.interval_millis = flcb.interval_secs * 1000.0;
		flcb.relative_to_now=0;

		m_vecFlightLoops.push_back( flcb );
		return (XPLMFlightLoopID)m_vecFlightLoops.size();
	}



	void Plugin::send_xpl_message( int from, int message, void* param ) {

		if( m_plugin_is_enabled ){
			std::cout<<"FXPLM/ m_dlh["<< m_plugin_id <<"/" << m_pluginSig << "]->XPluginReceiveMessage("
			<< from << ", "
			<< (void*)(int64_t)message << ", "
			<< (void*)param << " "
			")\n";

			PluginContextGuard ctx(this);

			void (*fptr_rx_msg)(int,int,void*);
			fptr_rx_msg = (void (*)(int,int,void*))dlsym( m_dlh, "XPluginReceiveMessage" ); //FIXME: replace with fn sig typedef

			(*fptr_rx_msg)( from, message, param );

		}

	}



	void Plugin::call_disable() {
		if( m_plugin_start_ret_val ) {

			PluginContextGuard ctx(this);

			std::cout<<"------------------------\nFXPLM/ m_dlh["<< m_plugin_id <<"/" << m_pluginSig << "]->XPluginDisable()\n";
			void (*fptr_disable)();
			fptr_disable = (void (*)())dlsym( m_dlh, "XPluginDisable" ); //FIXME: replace with fn sig typedef

			if (fptr_disable) {
				(*fptr_disable)();
				m_plugin_is_enabled = false;
			}else {
				std::cout<<"FXPLM/ plugin has no disable fn. Host App? Broken plugin?\n";
			}

		}else{
			std::cout<<"FXPLM/ m_dlh["<< m_plugin_id <<"/" << m_pluginSig << "]->XPluginDisable - skipped. Plugin refused to start.\n";
		} //check that plugin ever started

	} //call_disable()


	int Plugin::call_enable() {
		m_plugin_enable_ret_val = 0;

		PluginContextGuard ctx(this);

		std::cout<<"------------------------\nFXPLM/ m_dlh["<< m_plugin_id <<"/" << m_pluginSig << "]->XPluginEnable()\n";
		int (*fptr_enable)();
		fptr_enable = (int (*)()) dlsym(m_dlh, "XPluginEnable"); //FIXME: replace with fn sig typedef
		m_plugin_enable_ret_val = (*fptr_enable)();

		std::cout<<"------------------------\nFXPLM/ m_dlh["<< m_plugin_id <<"/" << m_pluginSig << "]->XPluginEnable() finished\n";

		if( ! m_plugin_enable_ret_val ){
			// update Plugin* (this) status vars to show that plugin is disabled.
			std::cout << "FXPLM/ m_dlh->XPluginEnable(): returned 0 and refused to enable.\n";
			m_plugin_is_enabled = false;

		}else{
			m_plugin_is_enabled = true;

		}

		return m_plugin_enable_ret_val;

	}




	int Plugin::call_start( char* name, char* sig, char* desc ) {

		m_plugin_start_ret_val = 0;

		std::cout<<"------------------------\nFXPLM/ m_dlh["<< m_plugin_id <<"]->XPluginStart()\n";
		int (*fptr_start)(char*,char*,char*);
		fptr_start = (int (*)(char*,char*,char*))dlsym( m_dlh, "XPluginStart" ); //FIXME: replace with fn sig typedef
		if( fptr_start ) {

			PluginContextGuard ctx(this);

			m_plugin_start_ret_val = (*fptr_start)(name, sig, desc);

			std::cout<<"------------------------\nFXPLM/ m_dlh["<< m_plugin_id <<"]->XPluginStart() returned: "<< m_plugin_start_ret_val <<"\n";
			std::cout << "FXPLM/ \tplugin: [" << m_pluginFilename << "] identified itself as:\n";

			std::cout << "FXPLM/ \t  name: [" << name << "]\n";
			std::cout << "FXPLM/ \t  sig:  [" << sig << "]\n";
			std::cout << "FXPLM/ \t  desc: [" << desc << "]\n";

			m_pluginName = name;
			m_pluginSig = sig;
			m_pluginDesc = desc;

			//FIXME: search existing plugin pool for clashing id strings.

		}else{
			std::string msg = "------------------------\nFXPLM/ Could not find XPluginStart";
			throw std::runtime_error( msg );
		}


		if( m_plugin_start_ret_val ){
			this->call_enable();

		}else{
			// update Plugin* (this) status vars to show that plugin refused to start.
			std::cout << "------------------------\nFXPLM/ m_dlh->XPluginStart Error: Plugin refused to start and returned 0.\n";
		}


		return m_plugin_start_ret_val;
	}



	void Plugin::call_stop() {
		if( m_plugin_start_ret_val ){

			PluginContextGuard ctx(this);

			std::cout<<"------------------------\nFXPLM/ m_dlh["<< m_plugin_id <<"/" << m_pluginSig << "]->XPluginStop()\n";
			void (*fptr_stop)();
			fptr_stop = (void (*)())dlsym( m_dlh, "XPluginStop" ); //FIXME: replace with fn sig typedef
			(*fptr_stop)();

		}else{
			std::cout<<"------------------------\nFXPLM/ m_dlh["<< m_plugin_id <<"/" << m_pluginSig << "]->XPluginStop - skipped. Plugin refused to start.\n";
		}

	}




const char* Plugin::getSafeSig(){


	if( (void*)this == nullptr ){ //FIXME: this is apparently UB. to properly fix it we need to enforce all deref casts of Plugin* as clean.
		throw std::runtime_error("Plugin::getSafeSig(): Plugin* is nullptr");
	}


	const char* sep = ":";
	const std::string s_plugin_id = std::to_string(m_plugin_id);


	auto lam_splitString = [](const std::string& str, char delimiter) -> std::vector<std::string>{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(str);

		while (std::getline(tokenStream, token, delimiter)) {
			tokens.push_back(token);
		}

		return tokens;
	};


//	if( m_safeSig.empty() ){
		if( m_pluginSig.empty() ){
			auto tokens = lam_splitString(m_pluginFilename, '/');
			const std::string fn_clean =
					tokens[ tokens.size() - 4 ] + "/" +
					tokens[ tokens.size() - 3 ] + "/" +
					tokens[ tokens.size() - 2 ] + "/" +
					tokens[ tokens.size() - 1 ];

			m_safeSig = s_plugin_id + sep + fn_clean;
		}else{
			m_safeSig = s_plugin_id + sep + m_pluginSig;
		}
//	}

	return m_safeSig.c_str();

}

