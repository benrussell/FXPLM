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

