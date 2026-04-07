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




class glue_DrawUtils {
public:
	static void drawTexturedQuad(float w, float h, GLuint tex_id);
};


#endif //XPLM_GLUE_DRAWUTILS_H
