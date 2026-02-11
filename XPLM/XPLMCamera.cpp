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