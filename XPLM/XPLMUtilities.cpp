//
//  XPLMUtilities.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "XPLM.h"

#include "XPLMUtilities.h"


#include <filesystem>
#include <iostream>
#include <string>


#include "glue_Plugin.hpp"
namespace XPHost {
    extern std::vector<Plugin*> m_vecPlugins;
    extern std::vector<std::string> m_vecLog;
}


void* FXPLM_GetVecLogPtr() {
    return &XPHost::m_vecLog;
}



//class Plugin;
extern Plugin* global_target_plugin;



void XPLMGetSystemPath( char* outBuff ){

	std::cout << "FXPLM/ ["<< global_target_plugin->getSafeSig()
			  << "] XPLMGetSystemPath:";

	std::cout << " ret[" << fxplm_global_sys_folder << "/]\n";
    snprintf( outBuff, 512, "%s/", fxplm_global_sys_folder.c_str() );
}


void XPLMDebugString( const char* msg ){

	XPHost::m_vecLog.emplace_back( msg );

	FXPLM_DebugLogHeader("XPLMDebugString");
	std::cout << msg;

    const size_t sl = strlen(msg);
	if( msg[sl-1] != '\n' ){
		std::cout << "\n";
	}

}


int XPLMFindPluginBySignature( char* sig ){

	FXPLM_DebugLogHeader("XPLMFindPluginBySignature");

	std::cout<<" [" << std::string(sig) << "] ";

    for ( auto plugin: XPHost::m_vecPlugins ) {
        if( plugin->m_pluginSig == sig ){
            std::cout << " found plugin: " << plugin->m_plugin_id << "\n";
            return plugin->m_plugin_id;
        }
    }

    std::cout << " 404\n";
    //returning 0 will route all msgs into the host.
    //returning -1 will probably set a flag on the querying plugin side.
    return 0;//-1;
}


// this can send from any to any
void FXPLM_SendMessageToPlugin( int from, int to, int message, void* param ){

	FXPLM_DebugLogHeader("FXPLM_SendMessageToPlugin");
	std::cout << " from:" << from;
	std::cout << " to:" << to;
	std::cout << " msg:" << (void*)(int64_t)message;
	std::cout << " param:" << (void*)param;
	std::cout << "\n";


#if 0 //FIXME: FXPLM: port vecPluginMessages
    //this is a plugin registration msg, decode it.
    if ( message == 0x01000000 ) {
        std::string payload = std::string( (char*)param );
        XPHost::m_vecPluginMessages.push_back(payload);
        std::cout << payload << "\n";
    }

    //log for host gui
    XPHost::m_vecPluginMessages.push_back(msg);
#endif


    if ( to == 0 ) {
        //msg is to host
        std::cout << " * msg is to host\n";
        return;
    }


    size_t target_id = to;
    if( target_id >= XPHost::m_vecPlugins.size() ){
        std::cerr << "FXPLM_SendMessageToPlugin:  target_id out of range: " << target_id << "\n";
        return;
    }

    auto target = XPHost::m_vecPlugins[target_id];
    target->takeContext();
    	target->send_xpl_message( from, message, param );
    target->releaseContext();

}


//this can only send from a plugin to another plugin or the host.
//this version is the SDK compliant version
void XPLMSendMessageToPlugin( int to, int message, void* param ){

	FXPLM_DebugLogHeader("XPLMSendMessageToPlugin");
	std::cout << " to:" << to;
	std::cout << " msg:" << (void*)(int64_t)message;
	std::cout << " param:" << (void*)param;
	std::cout << "\n";

    int sender_id = global_target_plugin->m_plugin_id;
	FXPLM_SendMessageToPlugin( sender_id, to, message, param );

}




XPLM_API XPLMCommandRef FXPLM_CommandInfo( int plugin_id, int cmd_id ) {
    auto p = XPHost::m_vecPlugins[plugin_id];
    auto cmd = p->m_vecCommands[cmd_id];

    return cmd;
}


XPLM_API int FXPLM_CommandCountForPluginID( int plugin_id ) {
    auto p = XPHost::m_vecPlugins[plugin_id];

    return p->m_vecCommands.size();
}









