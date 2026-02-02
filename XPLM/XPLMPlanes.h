//
//  XPLMPlanes.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef XPLMPlanes_hpp
#define XPLMPlanes_hpp

#include "defs.h"

#include <stdio.h>

#include "XPLMPlugin.h"

XPLM_API void XPLMGetNthAircraftModel(
    int inIndex,
    char* outFilename, // [256]
    char* outPath // [512]
);


typedef void (* XPLMPlanesAvailable_f)(
                         void *               inRefcon);


XPLM_API int        XPLMAcquirePlanes(
						 char **              inAircraft,    /* Can be NULL */
						 XPLMPlanesAvailable_f inCallback,
						 void *               inRefcon);



XPLM_API void       XPLMCountAircraft(
						 int *                outTotalAircraft,
						 int *                outActiveAircraft,
						 XPLMPluginID *       outController);


XPLM_API void       XPLMPlaceUserAtAirport(
						 const char *         inAirportCode);



XPLM_API void       XPLMPlaceUserAtLocation(
						 double               latitudeDegrees,
						 double               longitudeDegrees,
						 float                elevationMetersMSL,
						 float                headingDegreesTrue,
						 float                speedMetersPerSecond);


XPLM_API void       XPLMReleasePlanes(void);


XPLM_API void       XPLMSetActiveAircraftCount(
						 int                  inCount);





#endif /* XPLMPlanes_hpp */
