//
// Created by Ben on 20/11/2025.
//

#ifndef XPLMNAVIGATION_H
#define XPLMNAVIGATION_H

#include "defs.h"


#define XPLM_NAV_NOT_FOUND   -1

typedef int XPLMNavRef;


enum XPLMNavType {
	xplm_Nav_Unknown=0,
	xplm_Nav_Airport=1,
	xplm_Nav_NDB=2,
	xplm_Nav_VOR=4,
	xplm_Nav_ILS=8,
	xplm_Nav_Localizer=16,
	xplm_Nav_GlideSlope=32,
	xplm_Nav_OuterMarker=64,
	xplm_Nav_MiddleMarker=128,
	xplm_Nav_InnerMarker=256,
	xplm_Nav_Fix=512,
	xplm_Nav_DME=1024,
	xplm_Nav_LatLon=2048,
	xplm_Nav_TACAN=4096
};


XPLM_API XPLMNavRef XPLMGetFirstNavAid(void);

XPLM_API XPLMNavRef XPLMGetNextNavAid(
						 XPLMNavRef           inNavAidRef);

XPLM_API XPLMNavRef XPLMFindFirstNavAidOfType(
						 XPLMNavType          inType);

XPLM_API XPLMNavRef XPLMFindLastNavAidOfType(
						 XPLMNavType          inType);


XPLM_API XPLMNavRef XPLMFindNavAid(
						 const char *         inNameFragment,    /* Can be NULL */
						 const char *         inIDFragment,    /* Can be NULL */
						 float *              inLat,    /* Can be NULL */
						 float *              inLon,    /* Can be NULL */
						 int *                inFrequency,    /* Can be NULL */
						 XPLMNavType          inType);


XPLM_API void       XPLMGetNavAidInfo(
						 XPLMNavRef           inRef,
						 XPLMNavType *        outType,    /* Can be NULL */
						 float *              outLatitude,    /* Can be NULL */
						 float *              outLongitude,    /* Can be NULL */
						 float *              outHeight,    /* Can be NULL */
						 int *                outFrequency,    /* Can be NULL */
						 float *              outHeading,    /* Can be NULL */
						 char *               outID,    /* Can be NULL */
						 char *               outName,    /* Can be NULL */
						 char *               outReg);    /* Can be NULL */



XPLM_API int        XPLMCountFMSEntries(void);

XPLM_API int        XPLMGetDisplayedFMSEntry(void);

XPLM_API int        XPLMGetDestinationFMSEntry(void);

XPLM_API void       XPLMSetDisplayedFMSEntry(
						 int                  inIndex);

XPLM_API void       XPLMSetDestinationFMSEntry(
						 int                  inIndex);

XPLM_API void       XPLMGetFMSEntryInfo(
						 int                  inIndex,
						 XPLMNavType *        outType,    /* Can be NULL */
						 char *               outID,    /* Can be NULL */
						 XPLMNavRef *         outRef,    /* Can be NULL */
						 int *                outAltitude,    /* Can be NULL */
						 float *              outLat,    /* Can be NULL */
						 float *              outLon);    /* Can be NULL */

XPLM_API void       XPLMSetFMSEntryInfo(
						 int                  inIndex,
						 XPLMNavRef           inRef,
						 int                  inAltitude);

XPLM_API void       XPLMSetFMSEntryLatLon(
						 int                  inIndex,
						 float                inLat,
						 float                inLon,
						 int                  inAltitude);

XPLM_API void       XPLMClearFMSEntry(
						 int                  inIndex);


enum XPLMNavFlightPlan {
	xplm_Fpl_Pilot_Primary=0,
	xplm_Fpl_CoPilot_Primary=1,
	xplm_Fpl_Pilot_Approach=2,
	xplm_Fpl_CoPilot_Approach=3,
	xplm_Fpl_Pilot_Temporary=4,
	xplm_Fpl_CoPilot_Temporary=5
};


XPLM_API int        XPLMCountFMSFlightPlanEntries(
						 XPLMNavFlightPlan    inFlightPlan);

XPLM_API int        XPLMGetDisplayedFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan);

XPLM_API int        XPLMGetDestinationFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan);

XPLM_API void       XPLMSetDisplayedFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex);

XPLM_API void       XPLMSetDestinationFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex);

XPLM_API void       XPLMSetDirectToFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex);

XPLM_API void       XPLMGetFMSFlightPlanEntryInfo(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 XPLMNavType *        outType,    /* Can be NULL */
						 char *               outID,    /* Can be NULL */
						 XPLMNavRef *         outRef,    /* Can be NULL */
						 int *                outAltitude,    /* Can be NULL */
						 float *              outLat,    /* Can be NULL */
						 float *              outLon);    /* Can be NULL */

XPLM_API void       XPLMSetFMSFlightPlanEntryInfo(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 XPLMNavRef           inRef,
						 int                  inAltitude);

XPLM_API void       XPLMSetFMSFlightPlanEntryLatLon(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 float                inLat,
						 float                inLon,
						 int                  inAltitude);

XPLM_API void       XPLMSetFMSFlightPlanEntryLatLonWithId(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 float                inLat,
						 float                inLon,
						 int                  inAltitude,
						 const char*          inId,
						 unsigned int         inIdLength);

XPLM_API void       XPLMClearFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex);

XPLM_API void       XPLMLoadFMSFlightPlan(
						 int                  inDevice,
						 const char *         inBuffer,
						 unsigned int         inBufferLen);

XPLM_API unsigned int XPLMSaveFMSFlightPlan(
						 int                  inDevice,
						 char *               inBuffer,
						 unsigned int         inBufferLen);

XPLM_API XPLMNavType XPLMGetGPSDestinationType(void);

XPLM_API XPLMNavRef XPLMGetGPSDestination(void);


#endif //XPLMNAVIGATION_H
