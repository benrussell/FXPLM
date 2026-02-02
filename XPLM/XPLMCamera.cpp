//
// Created by Ben on 20/11/2025.
//

#include "XPLMCamera.h"

#include <iostream>



XPLM_API void       XPLMControlCamera(
						 XPLMCameraControlDuration inHowLong,
						 XPLMCameraControl_f  inControlFunc,
						 void *               inRefcon) {
	std::cerr<<"FXPLM/ NOP/ XPLMControlCamera\n";
}


XPLM_API void       XPLMDontControlCamera(void) {
	std::cerr<<"FXPLM/ NOP/ XPLMDontControlCamera\n";
}


XPLM_API int        XPLMIsCameraBeingControlled(
						 XPLMCameraControlDuration * outCameraControlDuration)    /* Can be NULL */
{
	std::cerr<<"FXPLM/ NOP/ XPLMIsCameraBeingControlled\n";
	return 0;
}

XPLM_API void       XPLMReadCameraPosition(
					XPLMCameraPosition_t * outCameraPosition) {
	std::cerr<<"FXPLM/ NOP/ XPLMReadCameraPosition\n";
}