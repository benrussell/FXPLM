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

#ifndef GLUE_DRAWCALLBACKHOST_HPP
#define GLUE_DRAWCALLBACKHOST_HPP



#include <iostream>

#include <GL/glew.h>





#include "XPLMDisplay.h"

#include "../third_party/timer/src/Timer.h"


#include "glue_FBO.hpp"

//#include <gz_shader.h>


class DrawCallbackHost {
public:

//	// fbo handle
//	GLuint m_fbo=0;
//	GLuint m_rbo=0;
//
//	int m_width=64;
//	int m_height=64;
//
//	GLuint m_tex=0;

	std::string m_deviceName;

//	float m_FboClearColorRGBA[4]={0.5, 0.0, 0.5, 1.0};

	//gz_fbo* m_screen_fbo;

	//gz::shader m_shader;

    XPLMDrawCallback_f m_draw_cb_f;
    XPLMDrawingPhase m_phase;
    int m_before;
    void* m_refcon;

	bool m_dcb_enabled;

	explicit DrawCallbackHost(
        XPLMDrawCallback_f   inCallback,
		XPLMDrawingPhase     inPhase,
		int                  inWantsBefore,
		void *               inRefcon
    ){

		m_dcb_enabled = true;

        m_draw_cb_f = inCallback;
        m_phase = inPhase;
        m_before = inWantsBefore;
        m_refcon = inRefcon;

		m_timer.start();


		//const int screenWidth=1024;
		//const int screenHeight=1024;

		//m_screen_fbo = new gz_fbo(screenWidth, screenHeight );
        //std::cout << "  glue_DrawCallBackHost: fbo tex_id: " << m_screen_fbo->m_tex << "\n";

	}



	~DrawCallbackHost(){
		std::cout<<"~DrawCallbackHost()\n";
		//std::cout <<" destruct:" << m_deviceId << "\n";

		//delete m_screen_fbo;

	}


	//this is called by bake but can also be called directly.
	void draw_screen(){
        if( m_draw_cb_f ){
            m_draw_cb_f(
                m_phase,
                m_before,
                m_refcon
            );
        }
	}



	double cost(){
		return m_bakeStop_Screen - m_bakeStart_Screen;
	}


	void bake(){
        //std::cout << "DrawCallbackHost->bake()\n";

		if( ! m_dcb_enabled ){
			return;
		}

		//bake the screen.
		m_bakeStart_Screen = m_timer.getElapsedTimeInMilliSec();
			//m_screen_fbo->push_fbo();
				draw_screen();
				//draw_triangle_dcb_host();
			//m_screen_fbo->pop_fbo();
		m_bakeStop_Screen = m_timer.getElapsedTimeInMilliSec();

	}



private:

	//profiling timer.
	double m_bakeStart_Screen=0;
	double m_bakeStop_Screen=0;

	Timer m_timer;



};



#endif //GLUE_DRAWCALLBACKHOST_HPP
