//
//  XPLMProcessing.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef XPLMProcessing_hpp
#define XPLMProcessing_hpp

#include "defs.h"

//#include <stdio.h>
#include <cstdio>



enum XPLMFlightLoopPhaseType{
    xplm_FlightLoop_Phase_BeforeFlightModel,
	xplm_FlightLoop_Phase_AfterFlightModel
};

typedef float (* XPLMFlightLoop_f)(
        float                inElapsedSinceLastCall,
        float                inElapsedTimeSinceLastFlightLoop,
        int                  inCounter,
        void *               inRefcon);

typedef struct {
    int                       structSize;
    XPLMFlightLoopPhaseType   phase;
    XPLMFlightLoop_f          callbackFunc;
    void *                    refcon;
} XPLMCreateFlightLoop_t;

typedef void * XPLMFlightLoopID;



XPLM_API float XPLMGetElapsedTime();

XPLM_API XPLMFlightLoopID XPLMCreateFlightLoop( XPLMCreateFlightLoop_t* loop_params );

XPLM_API void XPLMDestroyFlightLoop(XPLMFlightLoopID     inFlightLoopID);


XPLM_API void XPLMScheduleFlightLoop(
        XPLMFlightLoopID     inFlightLoopID,
        float                inInterval,
        int                  inRelativeToNow);


XPLM_API void       XPLMRegisterFlightLoopCallback(
						 XPLMFlightLoop_f     inFlightLoop,
						 float                inInterval,
						 void *               inRefcon);


XPLM_API void       XPLMUnregisterFlightLoopCallback(
						 XPLMFlightLoop_f     inFlightLoop,
						 void *               inRefcon);


#endif /* XPLMProcessing_hpp */
