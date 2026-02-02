//
//  XPLMPlanes.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "XPLMPlanes.h"
#include "XPLM.h"

#include <iostream>



void XPLMGetNthAircraftModel( //FIXME: where are the buffer size reqs defined?
    int inIndex,
    char* outFileName,
    char* outPath
){

	std::cout << "FXPLM/ ["<< global_target_plugin->getSafeSig()
			  << "] XPLMGetNthAircraftModel:";

	std::cout << " index:" << inIndex << "\n";


    if( ! outFileName ){
        std::cout << "FXPLM/   outFileName is nullptr\n";
    }else{
        snprintf( outFileName, 256, "Cessna_172.acf" );
        std::cout << "  outFilename: ["<< outFileName <<"]\n";
    }
    

    if( ! outPath ){
        std::cout << "FXPLM/   outPath is nullptr\n";
    }else{
        snprintf( outPath, 512, "Aircraft/Laminar Research/Cessna 172 SP" );
		std::cout << "  outPath: ["<< outPath <<"]\n";
    }
    
}



XPLM_API int        XPLMAcquirePlanes(
                         char **              inAircraft,    /* Can be NULL */
                         XPLMPlanesAvailable_f inCallback,
                         void *               inRefcon) {
    std::cerr<<"FXPLM/ NOP/ XPLMAcquirePlanes\n";
    return 0;
}


XPLM_API void       XPLMCountAircraft(
                         int *                outTotalAircraft,
                         int *                outActiveAircraft,
                         XPLMPluginID *       outController) {
    std::cerr<<"FXPLM/ NOP/ XPLMCountAircraft\n";
}


XPLM_API void       XPLMPlaceUserAtAirport(
                         const char *         inAirportCode) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMPlaceUserAtAirport");
}


XPLM_API void       XPLMPlaceUserAtLocation(
                         double               latitudeDegrees,
                         double               longitudeDegrees,
                         float                elevationMetersMSL,
                         float                headingDegreesTrue,
                         float                speedMetersPerSecond) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMPlaceUserAtLocation");
}



XPLM_API void       XPLMReleasePlanes(void) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMReleasePlanes");
}


XPLM_API void       XPLMSetActiveAircraftCount(
                         int                  inCount) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMSetActiveAircraftCount");
}





