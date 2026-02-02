//
//  XPLMProcessing.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "XPLMProcessing.h"
#include "XPLM.h"
#include <iostream>

#include "glue_Plugin.hpp"
//extern Plugin* global_target_plugin;


XPLMFlightLoopID XPLMCreateFlightLoop( XPLMCreateFlightLoop_t* loop_params ){

	FXPLM_DebugLogHeader("XPLMCreateFlightLoop");
	printf("  params:%p", loop_params);
    printf("  sz:%i", loop_params->structSize);
    printf("  phase:%i", loop_params->phase);
    printf("  cbf:%p", loop_params->callbackFunc);
    printf("  refcon:%p\n", loop_params->refcon);

    if( global_target_plugin ){
        return (void*)global_target_plugin->register_flcb( *loop_params );
    }else{
        std::cout<<" XPLMCreateFlightLoop failed; bad plugin ptr\n";
    }

    return nullptr;
}


[[maybe_unused]] void XPLMDestroyFlightLoop(XPLMFlightLoopID     inFlightLoopID){
	FXPLM_DebugLogHeader("NOP/ XPLMDestroyFlightLoop");
	std::cout << " inFlightLoopID:" << (void*)inFlightLoopID;
	std::cout << "\n";
}


// this pairs with CreateFlightLoop() and is required to get any work done.
[[maybe_unused]] void XPLMScheduleFlightLoop(
        XPLMFlightLoopID     inFlightLoopID,
        float                inInterval,
        int                  inRelativeToNow){

	FXPLM_DebugLogHeader("XPLMScheduleFlightLoop");
    std::cout << "  FlightLoopID:" << inFlightLoopID << "";
    std::cout << "  inInterval:" << inInterval << "";
    std::cout << "  inRelativeToNow:" << inRelativeToNow << "";
	std::cout << "\n";

    if( global_target_plugin ){
        global_target_plugin->flcb_set( inFlightLoopID, inInterval, inRelativeToNow );

    }else{
        std::cout << "  XPLMScheduleFlightLoop failed: bad global_target_plugin ptrn\n";
    }

}




float XPLMGetElapsedTime(){
    // This is probably slightly different from X-Plane behaviour.
    // The X-Plane timer has "feature" where it stalls during various operations.
    FXPLM_DebugLogHeader("XPLMGetElapsedTimer");
    std::cout << "\n";

	static XPLMDataRef dr = nullptr;
	if ( ! dr ) {
		dr = XPLMFindDataRef("sim/time/total_running_time_sec");
	}
	const float ret = XPLMGetDataf( dr );

	std::cout << " ret:" << ret;
	std::cout << "\n";

    return ret;

}


[[maybe_unused]] void       XPLMRegisterFlightLoopCallback(
                         XPLMFlightLoop_f     inFlightLoop,
                         float                inInterval,
                         void *               inRefcon) {

	FXPLM_DebugLogHeader("XPLMRegisterFlightLoopCallback");
	std::cout << "  FlightLoop_f:" << inFlightLoop;
	std::cout << "  inInterval:" << inInterval;
	std::cout << "  inRefcon:" << inRefcon;
	std::cout << "\n";

	// This is a legacy FLCB call, we auto wrap it in calls to the newer
	// XPLMCreateFlightLoop() params data.

	XPLMCreateFlightLoop_t params;
	params.structSize = sizeof( XPLMCreateFlightLoop_t );
	params.refcon = inRefcon;
	params.phase = xplm_FlightLoop_Phase_BeforeFlightModel; //legacy call can only do these.
	params.callbackFunc = inFlightLoop;

	auto fl_id = XPLMCreateFlightLoop( &params );

	XPLMScheduleFlightLoop( fl_id, inInterval, 0 );

}



[[maybe_unused]] void       XPLMUnregisterFlightLoopCallback(
                         XPLMFlightLoop_f     inFlightLoop,
                         void *               inRefcon) {
	FXPLM_DebugLogHeader("XPLMUnregisterFlightLoopCallback");
	std::cout << "  inFlightLoop:" << inFlightLoop;
	std::cout << "  inRefcon:" << inRefcon;
	std::cout << "\n";

	std::vector<Plugin::cb_params_t> vecKeepers;
	vecKeepers.reserve(global_target_plugin->m_vecFlightLoops.size());

	//iterate all fl's and find a candidate.
	for( const auto& fl: global_target_plugin->m_vecFlightLoops ){
		int match_count = 0;

		if( fl.params.callbackFunc == inFlightLoop ){
			//std::cout << "  unreg: matching flcb func ptr\n";
			++match_count;
		}

		if( fl.params.refcon == inRefcon ){
			//std::cout << "  unreg: matching refcon ptr\n";
			++match_count;
		}

		if( match_count == 2 ){
			//std::cout << "  unreg: found a valid target to unregister" << (void*)fl.params.callbackFunc << "\n";
		}else{
			vecKeepers.emplace_back(fl);
		}

	} //iterate fl vec

	global_target_plugin->m_vecFlightLoops.swap(vecKeepers);

} //XPLMUnregisterFlightLoopCallback(..)






