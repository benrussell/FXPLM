//
// Created by Ben on 20/11/2025.
//

#ifndef XPLMMAP_H
#define XPLMMAP_H

#include "defs.h"

typedef void * XPLMMapLayerID;

typedef void * XPLMMapProjectionID;


enum XPLMMapStyle {
	xplm_MapStyle_VFR_Sectional,
	xplm_MapStyle_IFR_LowEnroute,
	xplm_MapStyle_IFR_HighEnroute
};


typedef void (* XPLMMapDrawingCallback_f)(
						 XPLMMapLayerID       inLayer,
						 const float *        inMapBoundsLeftTopRightBottom,
						 float                zoomRatio,
						 float                mapUnitsPerUserInterfaceUnit,
						 XPLMMapStyle         mapStyle,
						 XPLMMapProjectionID  projection,
						 void *               inRefcon);


typedef void (* XPLMMapIconDrawingCallback_f)(
						 XPLMMapLayerID       inLayer,
						 const float *        inMapBoundsLeftTopRightBottom,
						 float                zoomRatio,
						 float                mapUnitsPerUserInterfaceUnit,
						 XPLMMapStyle         mapStyle,
						 XPLMMapProjectionID  projection,
						 void *               inRefcon);

typedef void (* XPLMMapLabelDrawingCallback_f)(
						 XPLMMapLayerID       inLayer,
						 const float *        inMapBoundsLeftTopRightBottom,
						 float                zoomRatio,
						 float                mapUnitsPerUserInterfaceUnit,
						 XPLMMapStyle         mapStyle,
						 XPLMMapProjectionID  projection,
						 void *               inRefcon);



typedef void (* XPLMMapPrepareCacheCallback_f)(
						 XPLMMapLayerID       inLayer,
						 const float *        inTotalMapBoundsLeftTopRightBottom,
						 XPLMMapProjectionID  projection,
						 void *               inRefcon);



typedef void (* XPLMMapWillBeDeletedCallback_f)(
						 XPLMMapLayerID       inLayer,
						 void *               inRefcon);



enum XPLMMapLayerType {
	xplm_MapLayer_Fill,
	xplm_MapLayer_Markings
};


#define XPLM_MAP_USER_INTERFACE "XPLM_MAP_USER_INTERFACE"

#define XPLM_MAP_IOS         "XPLM_MAP_IOS"

typedef struct {
     // Used to inform XPLMCreateMapLayer() of the SDK version you compiled against; should always be set to sizeof(XPLMCreateMapLayer_t)
     int                       structSize;
     // Globally unique string identifying the map you want this layer to appear in. As of XPLM300, this is limited to one of XPLM_MAP_USER_INTERFACE or XPLM_MAP_IOS
     const char *              mapToCreateLayerIn;
     // The type of layer you are creating, used to determine draw order (all plugin-created markings layers are drawn above all plugin-created fill layers)
     XPLMMapLayerType          layerType;
     // Optional callback to inform you this layer is being deleted (due to its owning map being destroyed)
     XPLMMapWillBeDeletedCallback_f willBeDeletedCallback;
     // Optional callback you want to use to prepare your draw cache when the map bounds change (set to NULL if you don't want this callback)
     XPLMMapPrepareCacheCallback_f prepCacheCallback;
     // Optional callback you want to use for arbitrary OpenGL drawing, which goes beneath all icons in the map's layering system (set to NULL if you don't want this callback)
     XPLMMapDrawingCallback_f  drawCallback;
     // Optional callback you want to use for drawing icons, which go above all built-in X-Plane icons (except the aircraft) in the map's layering system (set to NULL if you don't want this callback)
     XPLMMapIconDrawingCallback_f iconCallback;
     // Optional callback you want to use for drawing map labels, which go above all built-in X-Plane icons and labels (except those of aircraft) in the map's layering system (set to NULL if you don't want this callback)
     XPLMMapLabelDrawingCallback_f labelCallback;
     // True if you want a checkbox to be created in the map UI to toggle this layer on and off; false if the layer should simply always be enabled
     int                       showUiToggle;
     // Short label to use for this layer in the user interface
     const char *              layerName;
     // A reference to arbitrary data that will be passed to your callbacks
     void *                    refcon;
} XPLMCreateMapLayer_t;


XPLM_API XPLMMapLayerID XPLMCreateMapLayer(
						 XPLMCreateMapLayer_t * inParams);


XPLM_API int        XPLMDestroyMapLayer(
						 XPLMMapLayerID       inLayer);


typedef void (* XPLMMapCreatedCallback_f)(
						 const char *         mapIdentifier,
						 void *               refcon);


XPLM_API void       XPLMRegisterMapCreationHook(
						 XPLMMapCreatedCallback_f callback,
						 void *               refcon);


XPLM_API int        XPLMMapExists(
						 const char *         mapIdentifier);



enum XPLMMapOrientation {
	xplm_MapOrientation_Map,
	xplm_MapOrientation_UI
};


XPLM_API void       XPLMDrawMapIconFromSheet(
						 XPLMMapLayerID       layer,
						 const char *         inPngPath,
						 int                  s,
						 int                  t,
						 int                  ds,
						 int                  dt,
						 float                mapX,
						 float                mapY,
						 XPLMMapOrientation   orientation,
						 float                rotationDegrees,
						 float                mapWidth);


XPLM_API void       XPLMDrawMapLabel(
						 XPLMMapLayerID       layer,
						 const char *         inText,
						 float                mapX,
						 float                mapY,
						 XPLMMapOrientation   orientation,
						 float                rotationDegrees);


XPLM_API void       XPLMMapProject(
						 XPLMMapProjectionID  projection,
						 double               latitude,
						 double               longitude,
						 float *              outX,
						 float *              outY);



XPLM_API void       XPLMMapUnproject(
						 XPLMMapProjectionID  projection,
						 float                mapX,
						 float                mapY,
						 double *             outLatitude,
						 double *             outLongitude);


XPLM_API float      XPLMMapScaleMeter(
						 XPLMMapProjectionID  projection,
						 float                mapX,
						 float                mapY);


XPLM_API float      XPLMMapGetNorthHeading(
						 XPLMMapProjectionID  projection,
						 float                mapX,
						 float                mapY);





#endif //XPLMMAP_H
