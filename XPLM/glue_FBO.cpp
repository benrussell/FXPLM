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
// Created by Ben on 11/2/2026.
//


#include "glue_FBO.hpp"

#include <iostream>

#include "XPLMDisplay.h"

#include "../third_party/timer/src/Timer.h"






gz_fbo::gz_fbo(const int width, const int height, float fAlpha ){
//		std::cout<<"gz_fbo constructor()\n";

	m_rbo = 0;
	m_fbo = 0;

	m_width = width;
	m_height = height;




#define GZ_RESET_GL_STATE 1
#if GZ_RESET_GL_STATE

	std::cout << "FXPLM/ glue_FBO: *** RESET GL STATE BEFORE FBO CREATE ***\n";
	// 1. Reset Texture State
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, 0);

// 2. Disable Client Side Capabilities
// NanoVG GL2 often leaves these toggled on
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

// 3. Reset Pixel Store (Commonly changed for font atlases)
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

// 4. Reset FBO Bindings to default
	//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	//glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

// 5. Clear the error flag leaked by any of the above or nvg
	//while (glGetError() != GL_NO_ERROR);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << " OpenGL Error: 0x" << std::hex << err << std::dec << std::endl;
	}


#endif
#undef GZ_RESET_GL_STATE





	m_FboClearColorRGBA[0] = static_cast<float>(rand()) / (float)RAND_MAX;
	m_FboClearColorRGBA[1] = static_cast<float>(rand()) / (float)RAND_MAX;
	m_FboClearColorRGBA[2] = static_cast<float>(rand()) / (float)RAND_MAX;
	m_FboClearColorRGBA[3] = fAlpha;


	m_fbo = createFBO();
	m_tex = createTextureAttachment(width, height);
	m_rbo = createRenderbufferAttachment(width, height);
	checkFBOCompleteness();

//		std::cerr<<"gz_fbo constructor WTAF()\n";

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo); // Bind the FBO
//		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);  // Set clear color to red
	glClearColor(
			m_FboClearColorRGBA[0],
			m_FboClearColorRGBA[1],
			m_FboClearColorRGBA[2],
			m_FboClearColorRGBA[3]
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the FBO

};


gz_fbo::~gz_fbo(){
	std::cout << "~gz_FBO()\n";

	//release depth buffer resources.
	glDeleteRenderbuffersEXT( 1, &m_rbo );

	//release texture buffer resources.
	glDeleteFramebuffersEXT( 1, &m_fbo );

};



void gz_fbo::push_fbo( bool clear_content ) const{
//		std::cout<<"push fbo\n";

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo); // Bind the FBO

	if( clear_content ) {
		glClearColor(
				m_FboClearColorRGBA[0],
				m_FboClearColorRGBA[1],
				m_FboClearColorRGBA[2],
				m_FboClearColorRGBA[3]
		);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Clear the color and depth buffer
	}


#if 1 //FBO::push_fbo()
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,m_width, m_height);
	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,m_width, 0, m_height, 0, 1);
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
#endif

};

//dont make this static.
void gz_fbo::pop_fbo() const{

#if 1 //FBO::pop_fbo()
	glPopMatrix();
	glMatrixMode (GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
#endif
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
//		gz::gfx::xp::load_fbo_h();

//		std::cout<<"pop fbo\n";
};




const char* gz_fbo::GetGLErrorText(GLenum error) {
	switch (error) {
		case GL_NO_ERROR:
			return "No error";
		case GL_INVALID_ENUM:
			return "Invalid enum";
		case GL_INVALID_VALUE:
			return "Invalid value";
		case GL_INVALID_OPERATION:
			return "Invalid operation";
		case GL_STACK_OVERFLOW:
			return "Stack overflow";
		case GL_STACK_UNDERFLOW:
			return "Stack underflow";
		case GL_OUT_OF_MEMORY:
			return "Out of memory";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "Invalid framebuffer operation";
		default:
			return "Unknown error";
	}
}


void gz_fbo::CheckGLError() {
	GLenum error = glGetError();
	while (error != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << GetGLErrorText(error) << std::endl;
		error = glGetError();
	}
}





GLuint gz_fbo::createFBO() {
//		std::cout<<"createFBO()..\n";

	if( ! glGenFramebuffers ){
		throw std::runtime_error("GL is not init.");
	}

	GLuint fbo;
	glGenFramebuffers(1, &fbo);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		fprintf(stderr, "glGenFramebuffers failed: 0x%04X\n", err);
		std::__throw_runtime_error("gl error creating fbo");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

//		std::cout<<"createFBO(): ret: " << fbo << "\n";
	return fbo;
}

GLuint gz_fbo::createTextureAttachment(int width, int height) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	return texture;
}

GLuint gz_fbo::createRenderbufferAttachment(int width, int height) {
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	return rbo;
}

void gz_fbo::checkFBOCompleteness() {
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Framebuffer is not complete!" << std::endl;
		exit(EXIT_FAILURE);
	}
}
