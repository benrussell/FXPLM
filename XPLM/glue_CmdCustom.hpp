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
// Created by Ben on 1/11/2025.
//

#ifndef GLUE_CMDCUSTOM_H
#define GLUE_CMDCUSTOM_H



#include <iostream>

#include "XPLMUtilities.h"


class xpCmdCustom {
public:
	xpCmdCustom( const std::string& name, const std::string& desc ){
		m_name = name;
		m_description = desc;

	}

	void setHandlerFn(
			XPLMCommandCallback_f fn,
			int wants_before,
			void* refcon
			){

		m_cbf = fn;
		m_wants_before = wants_before;
		m_refcon = refcon;

	}

	void callBegin(){
		std::cout<<"cmd->callBegin():" << this->m_name << "\n";
		if( m_cbf ){
			m_cbf( this, XPLMCommandPhase::xplm_CommandBegin, this->m_refcon );
		}else{
			//throw std::runtime_error("cmd cbf is nullptr");
			std::cout << "cmd cbf is nullptr\n";
		}
	}


	void callHold(){
		std::cout<<"cmd->callHold():" << this->m_name << "\n";
		if( m_cbf ){
			m_cbf( this, XPLMCommandPhase::xplm_CommandContinue, this->m_refcon );
		}else{
			//throw std::runtime_error("cmd cbf is nullptr");
			std::cout << "cmd cbf is nullptr\n";
		}
	}


	void callEnd(){
		std::cout<<"cmd->callEnd():" << this->m_name << "\n";
		if( m_cbf ){
			m_cbf( this, XPLMCommandPhase::xplm_CommandEnd, this->m_refcon );
		}else{
			//throw std::runtime_error("cmd cbf is nullptr");
			std::cout << "cmd cbf is nullptr\n";
		}
	}

	XPLMCommandCallback_f m_cbf{};
	int m_wants_before=0;
	void* m_refcon{};

	std::string m_name{};
	std::string m_description{};

};


#endif //GLUE_CMDCUSTOM_H
