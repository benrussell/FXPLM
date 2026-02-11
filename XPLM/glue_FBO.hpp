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
// Created by Ben on 31/10/2025.
//

#ifndef GLUE_FBO_HPP
#define GLUE_FBO_HPP


//#include <iostream>
//
#include <GL/glew.h>
//
//#include "XPLMDisplay.h"
//
//#include "../third_party/timer/src/Timer.h"


class gz_fbo{
public:

	// fbo handle
	GLuint m_fbo=0;
	GLuint m_rbo=0;

	int m_width=64;
	int m_height=64;

	GLuint m_tex=0;

	float m_FboClearColorRGBA[4]; //={0.5, 0.0, 0.5, 1.0}; // Randomized in constructor

	gz_fbo(int width, int height, float fAlpha=1.0f );
	~gz_fbo();

	void push_fbo() const;
	//dont make this static.
	void pop_fbo() const;


private:

	const char* GetGLErrorText(GLenum error);

	void CheckGLError();


	GLuint createFBO();

	GLuint createTextureAttachment(int width, int height);

	GLuint createRenderbufferAttachment(int width, int height);

	void checkFBOCompleteness();

};


#endif //GLUE_FBO_HPP
