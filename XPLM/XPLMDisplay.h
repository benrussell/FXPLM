//
//  XPLMDisplay.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef XPLMDisplay_hpp
#define XPLMDisplay_hpp

#include "defs.h"


typedef void* XPLMWindowID;


//#include "../Plugin.h"
class Plugin;
extern Plugin* global_target_plugin;



typedef void* XPLMAvionicsID;
//typedef void* XPLMAvionicsBezelCallback_f;
typedef void (* XPLMAvionicsBezelCallback_f)(
        float                inAmbiantR,
        float                inAmbiantG,
        float                inAmbiantB,
        void *               inRefcon);

//typedef void* XPLMAvionicsScreenCallback_f;
typedef void (* XPLMAvionicsScreenCallback_f)(
        void *               inRefcon);


//typedef void* XPLMAvionicsMouse_f;
//typedef void* XPLMAvionicsMouse_f;
typedef void* XPLMAvionicsMouseWheel_f;
typedef void* XPLMAvionicsCursor_f;

enum [[maybe_unused]] XPLMMouseStatus{
    xplm_MouseDown=1,
    xplm_MouseDrag=2,
    xplm_MouseUp=3
};

//typedef void* XPLMAvionicsMouse_f;
//typedef void* XPLMAvionicsMouse_f;
typedef int (* XPLMAvionicsMouse_f)(
        int                  x,
        int                  y,
        XPLMMouseStatus      inMouse,
        void *               inRefcon);

typedef void* XPLMAvionicsMouseWheel_f;
typedef void* XPLMAvionicsCursor_f;
typedef void* XPLMAvionicsKeyboard_f;
typedef void* XPLMAvionicsBrightness_f;


typedef struct XPLMCreateAvionics_t{
    // Used to inform XPLMCreateAvionicsEx() of the SDK version you compiled against; should always be set to sizeof(XPLMCreateAvionics_t)
    int                       structSize;
    // Width of the device's screen in pixels.
    int                       screenWidth;
    // Height of the device's screen in pixels.
    int                       screenHeight;
    // Width of the bezel around your device's screen for 2D pop-ups.
    int                       bezelWidth;
    // Height of the bezel around your device's screen for 2D pop-ups.
    int                       bezelHeight;
    // The screen's lateral offset into the bezel for 2D pop-ups.
    int                       screenOffsetX;
    // The screen's vertical offset into the bezel for 2D pop-ups.
    int                       screenOffsetY;
    // If set to true (1), X-Plane won't call your plugin to re-render the device's screen every frame. Instead, you should tell X-Plane you want to refresh your screen with XPLMAvionicsNeedsDrawing(), and X-Plane will call you before rendering the next simulator frame.
    int                       drawOnDemand;
    // The draw callback you will use to draw the 2D-popup bezel. This is called only when the popup window is visible, and X-Plane is about to draw the bezel in it.
    XPLMAvionicsBezelCallback_f bezelDrawCallback;
    // The draw callback you will be using to draw into the device's screen framebuffer.
    XPLMAvionicsScreenCallback_f drawCallback;
    // The mouse click callback that is called when the user clicks onto your bezel.
    XPLMAvionicsMouse_f       bezelClickCallback;
    // The mouse click callback that is called when the user clicks onto your bezel.
    XPLMAvionicsMouse_f       bezelRightClickCallback;
    // The callback that is called when the users uses the scroll wheel over your avionics' bezel.
    XPLMAvionicsMouseWheel_f  bezelScrollCallback;
    // The callback that lets you determine what cursor should be shown when the mouse is over your device's bezel.
    XPLMAvionicsCursor_f      bezelCursorCallback;
    // The mouse click callback that is called when the user clicks onto your screen.
    XPLMAvionicsMouse_f       screenTouchCallback;
    // The right mouse click callback that is called when the user clicks onto your screen.
    XPLMAvionicsMouse_f       screenRightTouchCallback;
    // The callback that is called when the users uses the scroll wheel over your avionics' screen.
    XPLMAvionicsMouseWheel_f  screenScrollCallback;
    // The callback that lets you determine what cursor should be shown when the mouse is over your device's screen.
    XPLMAvionicsCursor_f      screenCursorCallback;
    // The key callback that is called when the user types in your popup.
    XPLMAvionicsKeyboard_f    keyboardCallback;
    // The callback that is called to determine the absolute brightness of the device's screen. Set to NULL to use X-Plane's default behaviour.
    XPLMAvionicsBrightness_f  brightnessCallback;
    // A null-terminated string of maximum 64 characters to uniquely identify your cockpit device. This must be unique (you cannot re-use an ID that X-Plane or another plugin provides), and it must not contain spaces. This is the string the OBJ file must reference when marking polygons with ATTR_cockpit_device. The string is copied when you call XPLMCreateAvionicsEx, so you don't need to hold this string in memory after the call.
    char *                    deviceID;
    // A null-terminated string to give a user-readable name to your device, which can be presented in UI dialogs.
    char *                    deviceName;
    // A reference which will be passed into your draw and mouse callbacks. Use this to pass information to yourself as needed.
    void *                    refcon;
} XPLMCreateAvionics_t;




