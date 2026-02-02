//
// Created by Ben on 20/11/2025.
//

#ifndef XPLMCAMERA_H
#define XPLMCAMERA_H


#include "defs.h"


enum XPLMCameraControlDuration {
	xplm_ControlCameraUntilViewChanges=1,
	xplm_ControlCameraForever=2,
};



typedef struct {
	float                     x;
	float                     y;
	float                     z;
	float                     pitch;
	float                     heading;
	float                     roll;
	float                     zoom;
} XPLMCameraPosition_t;



typedef int (* XPLMCameraControl_f)(
						 XPLMCameraPosition_t * outCameraPosition,    /* Can be NULL */
						 int                  inIsLosingControl,
						 void *               inRefcon);



XPLM_API void       XPLMControlCamera(
						 XPLMCameraControlDuration inHowLong,
						 XPLMCameraControl_f  inControlFunc,
						 void *               inRefcon);


XPLM_API void       XPLMDontControlCamera(void);


XPLM_API int        XPLMIsCameraBeingControlled(
						 XPLMCameraControlDuration * outCameraControlDuration);    /* Can be NULL */


XPLM_API void       XPLMReadCameraPosition(
						 XPLMCameraPosition_t * outCameraPosition);



#endif //XPLMCAMERA_H
