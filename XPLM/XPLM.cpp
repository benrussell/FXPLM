/*
 * FXPLM - A re-impl of the X-Plane XPLM layer.
 * Copyright (C) 2024-2026 Ben Russell - br@x-plugins.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <https://www.gnu.org/licenses/>.
 */

//
// Created by Ben on 22/10/2025.
//

#include "XPLM.h"

#include <filesystem>
#include <iostream>
#include "glue_Menus.h"

Plugin* global_target_plugin;

#include <algorithm>

#if 1 // stb_tt
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>
#endif


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>



#if 1
#include "DataRefsTxtParse.h"


void load_datarefs() {
	dref_factory::init(); //dref pool

	std::cout << "FXPLM/ load_datarefs()\n";

	const std::string rel_fname = "Resources/plugins/DataRefs_XWB.txt";

#if 1 //FIXME: FXPLM: port cmd loaders
	//auto cmds = CommandsTxtParse("Commands.txt");

	if( ! std::filesystem::exists(rel_fname)){
		namespace fs = std::filesystem;
		const std::string cwd = fs::current_path();
		std::cout << "FXPLM/ working folder: [" << cwd << "]\n";
		std::cout << "FXPLM/ load_datarefs: 404: [" << rel_fname << "] ********************\n";
	}

	auto drefs = DataRefsTxtParse(rel_fname.c_str());

	for ( const auto dr: drefs.m_recs ) {
		dref_factory::saveDref( dr.name, dr.type, false );
	}

	std::cout << "FXPLM/ search penalty: " << dref_factory::search_ctr << "\n";
#endif

}
#endif


void spawn_host_app_plugin() {
	std::cout<<"FXPLM/ spawn host_app plugin 0.\n";

	if (XPHost::m_vecPlugins.size() >0 ) {
		throw std::runtime_error("host_app plugin already exists");
	}

	const auto fname = "XPL_Workbench";
	Plugin *p = new Plugin(fname);
	XPHost::m_vecPlugins.push_back(p);
	p->takeContext();

}






//// Data needed by the drawing function
//static GLuint g_font_atlas_texture;
//static stbtt_bakedchar g_cdata[CHAR_COUNT];
//static unsigned char* g_font_data = nullptr;


void init_stbtt()
{

	std::cout << "******* init_stbtt() ********\n";

	// --- 1. Load Font File ---
	std::ifstream file(FONT_FILE, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "Error: Cannot open font file: " << FONT_FILE << std::endl;
		return;
	}
	size_t file_size = file.tellg();
	file.seekg(0);
	g_font_data = new unsigned char[file_size];
	file.read(reinterpret_cast<char*>(g_font_data), file_size);
	file.close();

	// --- 2. Create Font Atlas Bitmap ---
	unsigned char* bitmap = new unsigned char[ATLAS_SIZE * ATLAS_SIZE];

	// Use STBTT_point_size() for pt conversion (96 DPI assumption baked in)
	stbtt_BakeFontBitmap(
			g_font_data,
			0,
			FONT_HEIGHT_PX, // Font size in pixels (15 pt * 96/72 DPI = 20 px)
			bitmap,
			ATLAS_SIZE,
			ATLAS_SIZE,
			FIRST_CHAR,
			CHAR_COUNT,
			g_cdata
	);

	std::cout << "gc_data:" << (void*)&g_cdata << "\n";
	for(int x=0; x<CHAR_COUNT; x++){
		auto cdata = g_cdata[x];
//		std::cout << " char_target:" << char_target;
//		std::cout << " / gi:" << glyph_index;
		std::cout << "x:" << x;
		std::cout << " / adv:" << cdata.xadvance;
		std::cout << " / adv:" << cdata.xoff;
		std::cout << " / x0:" << cdata.x0;
		std::cout << " / y0:" << cdata.y0;
		std::cout << " / x1:" << cdata.x1;
		std::cout << " / y1:" << cdata.y1;
		std::cout << "\n";

	}



	// --- 3. Upload to OpenGL Texture ---
	glGenTextures(1, &g_font_atlas_texture);
	glBindTexture(GL_TEXTURE_2D, g_font_atlas_texture);

#if 0 // white bitmap data
	size_t total_bytes = (size_t)ATLAS_SIZE * ATLAS_SIZE * 4;
	unsigned char *bitmap2 = (unsigned char *)malloc(total_bytes);
	memset(bitmap, 0xFF, total_bytes);
	//memset( bitmap, 0xFF, ATLAS_SIZE*ATLAS_SIZE * 4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ATLAS_SIZE, ATLAS_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap2);
	free( bitmap2 );
#endif

#if 1
	// Crucial for single-channel textures
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// GL_ALPHA or GL_LUMINANCE is needed for GL 2.1 single-channel texture format
	// GL_ALPHA is often safer for blending in older GL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, ATLAS_SIZE, ATLAS_SIZE, 0,
				 GL_ALPHA, GL_UNSIGNED_BYTE, bitmap);
