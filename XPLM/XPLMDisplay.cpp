//
//  XPLMDisplay.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "XPLMDisplay.h"

#include <iostream>
#include <vector>
#include <string>

#include "XPLM.h"


#include "glue_Plugin.hpp"
#include "glue_AvionicsHost.hpp"

#include "glue_WindowEx.h"


extern AvionicsHost* dev;



XPLM_API XPLMWindowID XPLMCreateWindowEx( XPLMCreateWindow_t *params ){

	FXPLM_DebugLogHeader("XPLMCreateWindowEx");
    std::cout << " params: " << std::hex << params << std::dec;

    const size_t need_size = sizeof(XPLMCreateWindow_t);
    if( need_size != params->structSize ){
        std::cout << "  params struct size mismatch/unknown\t";
        std::cout << "  sizeof():" << need_size << " / p->size:" << params->structSize << "\n";
        return nullptr;
    }



	//std::cout << " params size is good. taking a copy of the struct..\n";
	auto tmp_win = new glue_WindowEx( params );
	global_target_plugin->m_vecWindowHandles.push_back(tmp_win );

	tmp_win->z_index = global_target_plugin->m_vecWindowHandles.size();


    std::cout<< "  l,t,r,b:" << params->left <<","<< params->top <<","<< params->right <<","<< params->bottom;
    int width = params->right - params->left;
    int height = params->top - params->bottom;

    std::cout << "  w:" << width << " h:" << height;

    std::cout << std::hex << "  drawWindowFunc:" << (void*)params->drawWindowFunc;
    std::cout << "  refcon: " << params->refcon << std::dec;


    std::cout << " / ret:" << std::hex << (void*)tmp_win << std::dec << "\n";
    return (XPLMWindowID)tmp_win;

}



XPLM_API void XPLMDestroyWindow( XPLMWindowID inWindowID ){
	FXPLM_DebugLogHeader("XPLMDestroyWindow");
    std::cout << " win:" << (void*)inWindowID << "\n";

    std::vector<glue_WindowEx*> vecKeepers;
	vecKeepers.reserve(global_target_plugin->m_vecWindowHandles.size());

//    std::cout << "  finding window..\n";
    for( const auto& wh: global_target_plugin->m_vecWindowHandles ){
    	if( wh == inWindowID ) {
//			std::cout << "   drop:" << wh << "\n";
		}else{
//			std::cout << "   keep:" << wh << "\n";
			vecKeepers.emplace_back( wh );
    	}
    }
	global_target_plugin->m_vecWindowHandles.swap(vecKeepers );

    delete (glue_WindowEx*)inWindowID;
}




XPLM_API void XPLMGetWindowGeometry( XPLMWindowID inWindowID,
							int *left, //can be null
							int *top,  //can be null
							int *right,  //can be null
							int *bottom  //can be null
							){

#if 0 //FIXME: log muted
    FXPLM_DebugLogHeader("XPLMGetWindowGeometry");
    std::cout << " id:" << inWindowID;
    std::cout << "\n";
#endif

	auto b = (glue_WindowEx*)inWindowID;

	if(left){
		*left = b->m_params->left;
	}

	if(top){
		*top = b->m_params->top;
	}

	if(right){
		*right = b->m_params->right;
	}

	if(bottom){
		*bottom = b->m_params->bottom;
	}

}


XPLM_API int XPLMGetWindowIsVisible( XPLMWindowID inWindowID ){
    std::cout << "XPLMGetWindowIsVisible\n";
    auto b = (glue_WindowEx*)inWindowID;
    
    //FIXME: return glfwGetWindowAttrib(b->m_winh, GLFW_VISIBLE);;
    return 0;
}


XPLM_API void XPLMSetWindowIsVisible( XPLMWindowID inWindowID, int inIsVisible ){

	FXPLM_DebugLogHeader("XPLMSetWindowIsVisible");
	std::cout << " id:" << inWindowID << "";
	std::cout << " visible:" << inIsVisible << "";

	std::cout << "\n";


	auto b = (glue_WindowEx*)inWindowID;

    b->m_params->visible = inIsVisible;

}


