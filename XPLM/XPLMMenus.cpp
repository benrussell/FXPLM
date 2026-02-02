//
// Created by Ben on 15/11/2025.
//

#include "XPLMMenus.h"

#include <iostream>

#include "XPLM.h"

#include "glue_Menus.h"



XPLMMenuID XPLMFindPluginsMenu() {
	FXPLM_DebugLogHeader("XPLMFindPluginsMenu");

	void* ret = &glue_Menus::m_PluginsMenu;
	std::cout << " / ret:"<< ret <<"\n";

	return ret;

}



XPLMMenuID XPLMCreateMenu(
							 const char *         inName,
							 XPLMMenuID           inParentMenu,
							 int                  inParentItem,
							 XPLMMenuHandler_f    inHandler,
							 void *               inMenuRef) {

	FXPLM_DebugLogHeader("XPLMCreateMenu");
	std::cout << " name:["<< inName <<"]";
	std::cout << " parent_id:"<< inParentMenu;
	std::cout << " parent_item:"<< (void*)(size_t)inParentItem;
	std::cout << " handler_f:"<< (void*)inHandler;
	std::cout << " menu_ref:"<< inMenuRef;

	auto target_mnu = (glue_MenuNode*)inParentMenu;

	auto new_mnu = new glue_MenuNode();
	new_mnu->m_sLabel = inName;
	new_mnu->m_parent_index = inParentItem;
	new_mnu->m_fn_click_handler = inHandler;
	new_mnu->m_refcon = inMenuRef;

	new_mnu->m_parent_plugin = global_target_plugin;

	target_mnu->m_vecSubNodes.push_back(new_mnu);

	std::cout << " / ret:"<< (void*)new_mnu <<"\n";

	return (XPLMMenuID)new_mnu;
}




int XPLMAppendMenuItem(
						 XPLMMenuID           inMenu,
						 const char *         inItemName,
						 void *               inItemRef,
						 int                  inDeprecatedAndIgnored){

	FXPLM_DebugLogHeader("XPLMAppendMenuItem");
	std::cout << " id:"<< inMenu <<"";
	std::cout << " inItemName:["<< inItemName <<"]";
	std::cout << " inItemRef:"<< inItemRef <<"";
//	std::cout << " deprecated:"<< inDeprecatedAndIgnored;

	auto target_mnu = (glue_MenuNode*)inMenu;

	auto new_mnu = new glue_MenuNode();
	new_mnu->m_sLabel = inItemName;
	new_mnu->m_parent_index = 0; //FIXME: parent index??
	new_mnu->m_fn_click_handler = nullptr; //FIXME: we can have a void* to a parent item that has the click handler?
	new_mnu->m_refcon = inItemRef;

	new_mnu->m_parentMenuNode = inMenu;

	target_mnu->m_vecSubNodes.push_back(new_mnu);

	int ret = (int)(uintptr_t)new_mnu;
	std::cout << " / ret:"<< (void*)(int64_t)ret <<"\n";

//	std::cout << " * inMenu label:"<< target_mnu->m_sLabel <<"\n";

	return ret;

}



void       XPLMDestroyMenu(
					XPLMMenuID           inMenuID){

	FXPLM_DebugLogHeader("NOP/ XPLMDestroyMenu");
	std::cout << "\n";

}



XPLM_API int        XPLMAppendMenuItemWithCommand(
						 XPLMMenuID           inMenu,
						 const char *         inItemName,
						 XPLMCommandRef       inCommandToExecute) {

	FXPLM_DebugLogHeader("DEV/ XPLMAppendMenuItemWithCommand");
	std::cout << " name:" << inItemName;
	std::cout << " menu:" << inMenu;
	std::cout << " cmd:" << inCommandToExecute;

	auto target_mnu = (glue_MenuNode*)inMenu;

	auto new_mnu = new glue_MenuNode();
	new_mnu->m_sLabel = inItemName;
	new_mnu->m_parent_index = 0; //FIXME: parent index??
	new_mnu->m_fn_click_handler = nullptr; //FIXME: we can have a void* to a parent item that has the click handler?
	//new_mnu->m_refcon = inItemRef; //FIXME: replace with cmd*

	new_mnu->m_parentMenuNode = inMenu;

	target_mnu->m_vecSubNodes.push_back(new_mnu);

	int ret = (int)(uintptr_t)new_mnu;
	std::cout << " / ret:"<< (void*)(int64_t)ret <<"\n";

//	std::cout << " * inMenu label:"<< target_mnu->m_sLabel <<"\n";

	return ret;

}



