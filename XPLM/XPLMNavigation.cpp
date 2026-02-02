//
// Created by Ben on 20/11/2025.
//

#include "XPLMNavigation.h"

#include <iostream>





XPLM_API XPLMNavRef XPLMGetFirstNavAid(void) {
	throw std::runtime_error("not impl: XPLMGetFirstNavAid");
}

XPLM_API XPLMNavRef XPLMGetNextNavAid(
						 XPLMNavRef           inNavAidRef) {
	throw std::runtime_error("not impl: XPLM");
}

XPLM_API XPLMNavRef XPLMFindFirstNavAidOfType(XPLMNavType          inType) {
	throw std::runtime_error("not impl: XPLMFindFirstNavAidOfType");
}

XPLM_API XPLMNavRef XPLMFindLastNavAidOfType(XPLMNavType          inType) {
	throw std::runtime_error("not impl: XPLMFindLastNavAidOfType");
}


XPLM_API XPLMNavRef XPLMFindNavAid(
						 const char *         inNameFragment,    /* Can be NULL */
						 const char *         inIDFragment,    /* Can be NULL */
						 float *              inLat,    /* Can be NULL */
						 float *              inLon,    /* Can be NULL */
						 int *                inFrequency,    /* Can be NULL */
						 XPLMNavType          inType) {
	throw std::runtime_error("not impl: XPLMFindNavAid");
}


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
						 char *               outReg)    /* Can be NULL */
{
	throw std::runtime_error("not impl: XPLMGetNavAidInfo");
}



XPLM_API int        XPLMCountFMSEntries(void) {
	std::cerr<<"FXPLM/ NOP/ XPLMCountFMSEntries\n";
	return 0;
}

XPLM_API int        XPLMGetDisplayedFMSEntry(void) {
	throw std::runtime_error("not impl: XPLMGetDisplayedFMSEntry");
}

XPLM_API int        XPLMGetDestinationFMSEntry(void) {
	throw std::runtime_error("not impl: XPLMGetDestinationFMSEntry");
}

XPLM_API void       XPLMSetDisplayedFMSEntry(
int                  inIndex) {
	throw std::runtime_error("not impl: XPLMSetDisplayedFMSEntry");
}

XPLM_API void       XPLMSetDestinationFMSEntry(
int                  inIndex) {
	throw std::runtime_error("not impl: XPLMSetDestinationFMSEntry");
}

XPLM_API void       XPLMGetFMSEntryInfo(
						 int                  inIndex,
						 XPLMNavType *        outType,    /* Can be NULL */
						 char *               outID,    /* Can be NULL */
						 XPLMNavRef *         outRef,    /* Can be NULL */
						 int *                outAltitude,    /* Can be NULL */
						 float *              outLat,    /* Can be NULL */
						 float *              outLon)    /* Can be NULL */
{
	throw std::runtime_error("not impl: XPLMGetFMSEntryInfo");
}

XPLM_API void       XPLMSetFMSEntryInfo(
						 int                  inIndex,
						 XPLMNavRef           inRef,
						 int                  inAltitude) {
	throw std::runtime_error("not impl: XPLMSetFMSEntryInfo");
}

XPLM_API void       XPLMSetFMSEntryLatLon(
						 int                  inIndex,
						 float                inLat,
						 float                inLon,
						 int                  inAltitude) {
	throw std::runtime_error("not impl: XPLMSetFMSEntryLatLon");
}



XPLM_API void       XPLMClearFMSEntry(
						 int                  inIndex) {
	std::cerr<<"FXPLM/ NOP/ XPLMClearFMSEntry\n";
}





XPLM_API int        XPLMCountFMSFlightPlanEntries(
XPLMNavFlightPlan    inFlightPlan) {
	throw std::runtime_error("not impl: XPLMCountFMSFlightPlanEntries");
}

XPLM_API int        XPLMGetDisplayedFMSFlightPlanEntry(
XPLMNavFlightPlan    inFlightPlan) {
	throw std::runtime_error("not impl: XPLMGetDisplayedFMSFlightPlanEntry");
}

XPLM_API int        XPLMGetDestinationFMSFlightPlanEntry(
XPLMNavFlightPlan    inFlightPlan) {
	throw std::runtime_error("not impl: XPLMGetDestinationFMSFlightPlanEntry");
}

XPLM_API void       XPLMSetDisplayedFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex) {
	throw std::runtime_error("not impl: XPLMSetDisplayedFMSFlightPlanEntry");
}

XPLM_API void       XPLMSetDestinationFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex) {
	throw std::runtime_error("not impl: XPLMSetDestinationFMSFlightPlanEntry");
}

XPLM_API void       XPLMSetDirectToFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex) {
	throw std::runtime_error("not impl: XPLMSetDirectToFMSFlightPlanEntry");
}

XPLM_API void       XPLMGetFMSFlightPlanEntryInfo(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 XPLMNavType *        outType,    /* Can be NULL */
						 char *               outID,    /* Can be NULL */
						 XPLMNavRef *         outRef,    /* Can be NULL */
						 int *                outAltitude,    /* Can be NULL */
						 float *              outLat,    /* Can be NULL */
						 float *              outLon)    /* Can be NULL */
{
	throw std::runtime_error("not impl: XPLMGetFMSFlightPlanEntryInfo");
}

XPLM_API void       XPLMSetFMSFlightPlanEntryInfo(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 XPLMNavRef           inRef,
						 int                  inAltitude) {
	throw std::runtime_error("not impl: XPLMSetFMSFlightPlanEntryInfo");
}

XPLM_API void       XPLMSetFMSFlightPlanEntryLatLon(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 float                inLat,
						 float                inLon,
						 int                  inAltitude) {
	throw std::runtime_error("not impl: XPLMSetFMSFlightPlanEntryLatLon");
}

XPLM_API void       XPLMSetFMSFlightPlanEntryLatLonWithId(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex,
						 float                inLat,
						 float                inLon,
						 int                  inAltitude,
						 const char*          inId,
						 unsigned int         inIdLength) {
	throw std::runtime_error("not impl: XPLMSetFMSFlightPlanEntryLatLonWithId");
}

XPLM_API void       XPLMClearFMSFlightPlanEntry(
						 XPLMNavFlightPlan    inFlightPlan,
						 int                  inIndex) {
	throw std::runtime_error("not impl: XPLMClearFMSFlightPlanEntry");
}

XPLM_API void       XPLMLoadFMSFlightPlan(
						 int                  inDevice,
						 const char *         inBuffer,
						 unsigned int         inBufferLen) {
	throw std::runtime_error("not impl: XPLMLoadFMSFlightPlan");
}


XPLM_API unsigned int XPLMSaveFMSFlightPlan(
						 int                  inDevice,
						 char *               inBuffer,
						 unsigned int         inBufferLen) {
	throw std::runtime_error("not impl: XPLMSaveFMSFlightPlan");
}

XPLM_API XPLMNavType XPLMGetGPSDestinationType(void) {
	throw std::runtime_error("not impl: XPLMGetGPSDestinationType");
}

XPLM_API XPLMNavRef XPLMGetGPSDestination(void) {
	throw std::runtime_error("not impl: XPLMGetGPSDestination");
}


