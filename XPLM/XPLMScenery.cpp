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
// Created by Ben on 20/11/2025.
//

#include "XPLMScenery.h"

#include <iostream>

#include "XPLM.h"


XPLM_API XPLMProbeRef XPLMCreateProbe(
						 XPLMProbeType        inProbeType) {

	FXPLM_DebugLogHeader("NOP/ XPLMCreateProbe");
	std::cout << " probe_type:" << inProbeType;

	std::cout << " / ret_hc:nullptr\n";

	return nullptr;
}


XPLM_API void       XPLMDestroyProbe(XPLMProbeRef inProbe) {
	FXPLM_DebugLogHeader("NOP/ XPLMDestroyProbe");
	std::cerr<<"\n";
}


XPLM_API XPLMProbeResult XPLMProbeTerrainXYZ(
						 XPLMProbeRef         inProbe,
						 float                inX,
						 float                inY,
						 float                inZ,
						 XPLMProbeInfo_t *    outInfo) {
	std::cerr<<"FXPLM/ NOP/ XPLMProbeTerrainXYZ\n";
	return xplm_ProbeError;
}




XPLM_API float      XPLMGetMagneticVariation(
						 double               latitude,
						 double               longitude) {
	std::cerr<<"FXPLM/ NOP/ XPLMGetMagneticVariation\n";
	return 0.f;
}


XPLM_API float      XPLMDegTrueToDegMagnetic(
float                headingDegreesTrue) {
	std::cerr<<"FXPLM/ NOP/ XPLMDegTrueToDegMagnetic\n";
	return 0.f;
}

XPLM_API float      XPLMDegMagneticToDegTrue(
float                headingDegreesMagnetic) {
	std::cerr<<"FXPLM/ NOP/ XPLMDegMagneticToDegTrue\n";
	return 0.f;
}





XPLM_API XPLMObjectRef XPLMLoadObject(
const char *         inPath) {
	std::cerr<<"FXPLM/ NOP/ XPLMDegMagneticToDegTrue\n";
	return nullptr;
}


XPLM_API void       XPLMLoadObjectAsync(
						 const char *         inPath,
						 XPLMObjectLoaded_f   inCallback,
						 void *               inRefcon) {
	std::cerr<<"FXPLM/ NOP/ XPLMLoadObjectAsync\n";
}


XPLM_API void       XPLMDrawObjects(
						 XPLMObjectRef        inObject,
						 int                  inCount,
						 XPLMDrawInfo_t *     inLocations,
						 int                  lighting,
						 int                  earth_relative) {
	std::cerr<<"FXPLM/ NOP/ XPLMDrawObjects\n";
}



XPLM_API void       XPLMUnloadObject(
XPLMObjectRef        inObject) {
	std::cerr<<"FXPLM/ NOP/ XPLMUnloadObject\n";
}



XPLM_API int        XPLMLookupObjects(
						 const char *         inPath,
						 float                inLatitude,
						 float                inLongitude,
						 XPLMLibraryEnumerator_f enumerator,
						 void *               ref) {
	std::cerr<<"FXPLM/ NOP/ XPLMLookupObjects\n";
	return 0;
}