typedef void (* XPLMDrawWindow_f)(
        XPLMWindowID         inWindowID,
        void *               inRefcon);



typedef int (* XPLMHandleMouseClick_f)(
        XPLMWindowID         inWindowID,
        int                  x,
        int                  y,
        XPLMMouseStatus      inMouse,
        void *               inRefcon);


enum [[maybe_unused]] XPLMKeyFlags{
	xplm_ShiftFlag=1,	//The shift key is down
	xplm_OptionAltFlag=2,	//The option or alt key is down
	xplm_ControlFlag=4,	//The control key is down
	xplm_DownFlag=8,	//The key is being pressed down
	xplm_UpFlag=16	//The key is being released
};

typedef void (* XPLMHandleKey_f)(
        XPLMWindowID         inWindowID,
        char                 inKey,
        XPLMKeyFlags         inFlags,
        char                 inVirtualKey,
        void *               inRefcon,
        int                  losingFocus);


enum [[maybe_unused]] XPLMCursorStatus {
	xplm_CursorDefault = 0,    // X-Plane manages the cursor normally, plugin does not affect the cursor.
	xplm_CursorHidden = 1,     // X-Plane hides the cursor.
	xplm_CursorArrow = 2,      // X-Plane shows the cursor as the default arrow.
	xplm_CursorCustom = 3,     // X-Plane shows the cursor but lets you select an OS cursor.
	xplm_CursorRotateSmall = 4,      // X-Plane shows a small bi-directional knob-rotating cursor.
	xplm_CursorRotateSmallLeft = 5,  // X-Plane shows a small counter-clockwise knob-rotating cursor.
	xplm_CursorRotateSmallRight = 6, // X-Plane shows a small clockwise knob-rotating cursor.
	xplm_CursorRotateMedium = 7,     // X-Plane shows a medium bi-directional knob-rotating cursor.
	xplm_CursorRotateMediumLeft = 8, // X-Plane shows a medium counter-clockwise knob-rotating cursor.
	xplm_CursorRotateMediumRight = 9, // X-Plane shows a medium clockwise knob-rotating cursor.
	xplm_CursorRotateLarge = 10,     // X-Plane shows a large bi-directional knob-rotating cursor.
	xplm_CursorRotateLargeLeft = 11, // X-Plane shows a large counter-clockwise knob-rotating cursor.
	xplm_CursorRotateLargeRight = 12, // X-Plane shows a large clockwise knob-rotating cursor.
	xplm_CursorUpDown = 13,          // X-Plane shows an up-and-down arrows cursor.
	xplm_CursorDown = 14,            // X-Plane shows a down arrow cursor.
	xplm_CursorUp = 15,              // X-Plane shows an up arrow cursor.
	xplm_CursorLeftRight = 16,       // X-Plane shows a left-right arrow cursor.
	xplm_CursorLeft = 17,            // X-Plane shows a left arrow cursor.
	xplm_CursorRight = 18,           // X-Plane shows a right arrow cursor.
	xplm_CursorButton = 19,          // X-Plane shows a button-pushing cursor.
	xplm_CursorHandle = 20,          // X-Plane shows a handle-grabbing cursor.
	xplm_CursorFourArrows = 21,      // X-Plane shows a four-arrows cursor.
	xplm_CursorSplitterH = 22,       // X-Plane shows a cursor to drag a horizontal splitter bar.
	xplm_CursorSplitterV = 23,       // X-Plane shows a cursor to drag a vertical splitter bar.
	xplm_CursorText = 24             // X-Plane shows an I-Beam cursor for text editing.
};


