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
// ObjLoader.cpp
// FXPLM
//

#include "ObjLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

[[maybe_unused]] FXPLM_Object_t* FXPLM_LoadWavefrontObj(const char* filepath) {
    if (!filepath) return nullptr;

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "FXPLM/ ObjLoader: Could not open file " << filepath << std::endl;
        return nullptr;
    }

    auto obj = new FXPLM_Object_t();
    obj->path = filepath;

    std::vector<float> v, vn, vt;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            v.push_back(x); v.push_back(y); v.push_back(z);
        } else if (type == "vn") {
            float x, y, z;
            iss >> x >> y >> z;
            vn.push_back(x); vn.push_back(y); vn.push_back(z);
        } else if (type == "vt") {
            float u, v_coord;
            iss >> u >> v_coord;
            vt.push_back(u); vt.push_back(v_coord);
        } else if (type == "f") {
            std::string vertexStr;
            std::vector<FXPLM_Vertex_t> faceVertices;

            while (iss >> vertexStr) {
                std::istringstream viss(vertexStr);
                std::string vIdxStr, vtIdxStr, vnIdxStr;
                std::getline(viss, vIdxStr, '/');
                std::getline(viss, vtIdxStr, '/');
                std::getline(viss, vnIdxStr, '/');

                FXPLM_Vertex_t vertex = {0,0,0, 0,0,0, 0,0};

                if (!vIdxStr.empty()) {
                    int vIdx = std::stoi(vIdxStr) - 1;
                    if (vIdx >= 0 && vIdx * 3 + 2 < v.size()) {
                        vertex.x = v[vIdx * 3];
                        vertex.y = v[vIdx * 3 + 1];
                        vertex.z = v[vIdx * 3 + 2];
                    }
                }
                if (!vtIdxStr.empty()) {
                    int vtIdx = std::stoi(vtIdxStr) - 1;
                    if (vtIdx >= 0 && vtIdx * 2 + 1 < vt.size()) {
                        vertex.u = vt[vtIdx * 2];
                        vertex.v = vt[vtIdx * 2 + 1];
                    }
                }
                if (!vnIdxStr.empty()) {
                    int vnIdx = std::stoi(vnIdxStr) - 1;
                    if (vnIdx >= 0 && vnIdx * 3 + 2 < vn.size()) {
                        vertex.nx = vn[vnIdx * 3];
                        vertex.ny = vn[vnIdx * 3 + 1];
                        vertex.nz = vn[vnIdx * 3 + 2];
                    }
                }

                faceVertices.push_back(vertex);
            }

            // Triangulate face (assuming simple convex polygons)
            for (size_t i = 1; i + 1 < faceVertices.size(); ++i) {
                obj->vertices.push_back(faceVertices[0]);
                obj->vertices.push_back(faceVertices[i]);
                obj->vertices.push_back(faceVertices[i + 1]);
            }
        }
    }

    std::cout << "FXPLM/ ObjLoader: Loaded " << obj->vertices.size() / 3 << " triangles from " << filepath << std::endl;
    return obj;
}


[[maybe_unused]] void FXPLM_DrawWavefrontObj(FXPLM_Object_t* obj, const XPLMDrawInfo_t* location) {
    if (!obj || obj->vertices.empty() || !location) return;

    glPushMatrix();
    
    // Apply local transformations
    glTranslatef(location->x, location->y, location->z);
    
    // X-Plane convention usually applies rotations: Heading (Y-axis), Pitch (X-axis), Roll (Z-axis)
    // The exact order might vary, but typical is:
    glRotatef(location->heading, 0.0f, -1.0f, 0.0f); // clockwise around Y?
    glRotatef(location->pitch, 1.0f, 0.0f, 0.0f);    // positive is up
    glRotatef(location->roll, 0.0f, 0.0f, -1.0f);

		glPushMatrix();
			glBegin(GL_TRIANGLES);
			for (const auto& v : obj->vertices) {
				glNormal3f(v.nx, v.ny, v.nz);
				glTexCoord2f(v.u, v.v);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		glPopMatrix();

    glPopMatrix();
}