XPLM_API int XPLMHasKeyboardFocus( XPLMWindowID inWindowID ){
    auto b = (glue_WindowEx*)inWindowID;
    //FIXME: return glfwGetWindowAttrib(b->m_winh, GLFW_FOCUSED);
    return 0;
}


XPLM_API int XPLMIsWindowInFront(){ //FIXME: sig is bad, no window id
	FXPLM_DebugLogHeader("HC/ XPLMIsWindowInFront");
	std::cout << " / ret:1\n";
    return 1;
}




XPLM_API void XPLMSetWindowGeometry( XPLMWindowID inWindowID, int left, int top, int right, int bottom ){

	FXPLM_DebugLogHeader("XPLMSetWindowGeometry");
	std::cout << " id:" << (void*)inWindowID << "";
	std::cout << " l:" << left << "";
    std::cout << " t:" << top << "";
    std::cout << " r:" << right << "";
    std::cout << " b:" << bottom << "";

    const int width = right - left;
    const int height = top - bottom;
	std::cout << " w():" << width << "";
	std::cout << " h():" << height << "";

	if( inWindowID == nullptr ){
		std::cout << "  **** ignored\n";
		return;
	}

	std::cout << "\n";

	auto b = (glue_WindowEx*)inWindowID;

	b->m_params->left = left;
	b->m_params->top = top;
	b->m_params->right = right;
	b->m_params->bottom = bottom;

}


XPLM_API void XPLMSetWindowPositioningMode(XPLMWindowID         inWindowID,
								  XPLMWindowPositioningMode inPositioningMode,
								  int                  inMonitorIndex){
	FXPLM_DebugLogHeader("NOP/ XPLMSetWindowPositioningMode");
	std::cout << " id:" << inWindowID << "";
	std::cout << " mode:" << inPositioningMode << "";
	std::cout << " monitor:" << inMonitorIndex << "";
	std::cout << "\n";
}


XPLM_API void XPLMSetWindowResizingLimits(XPLMWindowID         inWindowID,
                                                  int                  inMinWidthBoxels,
                                                  int                  inMinHeightBoxels,
                                                  int                  inMaxWidthBoxels,
                                                  int                  inMaxHeightBoxels){

	FXPLM_DebugLogHeader("NOP/ XPLMSetWindowResizingLimits");
	std::cout << std::hex << "  id:" << inWindowID << std::dec << "";
//    std::cout<<"  window_id:" << (size_t)inWindowID <<"";
    std::cout<<"  min width: " << inMinWidthBoxels << "";
    std::cout<<"  min height: " << inMinHeightBoxels << "";
    std::cout<<"  max width: " << inMaxWidthBoxels << "";
    std::cout<<"  max height: " << inMaxHeightBoxels << "\n";

}


XPLM_API void XPLMSetWindowTitle( XPLMWindowID inWindowID, const char* new_title ){

	FXPLM_DebugLogHeader("XPLMSetWindowTitle");
	std::cout << std::hex << "  id:" << inWindowID << std::dec << "";
	std::cout << "  title:[" << new_title << "]\n";

    auto b = (glue_WindowEx*)inWindowID;
    b->m_sWindowTitle = new_title;

}


XPLM_API void XPLMTakeKeyboardFocus( XPLMWindowID inWindowID ){

	FXPLM_DebugLogHeader("NOP/ XPLMTakeKeyboardFocus");
	std::cout << "\n";
//    glfwFocusWindow(inWindowID);
}






XPLM_API void       XPLMAvionicsNeedsDrawing(
        XPLMAvionicsID       inHandle){
    std::cout<< "NOP/ XPLMAvionicsNeedsDrawing: " << (size_t)inHandle << "\n";
}