typedef XPLMCursorStatus (* XPLMHandleCursor_f)(
        XPLMWindowID         inWindowID,
        int                  x,
        int                  y,
        void *               inRefcon);


typedef int (* XPLMHandleMouseWheel_f)(
        XPLMWindowID         inWindowID,
        int                  x,
        int                  y,
        int                  wheel,
        int                  clicks,
        void *               inRefcon);

enum [[maybe_unused]] XPLMWindowDecoration{
    //FIXME: add members for WindowDecoration
};

enum [[maybe_unused]] XPLMWindowLayer{
    //FIXME: Add members for WindowLayer
};




typedef struct XPLMCreateWindow_t{
    // Used to inform XPLMCreateWindowEx() of the SDK version you compiled against; should always be set to sizeof(XPLMCreateWindow_t)
    int                       structSize;
    // Left bound, in global desktop boxels
    int                       left;
    // Top bound, in global desktop boxels
    int                       top;
    // Right bound, in global desktop boxels
    int                       right;
    // Bottom bound, in global desktop boxels
    int                       bottom;
    int                       visible;
    XPLMDrawWindow_f          drawWindowFunc;
    // A callback to handle the user left-clicking within your window (or NULL to ignore left clicks)
    XPLMHandleMouseClick_f    handleMouseClickFunc;
    XPLMHandleKey_f           handleKeyFunc;
    XPLMHandleCursor_f        handleCursorFunc;
    XPLMHandleMouseWheel_f    handleMouseWheelFunc;
    // A reference which will be passed into each of your window callbacks. Use this to pass information to yourself as needed.
    void *                    refcon;
    // Specifies the type of X-Plane 11-style "wrapper" you want around your window, if any
    XPLMWindowDecoration      decorateAsFloatingWindow;
    XPLMWindowLayer           layer;
    // A callback to handle the user right-clicking within your window (or NULL to ignore right clicks)
    XPLMHandleMouseClick_f    handleRightClickFunc;
} XPLMCreateWindow_t;





XPLM_API void XPLMGetScreenBoundsGlobal(
        int *outLeft,    /* Can be NULL */
        int *outTop,    /* Can be NULL */
        int *outRight,    /* Can be NULL */
        int *outBottom /* Can be NULL */
);


XPLM_API void XPLMCreateAvionicsEx(
        void *params
);


XPLM_API void XPLMSetWindowGeometry(XPLMWindowID inWindowID, int left, int top, int right, int bottom);



enum [[maybe_unused]] XPLMWindowPositioningMode {
	xplm_WindowPositionFree = 0,               // The default positioning mode. Set the window geometry and its future position will be determined by its window gravity, resizing limits, and user interactions.
	xplm_WindowCenterOnMonitor = 1,            // Keep the window centered on the monitor you specify
	xplm_WindowFullScreenOnMonitor = 2,        // Keep the window full screen on the monitor you specify
	xplm_WindowFullScreenOnAllMonitors = 3,    // Like gui_window_full_screen_on_monitor, but stretches over *all* monitors and popout windows. This is an obscure one... unless you have a very good reason to need it, you probably don't!
	xplm_WindowPopOut = 4,                     // A first-class window in the operating system, completely separate from the X-Plane window(s)
	xplm_WindowVR = 5                          // A floating window visible on the VR headset
};