XPLMCommandRef XPLMFindCommand(
        const char *         inName){
//    std::cout<<"FXPLM/ XPLMFindCommand:[" << inName << "]\n";

    
    for( const auto& p: XPHost::m_vecPlugins ){
        for( const auto& cmd: p->m_vecCommands ){
            if( cmd->m_name == inName ){
//                std::cout << "found cmd\n";
                return cmd;
            }
        }
    }


#define FXPLM_AUTO_CMD_CREATE 0 //FIXME:
#if FXPLM_AUTO_CMD_CREATE
    auto cmd = new xpCmdCustom( inName, "inDescription" );

    if ( global_target_plugin ) {
        std::cout << "auto created cmd, attempting to assing to global_target_plugin\n";
        global_target_plugin->m_vecCommands.push_back( cmd );

    }else {
        std::cerr << "global_target_plugin is nullptr\n";
    }

    std::cout << "attempting to return new auto created cmd handle\n";
    return cmd;
#endif
#undef FXPLM_AUTO_CMD_CREATE

#define FXPLM_REPORT_CMD_404 0
#if FXPLM_REPORT_CMD_404
	//FIXME: report querying plugin
    std::cout << "FXPLM/ XPLMFindCommand: 404: [" + std::string(inName) + "]\n";
#endif
#undef FXPLM_REPORT_CMD_404

    return nullptr;

};


void       XPLMCommandBegin(
        XPLMCommandRef       inCommand){
//    std::cout<<"XPLMCommandBegin\n";
    if( inCommand ) {
//        std::cout<<"got cmd ptr..\n";
        auto cmd = (xpCmdCustom *) inCommand;
        cmd->callBegin();
    }
};


void       XPLMCommandEnd(
        XPLMCommandRef       inCommand){
//    std::cout<<"XPLMCommandEnd\n";
    if( inCommand ) {
//        std::cout<<"got cmd ptr..\n";
        auto cmd = (xpCmdCustom *) inCommand;
        cmd->callEnd();
    }
};


void       XPLMCommandOnce(
        XPLMCommandRef       inCommand){
//    std::cout<<"XPLMCommandOnce\n";

    if( inCommand ){
//        std::cout<<"got cmd ptr..\n";
        auto cmd = (xpCmdCustom*)inCommand;
        cmd->callBegin();
        cmd->callEnd();

//        std::cout<<"ran cmd.\n";
    }else{
//        throw std::runtime_error("XPLMCommandOnce: cmd id is nullptr");
        std::cerr << "XPLMCommandOnce: cmd id is nullptr\n";
    }

};


XPLMCommandRef XPLMCreateCommand(
        const char *         inName,
        const char *         inDescription){

	FXPLM_DebugLogHeader("XPLMCreateCommand");
	std::cout<<" name:[" << inName << "]";
	std::cout<<" desc:[" << inDescription << "]";
	std::cout<<"\n";

	auto cmd = new xpCmdCustom( inName, inDescription );
	global_target_plugin->m_vecCommands.push_back( cmd );

	return cmd;

};


void       XPLMRegisterCommandHandler(
        XPLMCommandRef       inComand,
        XPLMCommandCallback_f inHandler,
        int                  inBefore,
        void *               inRefcon){
//    std::cout<<"XPLMRegisterCommandHandler:\n";

    auto cmd = (xpCmdCustom*)inComand;
    if( cmd ){

        cmd->m_cbf = inHandler;
        cmd->m_wants_before = inBefore;
        cmd->m_refcon = inRefcon;
//        std::cout<<"  xpCmdCustom params updated.\n";

    }else{
        std::cout<<"  XPLMRegisterCommandHandler: bad command ref\n";
    }

};


void       XPLMUnregisterCommandHandler(
        XPLMCommandRef       inComand,
        XPLMCommandCallback_f inHandler,
        int                  inBefore,
        void *               inRefcon){
    std::cout<<"FXPLM/ NOP/ XPLMUnregisterCommandHandler\n"; //FIXME:
};


void XPLMReloadScenery() {
    std::cout<<"FXPLM/ NOP/ XPLMReloadScenery\n"; //FIXME
};





const char * XPLMGetDirectorySeparator(void) {
    // std::cout<<"FXPLM/ XPLMGetDirectorySeparator()\n";
    return "/";
}



