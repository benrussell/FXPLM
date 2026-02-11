//
//  xp_dref.hpp
//  XPLM
//
//  Created by Ben on 20/10/2025.
//

#ifndef xp_dref_hpp
#define xp_dref_hpp

#include <stdio.h>




#include <string>
#include <utility>
#include <iostream>
#include <vector>

class Plugin;



enum xp_dref_type{
    dref_ModelViewMatrix, //sim/graphics/view/modelview_matrix
    dref_ProjectionMatrix, //sim/graphics/view/projection_matrix
    dref_Viewport, //sim/graphics/view/viewport
    dref_VREnabled, //sim/graphics/VR/enabled

    dref_Generic,

};


class xp_dref {
public:
    virtual ~xp_dref() = default;

    xp_dref( std::string name, xp_dref_type type, std::string typeName );

    std::vector<Plugin*> m_vecPluginConsumers;

    std::string drefName;


    float m_valFloat;
    int m_valInt;
    double m_valDouble;


    //FIXME: This dref type meta data needs to be sorted out.
    xp_dref_type drefType;
    std::string drefTypeName;

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

	static xp_dref* saveDref( const std::string& name, const std::string type, bool try_find=true );

	static void init();

	static void cleanup( void* ptr_find_and_remove );

	static void delete_all();

};



#endif /* xp_dref_hpp */
