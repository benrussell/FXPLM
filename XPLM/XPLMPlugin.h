//
//  XPLMPlugin.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef XPLMPlugin_hpp
#define XPLMPlugin_hpp

#include "defs.h"


// https://developer.x-plane.com/sdk/XPLMPlugin/#XPLMSendMessageToPlugin

#define XPLM_MSG_PLANE_CRASHED 101
#define XPLM_MSG_PLANE_LOADED 102
#define XPLM_MSG_AIRPORT_LOADED 103
#define XPLM_MSG_SCENERY_LOADED 104
#define XPLM_MSG_AIRPLANE_COUNT_CHANGED 105
#define XPLM_MSG_PLANE_UNLOADED 106
#define XPLM_MSG_WILL_WRITE_PREFS 107
#define XPLM_MSG_LIVERY_LOADED 108
#define XPLM_MSG_ENTERED_VR  109
#define XPLM_MSG_EXITING_VR  110
#define XPLM_MSG_RELEASE_PLANES 111
#define XPLM_MSG_FMOD_BANK_LOADED 112
#define XPLM_MSG_FMOD_BANK_UNLOADING 113
#define XPLM_MSG_DATAREFS_ADDED 114




#define XPLMPluginID int


XPLM_API void XPLMEnableFeature( const char* feature_name );

XPLM_API int XPLMGetMyID( void );

XPLM_API void XPLMGetPluginInfo(
    int pluginId,
    char* outName,
    char* outFilePath,
    char* outSignature,
    char* outDescription
);

XPLM_API int        XPLMCountPlugins(void);

XPLM_API XPLMPluginID XPLMGetNthPlugin(
						 int                  inIndex);



XPLM_API int        XPLMIsPluginEnabled(
                         XPLMPluginID         inPluginID);


XPLM_API int        XPLMEnablePlugin(
						 XPLMPluginID         inPluginID);

XPLM_API void       XPLMDisablePlugin(
						 XPLMPluginID         inPluginID);

XPLM_API void       XPLMReloadPlugins(void);



XPLM_API int        XPLMIsFeatureEnabled(
						 const char *         inFeature);


XPLM_API XPLMPluginID XPLMFindPluginByPath(
						 const char *         inPath);



#endif /* XPLMPlugin_hpp */
