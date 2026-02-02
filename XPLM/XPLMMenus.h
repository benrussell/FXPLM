//
// Created by Ben on 15/11/2025.
//

#ifndef XPLMMENUS_H
#define XPLMMENUS_H

#include "defs.h"

#include "XPLMUtilities.h"


enum XPLMMenuCheck {
	xplm_Menu_NoCheck,
	xplm_Menu_Unchecked,
	xplm_Menu_Checked
};


typedef void * XPLMMenuID;


typedef void (* XPLMMenuHandler_f)(
						 void *               inMenuRef,
						 void *               inItemRef);


XPLM_API XPLMMenuID XPLMFindPluginsMenu(void);


XPLM_API XPLMMenuID XPLMFindAircraftMenu(void);


XPLM_API XPLMMenuID XPLMCreateMenu(
						 const char *         inName,
						 XPLMMenuID           inParentMenu,
						 int                  inParentItem,
						 XPLMMenuHandler_f    inHandler,
						 void *               inMenuRef);


XPLM_API void       XPLMDestroyMenu(
						 XPLMMenuID           inMenuID);


XPLM_API void       XPLMClearAllMenuItems(
						 XPLMMenuID           inMenuID);


XPLM_API int        XPLMAppendMenuItem(
						 XPLMMenuID           inMenu,
						 const char *         inItemName,
						 void *               inItemRef,
						 int                  inDeprecatedAndIgnored);


XPLM_API int        XPLMAppendMenuItemWithCommand(
						 XPLMMenuID           inMenu,
						 const char *         inItemName,
						 XPLMCommandRef       inCommandToExecute);


XPLM_API void       XPLMAppendMenuSeparator(
						 XPLMMenuID           inMenu);


XPLM_API void       XPLMSetMenuItemName(
						 XPLMMenuID           inMenu,
						 int                  inIndex,
						 const char *         inItemName,
						 int                  inDeprecatedAndIgnored);


XPLM_API void       XPLMCheckMenuItem(
						 XPLMMenuID           inMenu,
						 int                  index,
						 XPLMMenuCheck        inCheck);


XPLM_API void       XPLMCheckMenuItemState(
						 XPLMMenuID           inMenu,
						 int                  index,
						 XPLMMenuCheck *      outCheck);


XPLM_API void       XPLMEnableMenuItem(
						 XPLMMenuID           inMenu,
						 int                  index,
						 int                  enabled);

XPLM_API void       XPLMRemoveMenuItem(
						 XPLMMenuID           inMenu,
						 int                  inIndex);


XPLM_API void       XPLMCheckMenuItemState(
						 XPLMMenuID           inMenu,
						 int                  index,
						 XPLMMenuCheck *      outCheck);


XPLM_API void       XPLMClearAllMenuItems(
						 XPLMMenuID           inMenuID);


XPLM_API void       XPLMSetMenuItemName(
						 XPLMMenuID           inMenu,
						 int                  inIndex,
						 const char *         inItemName,
						 int                  inDeprecatedAndIgnored);





#endif //XPLMMENUS_H