XPLM_API void XPLMSetWindowPositioningMode( XPLMWindowID         inWindowID,
											XPLMWindowPositioningMode inPositioningMode,
											int                  inMonitorIndex);


XPLM_API void XPLMSetWindowResizingLimits(XPLMWindowID         inWindowID,
                                                  int                  inMinWidthBoxels,
                                                  int                  inMinHeightBoxels,
                                                  int                  inMaxWidthBoxels,
                                                  int                  inMaxHeightBoxels);

XPLM_API void XPLMSetWindowTitle(XPLMWindowID inWindowID, const char *new_title);


XPLM_API void XPLMGetWindowGeometry(XPLMWindowID inWindowID, int *left, int *top, int *right, int *bottom);

XPLM_API int XPLMGetWindowIsVisible(XPLMWindowID inWindowID);

XPLM_API void XPLMSetWindowIsVisible(XPLMWindowID inWindowID, int inIsVisible);


XPLM_API int XPLMIsWindowInFront();


XPLM_API XPLMWindowID XPLMCreateWindowEx(XPLMCreateWindow_t *params);


XPLM_API void XPLMDestroyWindow(XPLMWindowID inWindowID);


XPLM_API int XPLMHasKeyboardFocus(XPLMWindowID inWindowID);


XPLM_API void XPLMTakeKeyboardFocus(XPLMWindowID inWindowID);




XPLM_API void       XPLMAvionicsNeedsDrawing(
        XPLMAvionicsID       inHandle);


XPLM_API void       XPLMDestroyAvionics(
        XPLMAvionicsID       inHandle);


// https://developer.x-plane.com/sdk/XPLMDrawingPhase/

enum [[maybe_unused]] XPLMDrawingPhase{

	/* Deprecated as of XPLM302 */
	xplm_Phase_FirstScene      = 0,   // Earliest 3-D draw point
	xplm_Phase_Terrain         = 5,   // Land and water
	xplm_Phase_Airports        = 10,  // Runways and airport detail
	xplm_Phase_Vectors         = 15,  // Roads, trails, trains
	xplm_Phase_Objects         = 20,  // 3-D objects
	xplm_Phase_Airplanes       = 25,  // External aircraft views
										//SASL3 uses this
	xplm_Phase_LastScene       = 30,  // Last 3-D draw point

	/* Active Phases */
	xplm_Phase_Modern3D        = 31,  // Modern 3-D drawing
	xplm_Phase_FirstCockpit    = 35,  // First 2-D draw point
	xplm_Phase_Panel           = 40,  // Static aircraft panel
	xplm_Phase_Gauges          = 45,  // Moving aircraft parts
										//SASL3 uses this
	xplm_Phase_Window          = 50,  // Floating plugin windows
	xplm_Phase_LastCockpit     = 55,  // Last 2-D draw point

	/* Removed as of XPLM300 (Use XPLMMap API) */
	xplm_Phase_LocalMap3D      = 100,
	xplm_Phase_LocalMap2D      = 101,
	xplm_Phase_LocalMapProfile = 102

};




typedef int (* XPLMDrawCallback_f)(
                         XPLMDrawingPhase     inPhase,
                         int                  inIsBefore,
                         void *               inRefcon);


// ret 1 for cb register success
XPLM_API int         XPLMRegisterDrawCallback(
         XPLMDrawCallback_f   inCallback,
        XPLMDrawingPhase     inPhase,
        int                  inWantsBefore,
        void *               inRefcon);


XPLM_API int        XPLMUnregisterDrawCallback(
                         XPLMDrawCallback_f   inCallback,
                         XPLMDrawingPhase     inPhase,
                         int                  inWantsBefore,
                         void *               inRefcon);




XPLM_API void XPLMGetMouseLocationGlobal();



