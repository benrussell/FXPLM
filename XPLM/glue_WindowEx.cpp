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

#if 0
	const size_t need_size = sizeof(XPLMCreateWindow_t);
	const size_t legacy_size = sizeof(XPLMCreateWindow_t_legacy);

	if( need_size != params->structSize ){
		std::cout << "  params struct size mismatch/unknown\t";
		std::cout << "  sizeof():" << need_size << " / p->size:" << params->structSize << "\n";
		std::cout << "  legacy size:" << legacy_size << "\n";
		//return nullptr;
		throw std::runtime_error("cannot create window.");
	}
#endif


//	std::cout << "  memcpy params\n";
	m_params = new XPLMCreateWindow_t();
	memset( m_params, 0, sizeof(XPLMCreateWindow_t)); //init to 0's

	const size_t cp_size = std::min(params->structSize, (int)sizeof(XPLMCreateWindow_t));
	memcpy( m_params, params, cp_size );

	//FIXME: m_params->structSize probably needs to be updated

//	std::cout << "finished: glue_WindowEx ctor\n";
}


glue_WindowEx::~glue_WindowEx() {
	delete m_params;
}