void XPLMGetDirectoryContents(const char* inDirectoryPath,
                             int inFirstReturn,
                             char* outFileNames,
                             int inFileNameBufSize,
                             char** outIndices,
                             int inIndexCount,
                             int* outTotalFiles,
                             int* outReturnedFiles) {

#if 1
	FXPLM_DebugLogHeader("XPLMGetDirectoryContents");
    std::cout<<"  inDirectoryPath: [" << inDirectoryPath << "]\n";
    std::cout<<"  inFirstReturn: " << inFirstReturn << "\n";
    // std::cout<<"  outFileNames: " << outFileNames << "\n";
    std::cout<<"  inFileNameBufSize: " << inFileNameBufSize << "\n";
    // std::cout<<"  outIndices: " << outIndices << "\n";
    std::cout<<"  inIndexCount: " << inIndexCount << "\n";
    // std::cout<<"  outTotalFiles: " << outTotalFiles << "\n";
    // std::cout<<"  outReturnedFiles: " << outReturnedFiles << "\n";
#endif


    if (!inDirectoryPath || !outFileNames || !outReturnedFiles) {
        if (outReturnedFiles) *outReturnedFiles = 0;
        if (outTotalFiles) *outTotalFiles = 0;
        return;
    }

#if 1 // XPLMGetDirectoryContents(...): build folder content
    std::vector<std::string> files;

    // const std::string hack_path = "/Users/br/tmp/xlua";

    // --- 1. Get Directory Contents using C++17 Filesystem ---
    try {
        // Collect all filenames in the directory
        for (const auto& entry : std::filesystem::directory_iterator(inDirectoryPath)) {
        // for (const auto& entry : std::filesystem::directory_iterator(hack_path)) {
            // Only capture the filename part (not the full path)
            files.push_back(entry.path().filename().string());
        }
    } catch (const std::exception& e) {
        // Handle directory read errors by returning zero files
        if (outReturnedFiles) *outReturnedFiles = 0;
        if (outTotalFiles) *outTotalFiles = 0;
        return;
    }

    // --- 2. Set Total Files Count ---
    if (outTotalFiles) {
        *outTotalFiles = static_cast<int>(files.size());
    }

    // --- 3. Prepare for Copying ---
    int availableSpace = inFileNameBufSize;
    int filesReturned = 0;
    int currentPos = 0;

    // Skip files before inFirstReturn
    size_t startIndex = static_cast<size_t>(inFirstReturn);

    // --- 4. Process and Copy Files ---
    for (size_t i = startIndex;
         i < files.size() &&
         availableSpace > 0 &&
         // Stop processing files if the index array is full (and we have an array to fill)
         (outIndices == nullptr || filesReturned < inIndexCount);
         ++i)
    {
        const std::string& filename = files[i];
        size_t fileLen = filename.length();

        // Check if we have space for this filename + null terminator
        if (availableSpace >= (fileLen + 1)) {

            // Copy filename to output buffer
            std::strcpy(outFileNames + currentPos, filename.c_str());
            // std::cout<<"FXPLM/ dir content: fn: [" << filename << "]\n";

            // Update indices if requested and we haven't exceeded the index count
            if (outIndices && filesReturned < inIndexCount) {
                outIndices[filesReturned] = outFileNames + currentPos;
            }

            // Advance position and reduce available space
            currentPos += fileLen + 1;
            availableSpace -= fileLen + 1;
            filesReturned++;
        } else {
            // Buffer is full (or not large enough for the next file)
            break;
        }
    }

    // --- 5. Set Returned Files Count ---
    if (outReturnedFiles) {
        *outReturnedFiles = filesReturned;
    }
#endif

}



XPLM_API char *     XPLMExtractFileAndPath(
                         char *               inFullPath) {

	FXPLM_DebugLogHeader("XPLMExtractFileAndPath");
    std::cout<<" ["<< inFullPath <<"]\n";

    size_t i = strlen(inFullPath);;
    for (; i-- > 0; ) {
        if (inFullPath[i] == '/') {
            //found sep, split the string
            inFullPath[i] = 0;
            i++; //move to start of filename
            break;
        }
    }

    return inFullPath + i;

}




XPLM_API void *     XPLMFindSymbol(
                         const char *         inString) {

	FXPLM_DebugLogHeader("XPLMFindSymbol");
	std::cout<<" ["<< inString <<"]";

    void* fn_h = dlsym(RTLD_DEFAULT, inString);
    if( ! fn_h ){
    	std::cout << " / ret:nullptr - 404\n";
    }else{
    	std::cout << " / ret:" << fn_h << "\n";
    }

    return fn_h;

}



XPLM_API void       XPLMGetVersions(
                         int *                outXPlaneVersion,
                         int *                outXPLMVersion,
                         XPLMHostApplicationID * outHostID) {

	FXPLM_DebugLogHeader("XPLMGetVersions");
	std::cout << "\n";

	//FIXME: configurable version vals for XPLMGetVersions
    *outXPlaneVersion = 120;
    *outXPLMVersion = 400;

    *outHostID = xplm_Host_XPlane;
}


XPLM_API int        XPLMLoadDataFile(
                         XPLMDataFileType     inFileType,
                         const char *         inFilePath)    /* Can be NULL */
{

    FXPLM_DebugLogHeader("NOP/ XPLMLoadDataFile");

    switch (inFileType) {
    case xplm_DataFile_Situation:
        std::cout<<" type:[sit file]";
        break;
    case xplm_DataFile_ReplayMovie:
        std::cout<<" type:[replay file]";
        break;
    }

    std::cout<<" filename:["<< inFilePath <<"]\n";

    return 0;

}


XPLM_API int        XPLMSaveDataFile(
                         XPLMDataFileType     inFileType,
                         const char *         inFilePath) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMSaveDataFile");
}



