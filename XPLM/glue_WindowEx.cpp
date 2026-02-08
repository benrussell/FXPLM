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