XPLM_API void       XPLMBringWindowToFront(
                         XPLMWindowID         inWindow);



XPLM_API void       XPLMGetScreenSize(
                         int *                outWidth,    /* Can be NULL */
                         int *                outHeight); /* can be NULL */





XPLM_API void       XPLMSetWindowRefCon(
                         XPLMWindowID         inWindowID,
                         void *               inRefcon);




typedef void (* XPLMReceiveMonitorBoundsGlobal_f)(
                         int                  inMonitorIndex,
                         int                  inLeftBx,
                         int                  inTopBx,
                         int                  inRightBx,
                         int                  inBottomBx,
                         void *               inRefcon);


XPLM_API void       XPLMGetAllMonitorBoundsGlobal(
                         XPLMReceiveMonitorBoundsGlobal_f inMonitorBoundsCallback,
                         void *               inRefcon);


typedef void (* XPLMReceiveMonitorBoundsOS_f)(
                         int                  inMonitorIndex,
                         int                  inLeftPx,
                         int                  inTopPx,
                         int                  inRightPx,
                         int                  inBottomPx,
                         void *               inRefcon);

XPLM_API void       XPLMGetAllMonitorBoundsOS(
                         XPLMReceiveMonitorBoundsOS_f inMonitorBoundsCallback,
                         void *               inRefcon);

XPLM_API void       XPLMGetWindowGeometryOS(
						 XPLMWindowID         inWindowID,
						 int *                outLeft,    /* Can be NULL */
						 int *                outTop,    /* Can be NULL */
						 int *                outRight,    /* Can be NULL */
						 int *                outBottom);    /* Can be NULL */

XPLM_API void       XPLMGetWindowGeometryVR(
						 XPLMWindowID         inWindowID,
						 int *                outWidthBoxels,    /* Can be NULL */
						 int *                outHeightBoxels);    /* Can be NULL */



typedef void * XPLMHotKeyID;

typedef void (* XPLMHotKey_f)(
						 void *               inRefcon);


XPLM_API XPLMHotKeyID XPLMRegisterHotKey(
						 char                 inVirtualKey,
						 XPLMKeyFlags         inFlags,
						 const char *         inDescription,
						 XPLMHotKey_f         inCallback,
						 void *               inRefcon);



typedef int (* XPLMKeySniffer_f)(
						 char                 inChar,
						 XPLMKeyFlags         inFlags,
						 char                 inVirtualKey,
						 void *               inRefcon);


XPLM_API int        XPLMRegisterKeySniffer(
						 XPLMKeySniffer_f     inCallback,
						 int                  inBeforeWindows,
						 void *               inRefcon);


XPLM_API void       XPLMSetHotKeyCombination(
						 XPLMHotKeyID         inHotKey,
						 char                 inVirtualKey,
						 XPLMKeyFlags         inFlags);



XPLM_API void       XPLMSetWindowGeometryOS(
						 XPLMWindowID         inWindowID,
						 int                  inLeft,
						 int                  inTop,
						 int                  inRight,
						 int                  inBottom);


XPLM_API void       XPLMSetWindowGeometryVR(
						 XPLMWindowID         inWindowID,
						 int                  widthBoxels,
						 int                  heightBoxels);

XPLM_API void       XPLMSetWindowGravity(
						 XPLMWindowID         inWindowID,
						 float                inLeftGravity,
						 float                inTopGravity,
						 float                inRightGravity,
						 float                inBottomGravity);

XPLM_API void       XPLMUnregisterHotKey(
						 XPLMHotKeyID         inHotKey);

XPLM_API int        XPLMUnregisterKeySniffer(
						 XPLMKeySniffer_f     inCallback,
						 int                  inBeforeWindows,
						 void *               inRefcon);

XPLM_API int        XPLMWindowIsInVR(
						 XPLMWindowID         inWindowID);

XPLM_API int        XPLMWindowIsPoppedOut(
						 XPLMWindowID         inWindowID);





#endif /* XPLMDisplay_hpp */
