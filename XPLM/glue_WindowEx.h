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
// Created by Ben on 28/12/2025.
//

#ifndef XPLM_GLUE_WINDOWEX_H
#define XPLM_GLUE_WINDOWEX_H


#include "XPLMDisplay.h"
#include <string>

class glue_WindowEx {
public:

	XPLMCreateWindow_t* m_params;

	//extra meta data that the SDK API needs but the params dont carry.
	std::string m_sWindowTitle;
	bool m_bPoppedOut=false;

	// performance timing data
	double m_bakeStart=0.0;
	double m_bakeStop=0.0;

	size_t z_index=0;

	explicit glue_WindowEx( XPLMCreateWindow_t* params );
	~glue_WindowEx();
};


#endif //XPLM_GLUE_WINDOWEX_H