XPLM_API void       XPLMAppendMenuSeparator(
						 XPLMMenuID           inMenu) {

	FXPLM_DebugLogHeader("NOP/ XPLMAppendMenuSeparator");
	std::cout << " menu:" << inMenu;
	std::cout << "\n";

}


XPLM_API void       XPLMCheckMenuItem(
						 XPLMMenuID           inMenu,
						 int                  index,
						 XPLMMenuCheck        inCheck) {
	FXPLM_DebugLogHeader("NOP/ XPLMCheckMenuItem");
	std::cout << " id:" << inMenu;
	std::cout << " index:" << (void*)(size_t)index;
	std::cout << " mnu_check:" << inCheck;
	std::cout << "\n";

}


XPLM_API void       XPLMCheckMenuItemState(
						 XPLMMenuID           inMenu,
						 int                  index,
						 XPLMMenuCheck *      outCheck) {
	FXPLM_DebugLogHeader("NOP/ XPLMCheckMenuItemState");
	std::cout << "\n";
}


XPLM_API void       XPLMClearAllMenuItems(
						 XPLMMenuID           inMenuID) {
	FXPLM_DebugLogHeader("NOP/ XPLMClearAllMenuItems");
	std::cout << "\n";
}


XPLM_API void       XPLMEnableMenuItem(
						 XPLMMenuID           inMenu,
						 int                  index,
						 int                  enabled) {

	//FIXME: SASL3 spams this
	#if 0
	FXPLM_DebugLogHeader("NOP/ XPLMEnableMenuItem");
	std::cout << " inMenu:" << inMenu;
	std::cout << " index:" << index;
	std::cout << " hex(index):" << (void*)(int64_t)index;

	std::cout << " enable:" << enabled;
	std::cout << "\n";
	#endif

}



XPLM_API XPLMMenuID XPLMFindAircraftMenu(void) {
	FXPLM_DebugLogHeader("XPLMFindAircraftMenu");

	void* ret = &glue_Menus::m_AircraftMenu;
	std::cout << " / ret:"<< ret <<"\n";

	return ret;

}


XPLM_API void       XPLMRemoveMenuItem(
						 XPLMMenuID           inMenu,
						 int                  inIndex) {
	FXPLM_DebugLogHeader("NOP/ XPLMRemoveMenuItem");
	std::cout << "\n";
}


XPLM_API void       XPLMSetMenuItemName(
						 XPLMMenuID           inMenu,
						 int                  inIndex,
						 const char *         inItemName,
						 int                  inDeprecatedAndIgnored) {
	FXPLM_DebugLogHeader("XPLMSetMenuItemName");
	std::cout << " inMenu:" << inMenu;
	std::cout << " inIndex:" << (void*)(int64_t)inIndex;
	std::cout << " inItemName:[" << inItemName << "]";
	std::cout << " \n";

	auto mnu_target = (glue_MenuNode*)inMenu;
//	std::cout << " mnu_target:[" << mnu_target->m_sLabel << "]\n";

//	std::cout << " searching for match index: want:" << (void*)inIndex << "\n";
	for( auto vp_sub_item: mnu_target->m_vecSubNodes ){
		auto sub_item = (glue_MenuNode*)vp_sub_item;

		int comp = (int)(intptr_t)sub_item;
//		std::cout << "  " << (void*)comp << "\n";

		if( comp == inIndex ){
//			std::cout << "  - match:[" << sub_item->m_sLabel << "]\n";
			sub_item->m_sLabel = inItemName;
			break;
		}

	}//loop all sub menu items

}



