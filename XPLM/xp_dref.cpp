//
//  xp_dref.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "xp_dref.hpp"


xp_dref::xp_dref( std::string name, xp_dref_type type, std::string typeName ){
//        std::cout << "xp_dref() constructor ********\n";
	drefName = std::move(name);
	drefType = type;

	drefTypeName = typeName;

	m_valDouble = 0.0;
	m_valFloat = 0.0f;
	m_valInt = 0;
}


std::string xp_dref::typeName() const{
	switch ( drefType ) {

		case dref_ModelViewMatrix:
			return "model";

		case dref_ProjectionMatrix:
			return "projection";

		case dref_Viewport:
			return "viewport";

		case dref_VREnabled:
			return "vr_enabled";

		case dref_Generic:
			return "generic";

		default:
			return "??";
	}
}



float xp_dref::getFloat(){
//        std::cout << "xp_dref->read(): " << drefName << "\n";
	return m_valFloat;
};

void xp_dref::setFloat( float new_val ){
	m_valFloat = new_val;
}


int xp_dref::getInt(){
//        std::cout << "xp_dref->read(): " << drefName << "\n";
	return m_valInt;
};

void xp_dref::setInt( int new_val ){
	m_valInt = new_val;
}











xp_dref* dref_factory::findDref( const std::string& name ){
	// std::cout<<"dref_factory::findDref: " << name << "\n";

	for( auto dr: XPHost::m_dref_pool ){
		++search_ctr;
		if( dr->drefName == name ){
//				std::cout << "  findDref: dref found ["<< name <<"]\n";
			return dr;
		}
	}

#define FXPLM_AUTO_CREATE_DREF_FOR_FIND_CALL 1
#if FXPLM_AUTO_CREATE_DREF_FOR_FIND_CALL
	//FIXME: this seems to fix the malloc-errors on exit that weve been seeing since the FXPLM split
	std::cout << "  findDref: dref create ["<< name <<"]\n";
	auto new_dr = saveDref( name, "auto_create", false );
	return new_dr;
#else
	std::cerr << "FXPLM/dref_factory.findDref(" << name << "): 404\n";
		return nullptr;
#endif
#undef FXPLM_AUTO_CREATE_DREF_FOR_FIND_CALL


}; //findDref



xp_dref* dref_factory::saveDref( const std::string& name, const std::string type, bool try_find ){
	//std::cout<<"dref_factory::saveDref: " << name << "\n";

	xp_dref* dr;

	//this is optional so we can load from DataRefs.txt without error logs
	if ( try_find ) {
		dr = findDref( name );
		if ( dr ) {
			std::cout << "  saveDref: dref found existing [" << name << "]\n";
			return dr;
		}
	}

	dr = new xp_dref( name, xp_dref_type::dref_Generic, type );
	XPHost::m_dref_pool.push_back(dr);

	//std::cout << "  dref created: ret new.\n";
	return dr;

}; //saveDref



void dref_factory::init(){

	if ( ! XPHost::m_dref_pool.empty() ) {
		throw std::runtime_error( "FXPLM/dref_factory::init() - pool is filled." );
	}


	std::cout << "FXPLM/ dref_factory::init()\n";

	//		auto dr_frp = new xp_dref_frp( "sim/time/framerate_period", xp_dref_type::dref_FrameRatePeriod, "float" );
	//		dref_pool.push_back(dr_frp);

	// ReSharper disable once CppDFAMemoryLeak
	auto dr_mvm = new xp_dref( "sim/graphics/view/modelview_matrix", xp_dref_type::dref_ModelViewMatrix, "float[4?]" );
	XPHost::m_dref_pool.push_back(dr_mvm);

	// ReSharper disable once CppDFAMemoryLeak
	auto dr_pm = new xp_dref( "sim/graphics/view/projection_matrix", xp_dref_type::dref_ProjectionMatrix, "float[4?]" );
	XPHost::m_dref_pool.push_back(dr_pm);

	// ReSharper disable once CppDFAMemoryLeak
	auto dr_vp = new xp_dref( "sim/graphics/view/viewport", xp_dref_type::dref_Viewport, "float" );
	XPHost::m_dref_pool.push_back(dr_vp);

	// ReSharper disable once CppDFAMemoryLeak
	auto dr_vr = new xp_dref( "sim/graphics/VR/enabled", xp_dref_type::dref_VREnabled, "int" );
	XPHost::m_dref_pool.push_back(dr_vr);

	//FIXME: need to try and load the DataRefs.txt file here.
	// drefs file is loaded elsewhere...

};



void dref_factory::cleanup( void* ptr_find_and_remove ) {
	std::cout << "FXPLM/ dref_factory::cleanup(): "<< ptr_find_and_remove <<"\n";

	std::vector<Plugin*> vec_plugin_ptr_keepers;

	for ( const auto ptr: XPHost::m_dref_pool ) {
		if ( ! ptr->m_vecPluginConsumers.empty() ) {
			//std::cout <<"  Looking at: ["<<  ptr->drefName <<"]\n";

			vec_plugin_ptr_keepers.clear();
			for ( const auto dr_consumer: ptr->m_vecPluginConsumers ) {
				if ( dr_consumer == ptr_find_and_remove ) {
					//std::cout <<"  - zombie found\n";
				}else {
					vec_plugin_ptr_keepers.push_back(dr_consumer);
				}
			} //consumer loop

			ptr->m_vecPluginConsumers.swap(vec_plugin_ptr_keepers);

		} //consumer size check
	} //loop drefs
	std::cout << "FXPLM/ dref_factory::cleanup() - finished.\n";
}




void dref_factory::delete_all() {
	for ( const auto ptr: XPHost::m_dref_pool ) {
		delete ptr;
	}
}