XPLM_API void       XPLMDestroyAvionics(
        XPLMAvionicsID       inHandle){
	FXPLM_DebugLogHeader("NOP/ XPLMDestroyAvionics");
    std::cout<< "  handle: " << inHandle << "\n";
}


XPLM_API void XPLMCreateAvionicsEx( void* params ){
	FXPLM_DebugLogHeader("XPLMCreateAvionicsEx");

    auto p = (XPLMCreateAvionics_t*)params;
    std::cout<<" device_id:" << p->deviceID << "\n";
    std::cout<<" device_name:" << p->deviceName << "\n";
    std::cout<<" drawing_fn:" << std::to_string( (size_t)p->drawCallback ) << "\n";
    std::cout<<" refcon:" << std::to_string( (size_t)p->refcon ) << "\n";
    std::cout<<" width,height:" << p->screenWidth << ", " << p->screenWidth << "\n";
    std::cout<<" offset x,y:" << p->screenOffsetX << ", " << p->screenOffsetY << "\n";

    if( global_target_plugin ){
        auto av_host = new AvionicsHost{p};
        global_target_plugin->m_vecAvionicsHost.push_back( av_host );

    }else{
        throw std::runtime_error("target plugin is nullptr");
    }

}




XPLM_API void XPLMGetScreenBoundsGlobal(
        int *                outLeft,    /* Can be NULL */
        int *                outTop,    /* Can be NULL */
        int *                outRight,    /* Can be NULL */
        int *                outBottom /* Can be NULL */
){

	static int log_ctr=0;
	if( log_ctr < 10 ){
		FXPLM_DebugLogHeader("XPLMGetScreenBoundsGlobal");
		std::cout << " / ret: hc: l,t,r,b:0,768,1024,0\n";
		log_ctr++;

		if( log_ctr > 9 ){
			std::cout << "  this msg will now mute.\n";
		}
	}


    if( outLeft ){
        *outLeft = 0; //FIXME: verify values
    }

    if( outTop ){
        *outTop = 768;
    }

    if( outRight ){
        *outRight = 1024;
    }

    if( outBottom ){
        *outBottom = 0;
    }

}







XPLM_API int XPLMRegisterDrawCallback(
         XPLMDrawCallback_f   inCallback,
        XPLMDrawingPhase     inPhase,
        int                  inWantsBefore,
        void *               inRefcon){

	FXPLM_DebugLogHeader("XPLMRegisterDrawCallback");
	std::cout << "\n";

#if 1 //FIXME: FXPLM: draw callback host class
	//create a draw callback wrapper instance
	auto dcbh =
		new DrawCallbackHost(
			inCallback,
			inPhase,
			inWantsBefore,
			inRefcon
		);

	global_target_plugin->m_vecDrawCallbackHost.push_back( dcbh );
#endif

	return 1;
}



XPLM_API int        XPLMUnregisterDrawCallback(
                    XPLMDrawCallback_f   inCallback,
                    XPLMDrawingPhase     inPhase,
                    int                  inWantsBefore,
                    void *               inRefcon){

	std::cout << "FXPLM/ NOP/ XPLMUnregisterDrawCallback"; //FIXME
	std::cout << "\n";
	//ret 1 if the cb was found, ret 0 if it was not.
	return 0;
}







XPLM_API void XPLMGetMouseLocationGlobal(){
    std::cout << "FXPLM/ NOP/ XPLMGetMouseLocationGlobal\n"; //FIXME
}

//DISPLAY



