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
//  XPLM.h
//  XPLM
//
//  Created by Ben on 18/10/2025.
//

#ifndef XPLM_hpp
#define XPLM_hpp

#include "defs.h"


#include "glue_Plugin.hpp"


#include "../third_party/timer/src/Timer.h"






#define FONT_HEIGHT_PX 12.0f
#define ATLAS_SIZE 512
#define FIRST_CHAR 32 // Space
#define CHAR_COUNT 96 // ASCII 32 to 127
#define FONT_FILE "/Users/br/XP12_Libs/Resources/fonts/GoogleSansCode-Bold.ttf"

#include <stb_truetype.h>

// Data needed by the drawing function
inline GLuint g_font_atlas_texture;
inline stbtt_bakedchar g_cdata[CHAR_COUNT];
inline unsigned char* g_font_data = nullptr;






inline std::string fxplm_global_sys_folder;


namespace XPHost {
	inline std::vector<Plugin*> m_vecPlugins;
	inline std::vector<std::string> m_vecLog;

//	inline float fps;

	inline std::string m_load_plugin_error_msg;

	inline Timer* m_ptrTimer;
}

// globals we need to access in the host app

//read vars, call fns
extern Plugin* global_target_plugin;



void FXPLM_DebugLogHeader( const char* msg );


XPLM_API void FXPLM_TestGL();


XPLM_API void FXPLM_Init( char*, char*, char* );

XPLM_API void FXPLM_SetContext( void* );


XPLM_API int FXPLM_LoadPlugin( const char* );
XPLM_API const char* FXPLM_LoadPlugin_GetErr();

XPLM_API void FXPLM_UnloadPlugins();


XPLM_API int FXPLM_RunFLCBS();


XPLM_API int FXPLM_DrawCBS();

XPLM_API int FXPLM_DrawWindows();

XPLM_API int FXPLM_HandleWindowClick( float x, float y );


XPLM_API void* FXPLM_PluginInstPtr( int plugin_id );


XPLM_API void* FXPLM_DrefPoolPtr();

XPLM_API xp_dref* FXPLM_DrefCreate( const char* dref_name );



// README: DO NOT ANNOTATE WITH XPLM_API or other decorators or the link will break.
void __XPLMValidateThreadSafety(const char* functionName,
								const char* fileName,
								int line);



#if 0 //del? Xcode suggestedd symbols
#import <Foundation/Foundation.h>

//! Project version number for XPLM.
FOUNDATION_EXPORT double XPLMVersionNumber;

//! Project version string for XPLM.
FOUNDATION_EXPORT const unsigned char XPLMVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <XPLM/PublicHeader.h>
#endif



#endif /* XPLM_hpp */