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
//  xp_dref.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef xp_dref_hpp
#define xp_dref_hpp

#include <stdio.h>


//#include "XPLMDataAccess.h"

#include <string>
#include <utility>
#include <iostream>
#include <vector>

class Plugin;




struct ParsedType {
	std::string baseType;
	std::vector<int> dimensions;
};




enum xp_dref_type{
    dref_ModelViewMatrix, //sim/graphics/view/modelview_matrix
    dref_ProjectionMatrix, //sim/graphics/view/projection_matrix
    dref_Viewport, //sim/graphics/view/viewport
    dref_VREnabled, //sim/graphics/VR/enabled

    dref_Generic,

};


struct xp_drefs_params {
	std::string name{}; //dref name
	xp_dref_type type=dref_Generic; //enum, used for hooking to fn handlers for gl
	std::string typeName_Raw{}; //type as written in drefs.txt?
	std::string typeName{}; //human-readable type name (float,int,etc)
	//ParsedType parsedType;

	size_t elements_needed=0;
	size_t bytes_needed=0;

	//XPLMDataTypeID sdk_type;

};



class xp_dref {
public:
    virtual ~xp_dref();

    //xp_dref( std::string name, xp_dref_type type, std::string typeName );
	explicit xp_dref( xp_drefs_params params );

    std::vector<Plugin*> m_vecPluginConsumers;

    std::string drefName;

	//FIXME: This dref type meta data needs to be sorted out.
	xp_dref_type drefType;
	std::string drefTypeName;
	std::string drefTypeName_Raw;

	//array dref storage and params
	size_t m_elements;
	size_t m_blob_size;
	void* m_blob;

	float m_valFloat;
    int m_valInt;
    double m_valDouble;


    std::string typeName() const;

    virtual float getFloat();
    virtual void setFloat( float new_val );

    virtual int getInt();
    virtual void setInt( int new_val );

//    virtual void read_arr( float* buff, int offset, int count );

};




typedef xp_dref* XPLMDataRef;


namespace XPHost {
	extern float fps;
	inline std::vector<xp_dref*> m_dref_pool;
}




class dref_factory{
public:
	static inline size_t search_ctr;


	static xp_dref* findDref( const std::string& name );

	static xp_dref* saveDref( const std::string& name, std::string raw_type, bool try_find=true );

	static void init();

	static void cleanup( void* ptr_find_and_remove );

	static void delete_all();

};



#endif /* xp_dref_hpp */
