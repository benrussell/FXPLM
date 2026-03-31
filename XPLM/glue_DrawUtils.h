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
// Created by Ben on 24/3/2026.
//

#ifndef XPLM_GLUE_DRAWUTILS_H
#define XPLM_GLUE_DRAWUTILS_H

#include <GL/glew.h>





auto lam_drawTexturedQuad = [](float w, float h, GLuint tex_id) {

	glEnable(GL_TEXTURE_2D);

	//glDisable(GL_COLOR_MATERIAL);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_FRAMEBUFFER_SRGB);
	//glDisableClientState(GL_COLOR_ARRAY);
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

//	glColor4f(0.5, 0.5, 0.0, 1.0);

//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, tex_id);

	// Draw the quad
	glBegin(GL_QUADS);

	// Bottom-left corner
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);

	// Bottom-right corner
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(w, 0.0f);

	// Top-right corner
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(w, h);

	// Top-left corner
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(0.0f, h);

	glEnd();
#if 0
	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_BLEND);

	// Disable 2D texture
	glDisable(GL_TEXTURE_2D);
#endif
};





class glue_DrawUtils {

};


#endif //XPLM_GLUE_DRAWUTILS_H
