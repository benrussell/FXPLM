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



XPLM_API void       XPLMSetUsersAircraft(
                         const char *         inAircraftPath) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMSetUsersAircraft");
}

