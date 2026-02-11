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

#include "glue_WindowEx.h"

#include <cstring>

//#include <iostream>

glue_WindowEx::glue_WindowEx(XPLMCreateWindow_t *params) {
//	std::cout << "glue_WindowEx ctor:\n";

//	std::cout << "  memcpy params\n";
	m_params = new XPLMCreateWindow_t();
	memcpy( m_params, params, sizeof(XPLMCreateWindow_t) );

//	std::cout << "finished: glue_WindowEx ctor\n";
}


glue_WindowEx::~glue_WindowEx() {
	delete m_params;
}