#endif

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// --- 4. Cleanup ---
	delete[] bitmap;
	// NOTE: g_font_data is kept until app exit if you need to call stbtt_Free...
	// or if you want to use other stb_truetype functions later.

	std::cout << "stb_truetype font atlas initialized." << std::endl;
	std::cout << " font atlas texture: " << g_font_atlas_texture << "\n";
}



XPLM_API void FXPLM_Init( char* name, char* sig, char* desc ) {

	std::cout<<"FXPLM_Init: 26.01.04.2108"<<std::endl;
	// std::cout<< name <<std::endl;
	// std::cout<< sig <<std::endl;
	// std::cout<< desc <<std::endl;

	// namespace fs = std::filesystem;
	// const std::string cwd = fs::current_path();
	// std::cout << "FXPLM/ working folder: [" << cwd << "]\n";

	#if APL
	{
		namespace fs = std::filesystem;
		fs::current_path("../../..");

		const std::string cwd = fs::current_path();
		std::cout << "FXPLM/ working folder: [" << cwd << "]\n";

		fxplm_global_sys_folder = cwd;
	}
	#else
	{
		namespace fs = std::filesystem;
		//fs::current_path("../../..");

		const std::string cwd = fs::current_path();
		std::cout << "FXPLM/ working folder: [" << cwd << "]\n";

		fxplm_global_sys_folder = cwd;
	}
	#endif

	XPHost::m_ptrTimer = new Timer();
	XPHost::m_ptrTimer->start();



#if 1
	// No OpenGL code can be used in here.
	// The calling code in XWB destroys a window shortly after that seems to reset a bunch of GL state.

	std::cout<<"FXPLM/ glewInit();"<<std::endl;
	glewInit();
	glewExperimental = GL_TRUE; // Ensure modern OpenGL functions are loaded
	if (glewInit() != GLEW_OK) {
		std::cerr << "FXPLM/ Failed to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
#else
	std::cout<<"FXPLM: *** NO GLEW INIT CALL ***\n";
#endif


	spawn_host_app_plugin();

	// dref_factory::init();
	load_datarefs();


	std::cout << "  mnu quick init\n";
	glue_Menus::m_AircraftMenu.m_sLabel = "Aircraft";
	glue_Menus::m_PluginsMenu.m_sLabel = "Plugins";


	std::cout<<"FXPLM_Init: completed."<<std::endl;

}



XPLM_API void FXPLM_SetContext( void* g_plugin ) {

	std::cout<<"XPLM_SetContext: "<<std::endl;

	std::cout<< std::hex << g_plugin <<std::endl;
}



XPLM_API int FXPLM_LoadPlugin( const char* fname ) {

	std::cerr<<"----------------------------\n";
	std::cerr<<"FXPLM_LoadPlugin:([" << fname << "])\n";
	//std::cerr<<"  cwd: [" << std::filesystem::current_path() << "]\n";

	int ret = 0;

	try {
		Plugin *p = new Plugin(fname);

		// This must happen so that plugins can query their own data during XPluginStart
		XPHost::m_vecPlugins.push_back(p);

		{
			//buffer size is defined by docs for XPLMGetPluginInfo(..)
			constexpr int buff_size = 256;
			char name[buff_size];
			char sig[buff_size];
			char desc[buff_size];

			snprintf( name, buff_size, "FXPLM Default Name" );
			snprintf( sig, buff_size, "FXPLM.default.signature" );
			snprintf( desc, buff_size, "FXPLM Default Description" );

			ret = p->call_start( name, sig, desc );
		}


#define FXPLM_SEARCH_FOR_PLUGIN_BY_SIG 0
#if FXPLM_SEARCH_FOR_PLUGIN_BY_SIG

		// this doesnt do anything to address macOS double load of xLua binary
		// leading to a CTD. Something to do with static vars not being init on the xLua side for the second load.

		bool accept_plugin = true;
		std::cout << "  searching for duplicate signature: " << p->m_pluginSig << "\n";

		for( const auto &existing_p: XPHost::m_vecPlugins ){
			if( existing_p->m_pluginSig == p->m_pluginSig ){
				//we have a duplicate!
				accept_plugin = false;
				std::cout << "  duplicate plugin sig found for existing plugin: " << existing_p->m_plugin_id << "\n";
			}
		}


		if( accept_plugin ){
			//XPHost::m_vecPlugins.push_back(p);
			printf("\nFXPLM_LoadPlugin: Success: [%s] Plugin* addr: %p\n", fname, p);

		}else{
			// FIXME: plugin_id_ctr will be out of sync now
			printf("\nFXPLM_LoadPlugin: Fail: [%s] Plugin* addr: %p was rejected.\n", fname, p);
			//delete p;

//			p->m_plugin_is_enabled = false;

		}
#endif
#undef FXPLM_SEARCH_FOR_PLUGIN_BY_SIG

	}catch (const std::runtime_error& e) {

		std::cerr << "FXPLM/ load_plugin/ runtime_error: " << e.what() << std::endl;
		XPHost::m_load_plugin_error_msg = e.what();

	}

	return ret;

}

XPLM_API const char* FXPLM_LoadPlugin_GetErr() {
	return XPHost::m_load_plugin_error_msg.c_str();
}


XPLM_API void       FXPLM_UnloadPlugins(void) {
	std::cout<<"FXPLM/ FXPLM_UnloadPlugins(): Unloading..\n";

	// Plugin [0] is "host app" and we keep it alive and restore it after we clear the vec.

	Plugin* ptr_keep_host;

	size_t ctr = 0;
	for( const auto p: XPHost::m_vecPlugins ){
		if (ctr>0) {
			//datarefs track their consumers by Plugin*
			dref_factory::cleanup(p);
			delete p;
		}else {
			ptr_keep_host = p;
		}
		ctr++;
	}
	XPHost::m_vecPlugins.clear();
	XPHost::m_vecPlugins.push_back(ptr_keep_host);
	Plugin::plugin_id_ctr = 1;


	std::cout<<"FXPLM/ FXPLM_UnloadPlugins(): Done.\n";

}









XPLM_API int FXPLM_RunFLCBS() {
	for ( auto xpl: XPHost::m_vecPlugins ) {
		xpl->run_flcbs();
	}

	return XPHost::m_vecPlugins.size();
}





XPLM_API int FXPLM_DrawWindows() {

	for( auto p: XPHost::m_vecPlugins ){
		if ( p->m_plugin_is_enabled ) {
			p->takeContext();
			for( const auto& win_h: p->m_vecWindowHandles ){
				if( win_h->m_params->visible ){
					win_h->m_bakeStart = XPHost::m_ptrTimer->getElapsedTimeInMilliSec();
					glDisable(GL_CULL_FACE);
					win_h->m_params->drawWindowFunc( win_h, win_h->m_params->refcon );
					glEnable(GL_CULL_FACE);
					win_h->m_bakeStop = XPHost::m_ptrTimer->getElapsedTimeInMilliSec();
				}
			}//loop windows
			p->releaseContext();
		} //enabled?
	} //loop all plugins

	return 1;
}



XPLM_API int FXPLM_HandleWindowClick( float x, float y ){

	FXPLM_DebugLogHeader("FXPLM_HandleWindowClick");
	std::cout << " x,y:" << x << "," << y << "\n";
	std::cout << "collate win_h\n";


	auto lam_boxTest = []( float x, float y,
			int left, int top, int right, int bottom ) -> bool {

		int score=0;
		if( x > (float)left && x < (float)right ){
//			std::cout << "    x hit\n";
			++score;
		}
		if( y > (float)bottom && y < (float)top ){
//			std::cout << "    y hit\n";
			++score;
		}

		if( score == 2 ){
			return true;
		}
		return false;
	};


	// [x] iterate through plugins and win handles.
	//     collect all win handles into vector
	// [x] z-index sort win handles
	// [x] iterate new sorted vec of handles and run click tests

	std::vector<glue_WindowEx*> vecWindowHandles;
	std::map<glue_WindowEx*, Plugin*> mapPluginForWindow;

	for( const auto p: XPHost::m_vecPlugins ){
		if ( p->m_plugin_is_enabled ) {
			for( const auto win_h: p->m_vecWindowHandles ){

				//don't route clicks to invisible windows.
				if( ! win_h->m_params->visible ){
					//std::cout << "    not visible. skip.\n";
					continue;
				}

				const bool click_hit = lam_boxTest( x,y,
											  win_h->m_params->left,
											  win_h->m_params->top,
											  win_h->m_params->right,
											  win_h->m_params->bottom
								  );
				//std::cout << "..click_hit:" << click_hit << "\n";

				if( click_hit ){
					//std::cout << "...win_h:" << (void*)win_h << "\n";
					//std::cout << "...title:" << win_h->m_sWindowTitle << "\n";
					//std::cout << "...z_index:" << win_h->z_index << "\n";

					//store the window for z_index sorting
					vecWindowHandles.push_back( win_h );
					//store a map from the win_h to the plugin that owns it for ctx switching later
					mapPluginForWindow[win_h] = p;
				}

			}//loop windows

		} //enabled?
	} //loop all plugins



	//std::cout << " > sort vecWindowHandles..\n";
	std::sort(vecWindowHandles.begin(), vecWindowHandles.end(), [](const glue_WindowEx* a, const glue_WindowEx* b) {
		#if 1
		//ascending order
		return a->z_index < b->z_index;
		#else
		// descending sort for debug
		return a->z_index > b->z_index;
		#endif
	});



	{ //var name isolation
		Plugin *p;
		std::cout << " iter sorted vecWindowHandles..\n";
		for (const auto win_h: vecWindowHandles) {
			p = mapPluginForWindow[win_h];
			p->takeContext();

			//FIXME: add click time logging
			// win_h->m_bakeStart = XPHost::m_ptrTimer->getElapsedTimeInMilliSec();

			if( win_h->m_params->handleMouseClickFunc ){
				int click_ret = win_h->m_params->handleMouseClickFunc(
						win_h,
						(int)x, (int)y,
						xplm_MouseDown,
						win_h->m_params->refcon
				);

				std::cout << "  win_h:" << (void*)win_h << "\n";
				std::cout << "  title:" << win_h->m_sWindowTitle << "\n";
				std::cout << "  z_index:" << win_h->z_index << "\n";
				std::cout << "    click_ret:" << click_ret;

#define FXPLM_CLICK_MOUSE_UP 0
#if FXPLM_CLICK_MOUSE_UP
				if( click_ret ){
//						int click_ret2 = win_h->m_params->handleMouseClickFunc(
//								win_h,
//								(int)x, (int)y,
//								xplm_MouseUp,
//								win_h->m_params->refcon
//						);
						//std::cout << " click_ret2:" << click_ret2;

						break; //early exit, we ate a click
					}
#endif

				std::cout << "\n";

				if( click_ret ){
					std::cout << "..click consumed; handler ret, loop break.\n";
					p->releaseContext(); //FIXME: code smell because early ret
					return 1; //FIXME: does the host app care about retval?
				}

			} //check for mouse handler


			p->releaseContext();
		}//loop win_h vec
	}//var name iso



	return 0;
}


XPLM_API int FXPLM_DrawCBS() {

	// Render all avionics device FBO surfaces.
	for( auto p: XPHost::m_vecPlugins ){
		if ( p->m_plugin_is_enabled ) {

			for( auto dev: p->m_vecAvionicsHost ){
				// This is an FBO bake loop.
				// This is NOT imgui calling code.
				dev->bake();
			}

			for( auto dev: p->m_vecDrawCallbackHost ){
				// This is an FBO bake loop.
				// This is NOT imgui calling code.
				dev->bake();
			}

		}

	}

	return 1;
}



XPLM_API void* FXPLM_PluginInstPtr( int plugin_id ) {
	//FIXME: shouldnt do this. but yknow. whatever.
	auto p = XPHost::m_vecPlugins[plugin_id];
	return p;
}



XPLM_API void* FXPLM_DrefPoolPtr() {
	return &XPHost::m_dref_pool;
}





XPLM_API xp_dref* FXPLM_DrefCreate( const char* dref_name ) {
	FXPLM_DebugLogHeader("FXPLM_DrefCreate");
	std::cout << " dref_name:[" << dref_name <<"]\n";
	return dref_factory::saveDref( dref_name, "FXPLM_DrefCreate", false );
}






// README: DO NOT ANNOTATE WITH XPLM_API or other decorators or the link will break.
void __XPLMValidateThreadSafety(const char* functionName,
								const char* fileName,
								int line) {

	// This is used by X-Plane to ensure that the caller is running in the main thread.
	// TODO: Long term: Add support for main thread detection so we can validate plugin behaviours.


	#define FXPLM_REPORT_VALIDATE_THREAD_SAFETY_CALLERS 0
#if FXPLM_REPORT_VALIDATE_THREAD_SAFETY_CALLERS
	printf("FXPLM/ __XPLMValidateThreadSafety: func:[%s] file:[%s]  line:%i\n",
		functionName, fileName, line
		);
#endif

}





void FXPLM_DebugLogHeader( const char* msg ){

	if( global_target_plugin == nullptr ){
		std::cout << "FXPLM/ [XWB.app] " << msg << ":";
		return;
	}

	std::cout << "FXPLM/ ["<< global_target_plugin->getSafeSig()
			  << "] " << msg << ":";
}



void FXPLM_TestGL() {

	FXPLM_DebugLogHeader("FXPLM_TestGL");
	std::cout << "\n";

//	{
//		GLuint tex_foo;
//		glGenTextures(1, &tex_foo);
//		std::cout << "  tex_foo:" << tex_foo << "\n";
//
//		gz::gfx::tex::load( "/Users/br/Downloads/ferris.png", tex_foo );
//
//	}


	init_stbtt();


}
