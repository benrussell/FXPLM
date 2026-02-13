//
//  XPLMUtilities.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef XPLMUtilities_hpp
#define XPLMUtilities_hpp

#include "defs.h"

#include <stdio.h>



XPLM_API char *     XPLMExtractFileAndPath(
                         char *               inFullPath);


XPLM_API void XPLMGetSystemPath( char* outBuff );


XPLM_API void XPLMReloadScenery();


XPLM_API const char * XPLMGetDirectorySeparator(void);

XPLM_API void XPLMGetDirectoryContents(const char *         inDirectoryPath,
                     int                  inFirstReturn,
                     char *               outFileNames,
                     int                  inFileNameBufSize,
                     char **              outIndices,    /* Can be NULL */
                     int                  inIndexCount,
                     int *                outTotalFiles,    /* Can be NULL */
                     int *                outReturnedFiles);




XPLM_API void XPLMDebugString(const char *msg);

XPLM_API int XPLMFindPluginBySignature( char* sig );

XPLM_API void FXPLM_SendMessageToPlugin( int from, int to, int message, void* param );
XPLM_API void XPLMSendMessageToPlugin( int to, int message, void* param );


XPLM_API void* FXPLM_GetVecLogPtr();



enum XPLMCommandPhase{
xplm_CommandBegin,
xplm_CommandContinue,
xplm_CommandEnd,
};


typedef void* XPLMCommandRef;

typedef int (* XPLMCommandCallback_f)(
    XPLMCommandRef       inCommand,
    XPLMCommandPhase     inPhase,
    void *               inRefcon);


XPLM_API XPLMCommandRef XPLMFindCommand(
    const char *         inName);


XPLM_API void       XPLMCommandBegin(
    XPLMCommandRef       inCommand);


XPLM_API void       XPLMCommandEnd(
    XPLMCommandRef       inCommand);


XPLM_API void       XPLMCommandOnce(
    XPLMCommandRef       inCommand);


XPLM_API XPLMCommandRef XPLMCreateCommand(
    const char *         inName,
    const char *         inDescription);


XPLM_API void       XPLMRegisterCommandHandler(
    XPLMCommandRef       inComand,
    XPLMCommandCallback_f inHandler,
    int                  inBefore,
    void *               inRefcon);


XPLM_API void       XPLMUnregisterCommandHandler(
    XPLMCommandRef       inComand,
    XPLMCommandCallback_f inHandler,
    int                  inBefore,
    void *               inRefcon);




XPLM_API int FXPLM_CommandCountForPluginID( int plugin_id );

XPLM_API XPLMCommandRef FXPLM_CommandInfo( int plugin_id, int cmd_id );




XPLM_API void *     XPLMFindSymbol(
                         const char *         inString);


enum XPLMHostApplicationID {
    xplm_Host_Unknown=0,
    xplm_Host_XPlane=1,
    xplm_Host_PlaneMaker=2,
    xplm_Host_WorldMaker=3,
    xplm_Host_Briefer=4,
    xplm_Host_PartMaker=5,
    xplm_Host_YoungsMod=6,
    xplm_Host_XAuto=7,
    xplm_Host_Xavion=8,
    xplm_Host_Control_Pad=9,
    xplm_Host_PFD_Map=10,
    xplm_Host_RADAR=11
};

XPLM_API void       XPLMGetVersions(
                         int *                outXPlaneVersion,
                         int *                outXPLMVersion,
                         XPLMHostApplicationID * outHostID);



enum XPLMDataFileType {
    xplm_DataFile_Situation=1,	//A situation (.sit) file, which starts off a flight in a given configuration.
    xplm_DataFile_ReplayMovie=2	//A situation movie (.smo) file, which replays a past flight.
};


XPLM_API int        XPLMLoadDataFile(
                         XPLMDataFileType     inFileType,
                         const char *         inFilePath);    /* Can be NULL */



XPLM_API int        XPLMSaveDataFile(
                         XPLMDataFileType     inFileType,
                         const char *         inFilePath);



XPLM_API void       XPLMGetPrefsPath(
                         char *               outPrefsPath);



typedef void (* XPLMError_f)(
                         const char *         inMessage);

XPLM_API void       XPLMSetErrorCallback(
                         XPLMError_f          inCallback);




#endif /* XPLMUtilities_hpp */
