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








xp_dref::~xp_dref() {
	free( m_blob );
}


//xp_dref::xp_dref( std::string name, xp_dref_type type, std::string typeName ){
xp_dref::xp_dref( xp_drefs_params params ){

	drefName = std::move(params.name);
	drefType = params.type;

	drefTypeName = params.typeName;
	drefTypeName_Raw = params.typeName_Raw;

	m_elements = params.elements_needed;
	m_blob_size = params.bytes_needed;

	//m_blob = malloc( m_blob_size );
	m_blob = calloc( 1, m_blob_size );

	// - call for malloc so we have some raw backing memory for the required array storage
	if ( !m_blob) {

		/* //extra debug info
		std::cout << "xp_dref() ctor fail ***:";
		std::cout << " elements_needed:" << params.elements_needed;
		std::cout << " bytes_needed:" << params.bytes_needed;
		std::cout << " name:" << drefName;
		std::cout << "\n";
		// */

		throw std::runtime_error("xp_dref ctor, could not alloc blob.");
	}

	//FIXME: - add appropriate wrapper fns's and wire them to the SetDatavX and GetDatavX functions of the SDK

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



xp_dref* dref_factory::saveDref( const std::string& name, const std::string raw_type, bool try_find ){
	//std::cout<<"dref_factory::saveDref: " << name << "\n";

	//this is optional so we can load from DataRefs.txt without error logs
	if ( try_find ) {
		if ( auto dr_find = findDref( name ) ) {
			std::cout << "  saveDref: dref found existing [" << name << "]\n";
			return dr_find;
		}
	}





	auto type_info = parseString( raw_type );

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

	size_t bytes_needed = 0;
	size_t elements_needed = 0;
	if( type_info.dimensions.size() > 0 ){
		std::cout << " type: " << type_info.baseType;

		std::cout << " elements: " << type_info.dimensions.size();
		elements_needed = type_info.dimensions[0];
		std::cout << " d:" <<  type_info.dimensions[0];
		if( type_info.dimensions.size() > 1 ){
			for( size_t x=1; x < type_info.dimensions.size(); ++x ){
				elements_needed = elements_needed * type_info.dimensions[x];
				std::cout << " d:" <<  type_info.dimensions[x];
			}
		}
		std::cout << "\n";

	} //if array


	std::cout << " elements:" << elements_needed;
	bytes_needed = elements_needed * element_bytes;
	std::cout << " bytes_needed:" << bytes_needed;
	std::cout << "\n";


	xp_drefs_params create_params;
	create_params.name = name;
	create_params.type = xp_dref_type::dref_Generic;
	create_params.typeName_Raw = raw_type;

	create_params.typeName = type_info.baseType;
	create_params.elements_needed = elements_needed; //0 elements = not array
	create_params.bytes_needed = bytes_needed;

	auto dr = new xp_dref( create_params );
	XPHost::m_dref_pool.push_back(dr);

	//std::cout << "  dref created: ret new.\n";
	return dr;

}; //saveDref



void dref_factory::init(){

	if ( ! XPHost::m_dref_pool.empty() ) {
		throw std::runtime_error( "FXPLM/dref_factory::init() - pool is filled." );
	}

	std::cout << "FXPLM/ dref_factory::init()\n";

	{
		xp_drefs_params create_params;
		create_params.name = "sim/graphics/view/modelview_matrix";
		create_params.type = xp_dref_type::dref_ModelViewMatrix;
		create_params.typeName = "float[4]";
		// ReSharper disable once CppDFAMemoryLeak
		auto dr = new xp_dref(create_params);
		XPHost::m_dref_pool.push_back(dr);
	}

	{
		xp_drefs_params create_params;
		create_params.name = "sim/graphics/view/projection_matrix";
		create_params.type = xp_dref_type::dref_ProjectionMatrix;
		create_params.typeName = "float[4]";
		// ReSharper disable once CppDFAMemoryLeak
		auto dr = new xp_dref(create_params);
		XPHost::m_dref_pool.push_back(dr);
	}

	{
		xp_drefs_params create_params;
		create_params.name = "sim/graphics/view/viewport";
		create_params.type = xp_dref_type::dref_Viewport;
		create_params.typeName = "float?"; //FIXME: resolve type label
		// ReSharper disable once CppDFAMemoryLeak
		auto dr = new xp_dref(create_params);
		XPHost::m_dref_pool.push_back(dr);
	}

	{
		xp_drefs_params create_params;
		create_params.name = "sim/graphics/VR/enabled";
		create_params.type = xp_dref_type::dref_VREnabled;
		create_params.typeName = "int?"; //FIXME: resolve type label
		// ReSharper disable once CppDFAMemoryLeak
		auto dr = new xp_dref(create_params);
		XPHost::m_dref_pool.push_back(dr);
	}

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





