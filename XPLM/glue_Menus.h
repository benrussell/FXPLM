//
// Created by Ben on 29/12/2025.
//

#ifndef XPLM_GLUE_MENUS_H
#define XPLM_GLUE_MENUS_H

// Acf Menu
// - folder
// -- item

// Plugins Menu
// - folder
// -- item

#include <string>
#include <vector>
#include <map>

#include "XPLMMenus.h"


// ptr to inst of these will be ret for XPLMMenuID usages
class glue_MenuNode{
public:
	std::string m_sLabel{"menu node"};
	bool m_bChecked=false;
	bool m_bEnabled=true;

	XPLMMenuHandler_f m_fn_click_handler=nullptr;
	//some menus map directly to a command.

	void* m_refcon=nullptr;

	int m_parent_index=0;

	//this is used to easily determine the click handler fn
	XPLMMenuID m_parentMenuNode=nullptr;

	std::vector<void*> m_vecSubNodes;

	//FIXME: when creating we should store the global_target_plugin ptr in this var
	// we can then use this member var to
	// take context before we call into the click handler.
	// this will give us correct blaming for FXPLM calls from the click handler.
	void* m_parent_plugin=nullptr;

};


class glue_Menus {
public:
	inline static glue_MenuNode m_AircraftMenu{};
	inline static glue_MenuNode m_PluginsMenu{};
};


#endif //XPLM_GLUE_MENUS_H
