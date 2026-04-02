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

#ifndef GLUE_AVIONICSHOST_HPP
#define GLUE_AVIONICSHOST_HPP



#include "XPLMDisplay.h"
#include "../third_party/timer/src/Timer.h"

#include "glue_FBO.hpp"
//#include <gz_shader.h>

#include <string>


class AvionicsHost {
public:

	XPLMCreateAvionics_t* m_params;

	std::string m_deviceName;
	std::string m_deviceId;

	gz_fbo* m_screen_fbo;
	gz_fbo* m_bezel_fbo;
	gz_fbo* m_composite_fbo;

	float m_bezel_ambient_color[4] = {0.5f, 0.5f, 0.5f, 1.f};

	bool m_popup_visible=false;
	bool m_wants_keyboard=false;

	//gz::shader m_shader;

	Plugin* m_parentPlugin;




	explicit AvionicsHost( XPLMCreateAvionics_t* p, Plugin* parent );
	~AvionicsHost();

	void draw_bezel();
	//this is called by bake but can also be called directly.
	void draw_screen();
	void draw_composite();
	void bake();


	double cost();
	double cost_screen();
	double cost_bezel();
	double cost_composite();


private:

	//profiling timer.
	double m_bakeStart_Screen=0;
	double m_bakeStop_Screen=0;
	double m_bakeStart_Bezel=0;
	double m_bakeStop_Bezel=0;
	double m_bakeStart_Composite=0;
	double m_bakeStop_Composite=0;
	Timer m_timer;

};




#endif //GLUE_AVIONICSHOST_HPP
