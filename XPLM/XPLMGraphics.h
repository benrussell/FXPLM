//
//  XPLMGraphics.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef XPLMGraphics_hpp
#define XPLMGraphics_hpp

#include "defs.h"

#include <stdio.h>

#include <GL/glew.h>
//#include <GLFW/glfw3.h>

#include <iostream>



XPLM_API void XPLMBindTexture2d( int textureNum, int textureUnit );


XPLM_API void XPLMGenerateTextureNumbers(GLuint *textures, int count );


XPLM_API void XPLMSetGraphicsState(
        int                  inEnableFog,
        int                  inNumberTexUnits,
        int                  inEnableLighting,
        int                  inEnableAlphaTesting,
        int                  inEnableAlphaBlending,
        int                  inEnableDepthTesting,
        int                  inEnableDepthWriting
);


enum XPLMFontID {
	xplmFont_Basic
};


XPLM_API void       XPLMDrawString(
                         float *              inColorRGB,
                         int                  inXOffset,
                         int                  inYOffset,
                         const char *         inChar,
                         int *                inWordWrapWidth,    /* Can be NULL */
                         XPLMFontID           inFontID);



XPLM_API void       XPLMDrawTranslucentDarkBox(
						 int                  inLeft,
						 int                  inTop,
						 int                  inRight,
						 int                  inBottom);


XPLM_API void       XPLMGetFontDimensions(
						 XPLMFontID           inFontID,
						 int *                outCharWidth,    /* Can be NULL */
						 int *                outCharHeight,    /* Can be NULL */
						 int *                outDigitsOnly);



enum XPLMTextureID {
	xplm_Tex_GeneralInterface,
	xplm_Tex_AircraftPaint,
	xplm_Tex_AircraftLiteMap,
	xplm_Tex_Radar_Pilot,
	xplm_Tex_Radar_Copilot,
};


XPLM_API int        XPLMGetTexture(
						 XPLMTextureID        inTexture);



XPLM_API float      XPLMMeasureString(
						 XPLMFontID           inFontID,
						 const char *         inChar,
						 int                  inNumChars);


XPLM_API void       XPLMLocalToWorld(
						 double               inX,
						 double               inY,
						 double               inZ,
						 double *             outLatitude,
						 double *             outLongitude,
						 double *             outAltitude);

XPLM_API void       XPLMWorldToLocal(
						 double               inLatitude,
						 double               inLongitude,
						 double               inAltitude,
						 double *             outX,
						 double *             outY,
						 double *             outZ);


#endif /* XPLMGraphics_hpp */
