//
// Created by Ben on 20/11/2025.
//

#include "XPLMMap.h"

#include <iostream>




XPLM_API XPLMMapLayerID XPLMCreateMapLayer(
						 XPLMCreateMapLayer_t * inParams) {
	std::cerr<<"FXPLM/ NOP/ XPLMCreateMapLayer\n";
	return nullptr;
}


XPLM_API int        XPLMDestroyMapLayer(
XPLMMapLayerID       inLayer) {
	std::cerr<<"FXPLM/ NOP/ XPLMDestroyMapLayer\n";
	return 0;
}




XPLM_API void       XPLMRegisterMapCreationHook(
						 XPLMMapCreatedCallback_f callback,
						 void *               refcon) {
	std::cerr<<"FXPLM/ NOP/ XPLMRegisterMapCreationHook\n";
}


XPLM_API int        XPLMMapExists(
const char *         mapIdentifier) {
	std::cerr<<"FXPLM/ NOP/ XPLMMapExists\n";
	return 0;
}





XPLM_API void       XPLMDrawMapIconFromSheet(
						 XPLMMapLayerID       layer,
						 const char *         inPngPath,
						 int                  s,
						 int                  t,
						 int                  ds,
						 int                  dt,
						 float                mapX,
						 float                mapY,
						 XPLMMapOrientation   orientation,
						 float                rotationDegrees,
						 float                mapWidth) {
	std::cerr<<"FXPLM/ NOP/ XPLMDrawMapIconFromSheet\n";
}


XPLM_API void       XPLMDrawMapLabel(
						 XPLMMapLayerID       layer,
						 const char *         inText,
						 float                mapX,
						 float                mapY,
						 XPLMMapOrientation   orientation,
						 float                rotationDegrees) {
	std::cerr<<"FXPLM/ NOP/ XPLMDrawMapLabel\n";
}


XPLM_API void       XPLMMapProject(
						 XPLMMapProjectionID  projection,
						 double               latitude,
						 double               longitude,
						 float *              outX,
						 float *              outY) {
	std::cerr<<"FXPLM/ NOP/ XPLMMapProject\n";
}



XPLM_API void       XPLMMapUnproject(
						 XPLMMapProjectionID  projection,
						 float                mapX,
						 float                mapY,
						 double *             outLatitude,
						 double *             outLongitude) {
	std::cerr<<"FXPLM/ NOP/ XPLMMapUnproject\n";
}


XPLM_API float      XPLMMapScaleMeter(
						 XPLMMapProjectionID  projection,
						 float                mapX,
						 float                mapY) {
	std::cerr<<"FXPLM/ NOP/ XPLMMapScaleMeter\n";
	return 1.f;
}


XPLM_API float      XPLMMapGetNorthHeading(
						 XPLMMapProjectionID  projection,
						 float                mapX,
						 float                mapY) {
	std::cerr<<"FXPLM/ NOP/ XPLMMapGetNorthHeading\n";
	return 0.f;
}


