//
// Created by Ben on 20/11/2025.
//

#ifndef XPLMINSTANCE_H
#define XPLMINSTANCE_H


#include "defs.h"

#include "XPLMScenery.h"


typedef void * XPLMInstanceRef;

XPLM_API XPLMInstanceRef XPLMCreateInstance(
						 XPLMObjectRef        obj,
						 const char **        datarefs);

XPLM_API void       XPLMInstanceSetAutoShift(
						 XPLMInstanceRef      instance);

XPLM_API void       XPLMDestroyInstance(
						 XPLMInstanceRef      instance);


XPLM_API void       XPLMInstanceSetPosition(
						 XPLMInstanceRef      instance,
						 const XPLMDrawInfo_t * new_position,
						 const float *        data);


XPLM_API void       XPLMInstanceSetPositionDouble(
						 XPLMInstanceRef      instance,
						 const XPLMDrawInfoDouble_t * new_position,
						 const float *        data);





#endif //XPLMINSTANCE_H
