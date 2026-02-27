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
//  XPLMGraphics.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "XPLMGraphics.h"
#include "XPLM.h"

#include <iostream>

#include <GL/glew.h>



#include "glue_Plugin.hpp"
extern Plugin* global_target_plugin;

#define FXPLM_GFX_DEBUG_ENABLE 0 //FIXME: log muted

void XPLMBindTexture2d( int textureNum, int textureUnit ){

#if 0 //FXPLM_GFX_DEBUG_ENABLE //FIXME: log muted
    FXPLM_DebugLogHeader("XPLMBindTeture2d");
    std::cout << " tex_num:" << textureNum;
    std::cout << " tex_unit:" << textureUnit;
    std::cout << "\n";
#endif

	// Step 1: Select the active texture unit (where the binding will occur)
	// The textureUnit parameter should be something like GL_TEXTURE0 + N
	//glActiveTexture( GL_TEXTURE0 + textureUnit );
	glActiveTexture( GL_TEXTURE0 );

	// Step 2: Bind the texture ID to the 2D texture target on that unit
	// GL_TEXTURE_2D is the constant for the texture *type* (target)
	glBindTexture( GL_TEXTURE_2D, textureNum );

	glEnable(GL_TEXTURE_2D);
}



void XPLMGenerateTextureNumbers(GLuint *textures, int count ){
	if( textures == nullptr ){
		throw std::runtime_error("XPLMGenerateTextureNumbers: textures target is nullptr");
	}

	FXPLM_DebugLogHeader("XPLMGenerateTextureNumbers");
	std::cout << " count:" << count;
	std::cout << "\n";

    glGenTextures( count, textures ); //FIXME: some kind of tracking and reset for this? pool mgr?

    for( auto x=0; x<count; ++x ){
        global_target_plugin->m_vecTextures.push_back( textures[x] );
    }

}





