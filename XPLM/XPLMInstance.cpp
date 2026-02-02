//
// Created by Ben on 20/11/2025.
//

#include "XPLMInstance.h"

#include <iostream>

XPLM_API XPLMInstanceRef XPLMCreateInstance(
						 XPLMObjectRef        obj,
						 const char **        datarefs) {
	std::cerr<<"FXPLM/ NOP/ XPLMCreateInstance\n";
	return nullptr;
}

XPLM_API void       XPLMInstanceSetAutoShift(
						 XPLMInstanceRef      instance) {
	std::cerr<<"FXPLM/ NOP/ XPLMInstanceSetAutoShift\n";
}

XPLM_API void       XPLMDestroyInstance(
XPLMInstanceRef      instance) {
	std::cerr<<"FXPLM/ NOP/ XPLMDestroyInstance\n";
}


XPLM_API void       XPLMInstanceSetPosition(
						 XPLMInstanceRef      instance,
						 const XPLMDrawInfo_t * new_position,
						 const float *        data) {
	std::cerr<<"FXPLM/ NOP/ XPLMInstanceSetPosition\n";
}



XPLM_API void       XPLMInstanceSetPositionDouble(
						 XPLMInstanceRef      instance,
						 const XPLMDrawInfoDouble_t * new_position,
						 const float *        data) {
	std::cerr<<"FXPLM/ NOP/ XPLMInstanceSetPositionDouble\n";
}

