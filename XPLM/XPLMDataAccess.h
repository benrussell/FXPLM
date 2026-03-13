//
//  XPLMDataAccess.hpp
//  XPLM
//
//  Created by Ben on 19/10/2025.
//

#ifndef XPLMDataAccess_hpp
#define XPLMDataAccess_hpp

#include "defs.h"

#include <stdio.h>


#include "xp_dref.hpp"


//typedef xp_dref* XPLMDataRef;
typedef void* XPLMDataRef;



namespace XPHost {
	extern float fps;
	extern std::vector<xp_dref*> m_dref_pool;
}



enum XPLMDataTypeID {
	xplmType_Unknown = 0,    // Data of a type the current XPLM doesn't do.
	xplmType_Int = 1,        // A single 4-byte integer, native endian.
	xplmType_Float = 2,      // A single 4-byte float, native endian.
	xplmType_Double = 4,     // A single 8-byte double, native endian.
	xplmType_FloatArray = 8, // An array of 4-byte floats, native endian.
	xplmType_IntArray = 16,  // An array of 4-byte integers, native endian.
	xplmType_Data = 32       // A variable block of data.
};






XPLM_API void XPLMSetDataf( XPLMDataRef dref_h, float new_value );

XPLM_API void XPLMSetDatavf( XPLMDataRef dref_h, float* new_values, int offset, int count );

XPLM_API void XPLMSetDatavi( XPLMDataRef dref_h, int* new_values, int offset, int count );


XPLM_API float XPLMGetDataf( XPLMDataRef dref_h );

XPLM_API int XPLMGetDatai( XPLMDataRef dref_h );

XPLM_API void XPLMSetDatai( XPLMDataRef dref_h, int val );


XPLM_API int XPLMGetDatavf( XPLMDataRef dref_h, float* buffer, int offset, int count );

XPLM_API int XPLMGetDatavi( XPLMDataRef dref_h, int* buffer, int offset, int count );


XPLM_API int XPLMIsDataRefGood( XPLMDataRef dref );

XPLM_API XPLMDataTypeID XPLMGetDataRefTypes( XPLMDataRef dref_h );

XPLM_API double XPLMGetDatad( XPLMDataRef dref_h );
XPLM_API void XPLMSetDatad( XPLMDataRef dref_h, double new_value );

XPLM_API void XPLMGetDatab();
XPLM_API void XPLMSetDatab();



XPLM_API XPLMDataRef XPLMFindDataRef( const char* dref_name );



//these are all placeholder type defs
typedef int    (* XPLMGetDatai_f)(void* inRefcon);
typedef void   (* XPLMSetDatai_f)(void* inRefcon, int inValue);

typedef float  (* XPLMGetDataf_f)(void* inRefcon);
typedef void   (* XPLMSetDataf_f)(void* inRefcon, float inValue);

typedef double (* XPLMGetDatad_f)(void* inRefcon);
typedef void   (* XPLMSetDatad_f)(void* inRefcon, double inValue);

typedef int    (* XPLMGetDatavi_f)(void* inRefcon, int* outValues, int inOffset, int inMax);
typedef void   (* XPLMSetDatavi_f)(void* inRefcon, int* inValues, int inOffset, int inCount);

typedef int    (* XPLMGetDatavf_f)(void* inRefcon, float* outValues, int inOffset, int inMax);
typedef void   (* XPLMSetDatavf_f)(void* inRefcon, float* inValues, int inOffset, int inCount);

typedef int    (* XPLMGetDatab_f)(void* inRefcon, void* outValue, int inOffset, int inMaxBytes);
typedef void   (* XPLMSetDatab_f)(void* inRefcon, void* inValue, int inOffset, int inLength);



struct FXPLM_DataAccessorBundle_t{
	int32_t				structSize;
	XPLMGetDatai_f       inReadInt;
	XPLMSetDatai_f       inWriteInt;
	XPLMGetDataf_f       inReadFloat;
	XPLMSetDataf_f       inWriteFloat;
	XPLMGetDatad_f       inReadDouble;
	XPLMSetDatad_f       inWriteDouble;
	XPLMGetDatavi_f      inReadIntArray;
	XPLMSetDatavi_f      inWriteIntArray;
	XPLMGetDatavf_f      inReadFloatArray;
	XPLMSetDatavf_f      inWriteFloatArray;
	XPLMGetDatab_f       inReadData;
	XPLMSetDatab_f       inWriteData;
};


XPLM_API XPLMDataRef XPLMRegisterDataAccessor(
                             const char *         inDataName,
                             XPLMDataTypeID       inDataType,
                             int                  inIsWritable,
                             XPLMGetDatai_f       inReadInt,
                             XPLMSetDatai_f       inWriteInt,
                             XPLMGetDataf_f       inReadFloat,
                             XPLMSetDataf_f       inWriteFloat,
                             XPLMGetDatad_f       inReadDouble,
                             XPLMSetDatad_f       inWriteDouble,
                             XPLMGetDatavi_f      inReadIntArray,
                             XPLMSetDatavi_f      inWriteIntArray,
                             XPLMGetDatavf_f      inReadFloatArray,
                             XPLMSetDatavf_f      inWriteFloatArray,
                             XPLMGetDatab_f       inReadData,
                             XPLMSetDatab_f       inWriteData,
                             void *               inReadRefcon,
                             void *               inWriteRefcon);

XPLM_API void XPLMUnregisterDataAccessor( XPLMDataRef inDataRef );




typedef void (* XPLMDataChanged_f)(
						 void *               inRefcon);

XPLM_API int        XPLMShareData(
						 const char *         inDataName,
						 XPLMDataTypeID       inDataType,
						 XPLMDataChanged_f    inNotificationFunc,
						 void *               inNotificationRefcon);



XPLM_API int        XPLMUnshareData(
						 const char *         inDataName,
						 XPLMDataTypeID       inDataType,
						 XPLMDataChanged_f    inNotificationFunc,
						 void *               inNotificationRefcon);


XPLM_API int        XPLMCanWriteDataRef(
						 XPLMDataRef          inDataRef);


#endif /* XPLMDataAccess_hpp */