void XPLMSetGraphicsState(
        int                  inEnableFog,
        int                  inNumberTexUnits,
        int                  inEnableLighting,
        int                  inEnableAlphaTesting,
        int                  inEnableAlphaBlending,
        int                  inEnableDepthTesting,
        int                  inEnableDepthWriting
){
#if 0 //FXPLM_GFX_DEBUG_ENABLE //FIXME: muted log
    FXPLM_DebugLogHeader("DEV/ XPLMSetGraphicsState");
    std::cout << " fog:" << inEnableFog;
	std::cout << " tu:" << inNumberTexUnits;
	std::cout << " light:" << inEnableLighting;
	std::cout << " atest:" << inEnableAlphaTesting;
	std::cout << " ablend:" << inEnableAlphaBlending;
	std::cout << " dtest:" << inEnableDepthTesting;
	std::cout << " dwrite:" << inEnableDepthWriting;
	std::cout << "\n";
#endif

#if 1 //FIXME XPLMSetGraphicsState GL state manip
    if( inEnableFog ){
        glEnable( GL_FOG );
    }else{
        glDisable( GL_FOG );
    }

    if( inNumberTexUnits ){ //FIXME: loop and call n times..
        glEnable( GL_TEXTURE );
        glEnable( GL_TEXTURE0 );
        glEnable( GL_TEXTURE1 );
    }else{
        glDisable( GL_TEXTURE );
        glDisable( GL_TEXTURE0 );
        glDisable( GL_TEXTURE1 );
    }

    if( inEnableLighting ){
        glEnable( GL_LIGHTING );
    }else{
        glDisable( GL_LIGHTING );
    }

    if( inEnableAlphaTesting ){
        glEnable( GL_ALPHA_TEST );
    }else{
        glDisable( GL_ALPHA_TEST );
    }

    if( inEnableAlphaBlending ){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}else{
		glDisable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

    if( inEnableDepthTesting ){
        glEnable( GL_DEPTH_TEST );
    }else{
        glDisable( GL_DEPTH_TEST );
    }

    if( inEnableDepthWriting ){
        glEnable( GL_DEPTH_WRITEMASK ); //FIXME: verify
    }else{
        glDisable( GL_DEPTH_WRITEMASK );
    }
#endif
    
}


// Assume ATLAS_SIZE is available in this scope
// #define ATLAS_SIZE 512

XPLM_API void       XPLMDrawString(
		float * inColorRGB,
		int                  inXOffset,
		int                  inYOffset,
		const char * inChar,
		int * inWordWrapWidth,    /* Can be NULL */
		XPLMFontID           inFontID) {

	/* //debug log
	FXPLM_DebugLogHeader("XPLMDrawString");
	std::cout << " x:" << inXOffset;
	std::cout << " y:" << inYOffset;
	std::cout << " inChar:[" << inChar << "]";
	if ( inWordWrapWidth ) {
		std::cout << " wrap_width:" << *inWordWrapWidth;
	}
	std::cout << " font_id:" << inFontID;
	std::cout << "\n";
	// */


	// FIX 1: lam_drawBox needs pixel dimensions, and UVs must be normalized here
	auto lam_drawBox = []( float* inColorRGB,
						   float px0, float py0, float px1, float py1, // Pixel Coords from cdata
						   float xoff, float yoff,               // Pixel Offsets
						   float width, float height ) {         // Pixel Size (px1-px0, py1-py0)

		glColor4f( inColorRGB[0],inColorRGB[1],inColorRGB[2],1.0f );

		// Normalize pixel coordinates to get true UVs (0.0 to 1.0)
		float u0 = px0 / ATLAS_SIZE;
		float v0 = py0 / ATLAS_SIZE; // TOP UV coordinate
		float u1 = px1 / ATLAS_SIZE;
		float v1 = py1 / ATLAS_SIZE; // BOTTOM UV coordinate

		glBegin(GL_QUADS);
		// Texture flip achieved by swapping v0 and v1 in glTexCoord2f calls

		// Top-Left Vertex (Y=yoff) -> Should map to BOTTOM UV (v1)
		glTexCoord2f(u0, v1);
		glVertex3f(xoff, -yoff, 0.f);

		// Top-Right Vertex (Y=yoff) -> Should map to BOTTOM UV (v1)
		glTexCoord2f(u1, v1);
		glVertex3f(xoff + width, -yoff, 0.f);

		// Bottom-Right Vertex (Y=yoff + height) -> Should map to TOP UV (v0)
		glTexCoord2f(u1, v0);
		glVertex3f(xoff + width, -yoff + height, 0.f);

		// Bottom-Left Vertex (Y=yoff + height) -> Should map to TOP UV (v0)
		glTexCoord2f(u0, v0);
		glVertex3f(xoff, -yoff + height, 0.f);
		glEnd();
	};

	// FIX 2: Enable Blending (was commented out)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, g_font_atlas_texture );

	glPushMatrix();
	glTranslatef(inXOffset,
			  	inYOffset - 10,
			  	0.f);

	float pen_x=0.f;

	const size_t sLen = strlen(inChar);
	for( size_t cx=0; cx<sLen; ++cx ) {
		char char_target = inChar[cx];
		int glyph_index = char_target - 32;

		// Ensure index is valid for g_cdata array
		if (glyph_index < 0) continue; // Skip non-printable or unsupported chars

		auto cdata = g_cdata[glyph_index];

		// FIX 3: Calculate actual pixel width and height (difference in pixel coordinates)
		float pixel_width = cdata.x1 - cdata.x0;
		float pixel_height = cdata.y1 - cdata.y0;

		// FIX 4: Skip characters with zero size (like space, which should only advance pen_x)
		if (pixel_width <= 0 || pixel_height <= 0) {
			pen_x += cdata.xadvance;
			continue;
		}

		glPushMatrix();
		// Apply per-character horizontal translation (pen_x)
		glTranslatef( pen_x, 0.f, 0.f );

		lam_drawBox( inColorRGB,
					 cdata.x0, cdata.y0, // Pixel UV start/end
					 cdata.x1, cdata.y1,
					 cdata.xoff, cdata.yoff, // Pixel Offsets
					 pixel_width, pixel_height // Pixel Dimensions
		);

		pen_x += cdata.xadvance;

		glPopMatrix();

	}

	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}



XPLM_API void       XPLMDrawTranslucentDarkBox(
                         int                  inLeft,
                         int                  inTop,
                         int                  inRight,
                         int                  inBottom) {

	FXPLM_DebugLogHeader("XPLMDrawTranslucentDarkBox");
	std::cout << " l:" << inLeft;
	std::cout << " t:" << inTop;
	std::cout << " r:" << inRight;
	std::cout << " b:" << inBottom;
	std::cout << "\n";

	//FIXME: draw a fuckin box eh.

	auto lam_drawTranslucentBox = [](float left, float top, float right, float bottom) {
		// 1. Enable Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// 2. Set Color: Dark Grey (0.2) at 50% Alpha (0.5)
		glColor4f(0.2f, 0.2f, 0.2f, 0.5f);

		// 3. Draw Geometry
		glBegin(GL_QUADS);
		glVertex2f(left,  top);    // Top Left
		glVertex2f(right, top);    // Top Right
		glVertex2f(right, bottom); // Bottom Right
		glVertex2f(left,  bottom); // Bottom Left
		glEnd();

		// 4. Cleanup state
		glDisable(GL_BLEND);
	};

	lam_drawTranslucentBox( inLeft,inTop,inRight,inBottom );

}



XPLM_API void       XPLMGetFontDimensions(
                         XPLMFontID           inFontID,
                         int *                outCharWidth,    /* Can be NULL */
                         int *                outCharHeight,    /* Can be NULL */
                         int *                outDigitsOnly /* Can be NULL */
                         ){

	// font 0 is mono spaced
	// font 18 is proportional

	FXPLM_DebugLogHeader("HC/ XPLMGetFontDimensions");
	std::cout << " id:" << inFontID;

	if( outCharWidth ){
	//	std::cout << " char_w:" << *outCharWidth;
		*outCharWidth = 7;
	}
	if( outCharHeight ){
	//	std::cout << " char_h:" << *outCharHeight;
		*outCharHeight = 12;

	}
	if( outDigitsOnly ){
		*outDigitsOnly = 0;
		std::cout << " digits_only:" << *outDigitsOnly;
	}

	std::cout << " / ret: w:7 h:10 digits:0\n";

}



XPLM_API int        XPLMGetTexture(
                         XPLMTextureID        inTexture) {

	FXPLM_DebugLogHeader("HC/ XPLMGetTexture");
	std::cout << " inTexture:" << inTexture;

    //FIXME: return a GL texture number that points to something useful
    switch( inTexture ){
    	case xplm_Tex_GeneralInterface:
    		std::cout << " general_interface";
    		//return 1;
    		break;
    	case xplm_Tex_AircraftPaint:
    		std::cout << " acf_paint";
    		//return 2;
    		break;
    	case xplm_Tex_AircraftLiteMap:
    		std::cout << " acf_lite_map";
    		//return 3;
    		break;
    	case xplm_Tex_Radar_Pilot:
    		std::cout << " radar_pilot";
    		//return 4;
    		break;
    	case xplm_Tex_Radar_Copilot:
    		std::cout << " radar_copilot";
    		//return 5;
    		break;

    	default:
			std::cout<<"unknown tex query id\n";
			break;
    }

	std::cout << "\n";

	return 0;

}



XPLM_API float      XPLMMeasureString(
                         XPLMFontID           inFontID,
                         const char *         inChar,
                         int                  inNumChars) {
#if FXPLM_GFX_DEBUG_ENABLE
	FXPLM_DebugLogHeader("HC/ XPLMMeasureString");
    std::cout<<"  inChar:["<< inChar <<"]  inNumChars:" << inNumChars << "";
#endif
    // inFontID is ignored because only the mono space font was ever widely used.

    float ret = 0.f;

    const float avg_width = 5.f;
    for( int x=0; x<inNumChars; ++x ){
    	ret += avg_width;
    	if( inChar[x] == 0 ){
    		break;
    	}
    }

#if FXPLM_GFX_DEBUG_ENABLE
    std::cout << " / ret:" << ret << "\n";
#endif
    return ret;
}



XPLM_API void       XPLMLocalToWorld(
                         double               inX,
                         double               inY,
                         double               inZ,
                         double *             outLatitude,
                         double *             outLongitude,
                         double *             outAltitude) {
    std::cerr<<"FXPLM/ NOP/ XPLMLocalToWorld\n";
    throw std::runtime_error("FXPLM/ NOP/ XPLMLocalToWorld");
}



XPLM_API void       XPLMWorldToLocal(
                         double               inLatitude,
                         double               inLongitude,
                         double               inAltitude,
                         double *             outX,
                         double *             outY,
                         double *             outZ) {
    std::cerr<<"FXPLM/ NOP/ XPLMWorldToLocal\n";
    throw std::runtime_error("FXPLM/ NOP/ XPLMWorldToLocal");
}


