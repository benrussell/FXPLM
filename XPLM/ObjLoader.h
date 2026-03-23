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
// ObjLoader.h
// FXPLM
//

#ifndef FXPLM_OBJLOADER_H
#define FXPLM_OBJLOADER_H

#include <vector>
#include <string>

#include "XPLMScenery.h"

struct FXPLM_Vertex_t {
    float x, y, z;
    float nx, ny, nz;
    float u, v;
};

struct FXPLM_Object_t {
    std::string path;
    std::vector<FXPLM_Vertex_t> vertices;
};

// Parses a wavefront .obj file, extracting triangulated faces into a flat vertex array.
[[maybe_unused]] FXPLM_Object_t* FXPLM_LoadWavefrontObj(const char* filepath);

// Draws the object using immediate mode OpenGL (glBegin/glEnd).
[[maybe_unused]] void FXPLM_DrawWavefrontObj(FXPLM_Object_t* obj, const XPLMDrawInfo_t* location);

#endif // FXPLM_OBJLOADER_H