XPLM_API void       XPLMBringWindowToFront(
                         XPLMWindowID         inWindow) {

	FXPLM_DebugLogHeader("DEV/ XPLMBringWindowToFront");
	std::cout << "\n";

	//return;

    // check to see if window is z_index 0
    // if not:
    	// iterate all window handles and increment their z_index value by 1.
    	// set the target win_h->z_index to 0

    // this should ensure clean consistent stacking behaviour for cheap easy code.

	std::cout << "z-shift deref: inWindow\n";
	auto win_h = (glue_WindowEx*)inWindow;
	std::cout << "  z-shift win_h:" << (void *) win_h << "\n";
	std::cout << "   z-shift title:" << win_h->m_sWindowTitle << "\n";
	std::cout << "   z-shift old z_index:" << win_h->z_index << "\n";

	if( 0 == win_h->z_index){
		std::cout << " z-shift already in front.\n";
		return;
	}


	//iterate all plugins / windows
	for( auto p: XPHost::m_vecPlugins ) {
		if (p->m_plugin_is_enabled) {
			p->takeContext();
			std::cout << " z-shift ctx push:" << p->m_pluginSig << "\n";

			std::cout << "  z-shift iter p->win_h[]\n";
			for (const auto &win_h: p->m_vecWindowHandles) {
				std::cout << "  z-shift win_h:" << (void *) win_h << "\n";
				std::cout << "   z-shift title:" << win_h->m_sWindowTitle << "\n";
				std::cout << "   z-shift z_index:" << win_h->z_index << "\n";

				win_h->z_index++;

			} //iter p->win_h[]

			std::cout << " z-shift ctx pop:" << p->m_pluginSig << "\n";
			p->releaseContext();

		}//enabled?
	}//loop plugins

	//FIXME: there is a small nice to have for this fn
	// if we record the z-index for the target before we move it then we only
	// have to z_shift increment for any windows that were below this z-index
	// if fn is focusing a window that is half way through the z-stack we will only need
	// to update the z-index values for the first half of the stack

	//update target window z_index to be 0.
	win_h->z_index = 0;
	std::cout << "z_index set. ret..\n";

}



XPLM_API void       XPLMGetScreenSize(
                         int *                outWidth,    /* Can be NULL */
                         int *                outHeight /* can be NULL */ ) {
    std::cerr <<"FXPL/ NOP/ XPLMGetScreenSize()\n";
}



XPLM_API void       XPLMSetWindowRefCon(
                         XPLMWindowID         inWindowID,
                         void *               inRefcon) {

	FXPLM_DebugLogHeader("XPLMSetWindowRefCon");
	std::cout << "  id:" << inWindowID << "";
	std::cout << "  refcon:" << (void*)inRefcon << "";

	if( inWindowID == nullptr ){
		std::cout << "  ****** ignored.\n";
		return;
	}

	std::cout << "\n";

	auto b = (glue_WindowEx*)inWindowID;
	b->m_params->refcon = inRefcon;

}




XPLM_API void       XPLMGetAllMonitorBoundsGlobal(
                         XPLMReceiveMonitorBoundsGlobal_f inMonitorBoundsCallback,
                         void *               inRefcon) {
	//FIXME: SASL 3 spams this
    //std::cerr << ("FXPLM/ NOP/ XPLMGetAllMonitorBoundsGlobal()\n");
}


XPLM_API void       XPLMGetAllMonitorBoundsOS(
                         XPLMReceiveMonitorBoundsOS_f inMonitorBoundsCallback,
                         void *               inRefcon) {
	//FIXME: SASL 3 spams this
	//std::cerr << ("FXPLM/ NOP/ XPLMGetAllMonitorBoundsOS()\n");
}


XPLM_API void       XPLMGetWindowGeometryOS(
                         XPLMWindowID         inWindowID,
                         int *                outLeft,    /* Can be NULL */
                         int *                outTop,    /* Can be NULL */
                         int *                outRight,    /* Can be NULL */
                         int *                outBottom)    /* Can be NULL */
{
	std::cerr << ("FXPL/ NOP/ XPLMGetWindowGeometryOS()\n");
}


