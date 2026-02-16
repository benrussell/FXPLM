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
//  xp_dref.cpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#include "xp_dref.hpp"








#include <iostream>
#include <string>
#include <vector>
#include <regex>

struct ParsedType {
	std::string baseType;
	std::vector<int> dimensions;
};

ParsedType parseString(const std::string& input) {
	ParsedType result;

	// Find the first bracket to isolate the base type
	size_t firstBracket = input.find('[');

	if (firstBracket == std::string::npos) {
		result.baseType = input;
		return result;
	}

	result.baseType = input.substr(0, firstBracket);

	// Extract numbers between []
	std::regex re("\\[(\\d+)\\]");
	auto words_begin = std::sregex_iterator(input.begin() + firstBracket, input.end(), re);
	auto words_end = std::sregex_iterator();

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		result.dimensions.push_back(std::stoi(match[1].str()));
	}

	return result;
}









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

	//std::cerr << "FXPLM/dref_factory.findDref(" << name << "): 404\n";
	return nullptr;

}; //findDref



xp_dref* dref_factory::saveDref( const std::string& name, const std::string type, bool try_find ){
	//std::cout<<"dref_factory::saveDref: " << name << "\n";


	auto type_info = parseString( type );


	size_t element_bytes = 0;
	if( type_info.baseType == "float" ){
		element_bytes = sizeof( float );
	}else if( type_info.baseType == "int" ) {
		element_bytes = sizeof( int );
	}else if( type_info.baseType == "double" ) {
		element_bytes = sizeof( double );
	}else if( type_info.baseType == "byte" ) {
		element_bytes = sizeof( char );
	}else{
		std::cout << "******* UNKNOWN DATA TYPE:" << type_info.baseType << "\n";
	}


	if( type_info.dimensions.size() > 0 ){
		std::cout << " type: " << type_info.baseType;

		std::cout << " arr_dims: " << type_info.dimensions.size();
		size_t elements_needed = type_info.dimensions[0];
		std::cout << " d:" <<  type_info.dimensions[0];
		if( type_info.dimensions.size() > 1 ){
			for( size_t x=1; x < type_info.dimensions.size(); ++x ){
				elements_needed = elements_needed * type_info.dimensions[x];
				std::cout << " d:" <<  type_info.dimensions[x];
			}
		}
		std::cout << " elements:" << elements_needed;

		size_t bytes_needed = elements_needed * element_bytes;
		std::cout << " bytes_needed:" << bytes_needed;

		std::cout << "\n";

	} //if array



	xp_dref* dr;

	//this is optional so we can load from DataRefs.txt without error logs
	if ( try_find ) {
		dr = findDref( name );
		if ( dr ) {
			std::cout << "  saveDref: dref found existing [" << name << "]\n";
			return dr;
		}
	}

	//FIXME: use our parsed type data above to affect the dref created here
	// - tag the new dref as an array type if needed
	// - call for malloc so we have some raw backing memory for the required array storage
	// - add appropriate wrapper fns's and wire them to the SetDatavX and GetDatavX functions of the SDK
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





