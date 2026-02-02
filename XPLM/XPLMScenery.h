//
// Created by Ben on 20/11/2025.
//

#ifndef XPLMSCENERY_H
#define XPLMSCENERY_H

#include "defs.h"

enum XPLMProbeType {
	xplm_ProbeY
};


enum XPLMProbeResult {
	xplm_ProbeHitTerrain,
	xplm_ProbeError,
	xplm_ProbeMissed
};


typedef void * XPLMProbeRef;


typedef struct {
	// Size of structure in bytes - always set this before calling the XPLM.
	int                       structSize;
	// Resulting X location of the terrain point we hit, in local OpenGL coordinates.
	float                     locationX;
	// Resulting Y location of the terrain point we hit, in local OpenGL coordinates.
	float                     locationY;
	// Resulting Z location of the terrain point we hit, in local OpenGL coordinates.
	float                     locationZ;
	// X component of the normal vector to the terrain we found.
	float                     normalX;
	// Y component of the normal vector to the terrain we found.
	float                     normalY;
	// Z component of the normal vector to the terrain we found.
	float                     normalZ;
	// X component of the velocity vector of the terrain we found.
	float                     velocityX;
	// Y component of the velocity vector of the terrain we found.
	float                     velocityY;
	// Z component of the velocity vector of the terrain we found.
	float                     velocityZ;
	// Tells if the surface we hit is water (otherwise it is land).
	int                       is_wet;
} XPLMProbeInfo_t;


XPLM_API XPLMProbeRef XPLMCreateProbe(
						 XPLMProbeType        inProbeType);


XPLM_API void       XPLMDestroyProbe(
						 XPLMProbeRef         inProbe);


XPLM_API XPLMProbeResult XPLMProbeTerrainXYZ(
						 XPLMProbeRef         inProbe,
						 float                inX,
						 float                inY,
						 float                inZ,
						 XPLMProbeInfo_t *    outInfo);


XPLM_API float      XPLMGetMagneticVariation(
						 double               latitude,
						 double               longitude);


XPLM_API float      XPLMDegTrueToDegMagnetic(
						 float                headingDegreesTrue);


XPLM_API float      XPLMDegMagneticToDegTrue(
						 float                headingDegreesMagnetic);



typedef void * XPLMObjectRef;


typedef struct {
	// Set this to the size of this structure!
	int                       structSize;
	// X location of the object in local coordinates.
	float                     x;
	// Y location of the object in local coordinates.
	float                     y;
	// Z location of the object in local coordinates.
	float                     z;
	// Pitch in degres to rotate the object, positive is up.
	float                     pitch;
	// Heading in local coordinates to rotate the object, clockwise.
	float                     heading;
	// Roll to rotate the object.
	float                     roll;
} XPLMDrawInfo_t;



typedef struct {
	// Set this to the size of this structure!
	int                       structSize;
	// X location of the object in local coordinates.
	double                    x;
	// Y location of the object in local coordinates.
	double                    y;
	// Z location of the object in local coordinates.
	double                    z;
	// Pitch in degres to rotate the object, positive is up.
	double                    pitch;
	// Heading in local coordinates to rotate the object, clockwise.
	double                    heading;
	// Roll to rotate the object.
	double                    roll;
} XPLMDrawInfoDouble_t;



typedef void (* XPLMObjectLoaded_f)(
						 XPLMObjectRef        inObject,
						 void *               inRefcon);


XPLM_API XPLMObjectRef XPLMLoadObject(
						 const char *         inPath);


XPLM_API void       XPLMLoadObjectAsync(
						 const char *         inPath,
						 XPLMObjectLoaded_f   inCallback,
						 void *               inRefcon);


XPLM_API void       XPLMDrawObjects(
						 XPLMObjectRef        inObject,
						 int                  inCount,
						 XPLMDrawInfo_t *     inLocations,
						 int                  lighting,
						 int                  earth_relative);



XPLM_API void       XPLMUnloadObject(
						 XPLMObjectRef        inObject);





typedef void (* XPLMLibraryEnumerator_f)(
						 const char *         inFilePath,
						 void *               inRef);


XPLM_API int        XPLMLookupObjects(
						 const char *         inPath,
						 float                inLatitude,
						 float                inLongitude,
						 XPLMLibraryEnumerator_f enumerator,
						 void *               ref);



#endif //XPLMSCENERY_H