XPLM_API void       XPLMGetWindowGeometryVR(
                         XPLMWindowID         inWindowID,
                         int *                outWidthBoxels,    /* Can be NULL */
                         int *                outHeightBoxels)    /* Can be NULL */
{
	std::cerr << ("FXPL/ NOP/ XPLMGetWindowGeometryVR()\n");
}


XPLM_API XPLMHotKeyID XPLMRegisterHotKey(
                         char                 inVirtualKey,
                         XPLMKeyFlags         inFlags,
                         const char *         inDescription,
                         XPLMHotKey_f         inCallback,
                         void *               inRefcon) {
    throw std::runtime_error("FXPL/ NOP/ XPLMRegisterHotKey()\n");
}


XPLM_API int        XPLMRegisterKeySniffer(
                         XPLMKeySniffer_f     inCallback,
                         int                  inBeforeWindows,
                         void *               inRefcon) {
    FXPLM_DebugLogHeader("NOP/ XPLMRegisterKeySniffer");
    std::cout << " cb:" << (void*)inCallback;
	std::cout << " before_windows:" << inBeforeWindows;
	std::cout << " refcon:" << inRefcon;
	std::cout << " / ret_hc:0\n";

    return 0; //FIXME: ret val should be?
}


XPLM_API void       XPLMSetHotKeyCombination(
                         XPLMHotKeyID         inHotKey,
                         char                 inVirtualKey,
                         XPLMKeyFlags         inFlags) {
    throw std::runtime_error("FXPL/ NOP/ XPLMSetHotKeyCombination()\n");
}


XPLM_API void       XPLMSetWindowGeometryOS(
                         XPLMWindowID         inWindowID,
                         int                  inLeft,
                         int                  inTop,
                         int                  inRight,
                         int                  inBottom) {
    throw std::runtime_error("FXPL/ NOP/ XPLMSetWindowGeometryOS()\n");
}


XPLM_API void       XPLMSetWindowGeometryVR(
                         XPLMWindowID         inWindowID,
                         int                  widthBoxels,
                         int                  heightBoxels) {
    throw std::runtime_error("FXPL/ NOP/ XPLMSetWindowGeometryVR()\n");
}


XPLM_API void       XPLMSetWindowGravity(
                         XPLMWindowID         inWindowID,
                         float                inLeftGravity,
                         float                inTopGravity,
                         float                inRightGravity,
                         float                inBottomGravity) {

	FXPLM_DebugLogHeader("NOP/ XPLMSetWindowGravity");
	std::cout << " id:" << inWindowID;
	std::cout << " left_g:" << inLeftGravity;
	std::cout << " top_g:" << inTopGravity;
	std::cout << " right_g:" << inRightGravity;
	std::cout << " bottom_g:" << inBottomGravity;
	std::cout << "\n";

}


XPLM_API void       XPLMUnregisterHotKey(
                         XPLMHotKeyID         inHotKey) {
    FXPLM_DebugLogHeader("NOP/ XPLMUnregisterHotKey");
}

XPLM_API int        XPLMUnregisterKeySniffer(
                         XPLMKeySniffer_f     inCallback,
                         int                  inBeforeWindows,
                         void *               inRefcon) {
	FXPLM_DebugLogHeader("NOP/ XPLMUnregisterKeySniffer");
	std::cout << "\n";

	return 0; //FIXME: ret val should be?
}

XPLM_API int        XPLMWindowIsInVR(
                         XPLMWindowID         inWindowID) {
    throw std::runtime_error("FXPL/ NOP/ XPLMWindowIsInVR()\n");
}

XPLM_API int        XPLMWindowIsPoppedOut(
                         XPLMWindowID         inWindowID) {

	//FIXME: SASL3 spams this
//	std::cerr << ("FXPLM/ NOP/ XPLMWindowIsPoppedOut()\n");

	// If we return 1 here SASL3 gets stuck in an endless loop calling CreateWindowEx which currently returns nullptrs

	auto b = (glue_WindowEx*)inWindowID;

	return b->m_bPoppedOut;

}






