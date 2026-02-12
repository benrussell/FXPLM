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
//  XPLMDataAccess.cpp
//  XPLM
//
//  Created by Ben on 19/10/2025.
//

#include "XPLMDataAccess.h"

#include "XPLM.h"

#include "glue_Plugin.hpp"
extern Plugin* global_target_plugin;


#include <iostream>





void XPLMSetDatavf( XPLMDataRef dref_h, float* new_values, int offset, int count ){

    FXPLM_DebugLogHeader("XPLMSetDatavf");
    std::cout << "\n";

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setFloat( new_values[0] );

    }

}


void XPLMSetDatavi( XPLMDataRef dref_h, int* new_values, int offset, int count ){

    FXPLM_DebugLogHeader("XPLMSetDatavi");
    std::cout << "\n";

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setFloat( new_values[0] ); //FIXME

    }

}




void XPLMSetDataf( XPLMDataRef dref_h, float new_value ){

    // FXPLM_DebugLogHeader("XPLMSetDataf");
    // std::cout << " dref_h:" << dref_h;
    // std::cout << " dref_h->name:" << dref_h->drefName;
    // std::cout << " val:" << new_value;
    // std::cout << "\n";

    //if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setFloat( new_value );
    //}

}



int XPLMGetDatavi( XPLMDataRef dref_h, int* buffer, int offset, int count ){

#if 1
    FXPLM_DebugLogHeader("HC/ XPLMGetDatavi");
    std::cout << " dref_h:" << dref_h;
	std::cout << " buff:" << buffer;
	std::cout << " offset:" << offset;
	std::cout << " count:" << count;
	std::cout << "\n";
#endif

    //XP11 sample values: 0,0,0,0
	if( buffer ){
        // prob only used for view matrix at this stage
        buffer[0] = 0; //left
        buffer[1] = 0; //bottom
        buffer[2] = 0; //right
        buffer[3] = 0; //top
	}

    return 4;
}




void XPLMGetDatavf( XPLMDataRef dref_h, float* buffer, int offset, int count ){

    FXPLM_DebugLogHeader("XPLMGetDatavf" );
    std::cout << " dref_h:" << dref_h;
    std::cout << " dref_h->name:" << dref_h->drefName;
    std::cout << " buffer:" << buffer;
    std::cout << " offset:" << offset;
    std::cout << " count:" << count;
    std::cout << "\n";

    if( dref_h ){

        auto dr_base = reinterpret_cast<xp_dref*>(dref_h);
        switch( dr_base->drefType ){
            case xp_dref_type::dref_ModelViewMatrix:
//                std::cout << " model view matrix\n";
                //FIXME: glGetFloatv( GL_MODELVIEW_MATRIX, buffer );

                //XP11
                // [1.,-0.,-0.000001,0.,0.,1.,0.,0.,0.000001,-0.,1.,0.,0.360008,-1.58,12.599999,1.]

                break;

            case xp_dref_type::dref_ProjectionMatrix:
//                std::cout << " projection matrix\n";
                //FIXME: glGetFloatv( GL_PROJECTION_MATRIX, buffer );

                // [0.001563,0.,0.,0.,0.,0.002778,0.,0.,0.,0.,-1.,0.,-1.,-1.,-0.,1.]

                break;

            default:
                std::cout << " unexpected: " << dr_base->drefName << "\n";
                break;
        }

    }


    //std::cout << "[" << global_target_plugin->m_pluginSig << "] " << "XPLMGetDatavf: bad handle.\n";

}





float XPLMGetDataf( XPLMDataRef dref_h ){

    // FXPLM_DebugLogHeader("XPLMGetDataf");
    // std::cout << " dref_h:" << dref_h;
    // std::cout << " dref_h->name:" << dref_h->drefName;
    // std::cout << "\n";

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);

        float ret=0.f;

        switch( dr->drefType ){
            // case dref_FrameRatePeriod:
            //     //ret = 1.f / XPHost::fps;
            //     ret = 1.f / 60.f;
            //     break;
            //
            default:
                ret = dr->getFloat();
                break;
        }

        //std::cout << "XPLMGetDataf: returning:" << ret << "\n";
        return ret;

    }


    //could not find a dref
	FXPLM_DebugLogHeader("XPLMGetDataf");
    std::cout << "bad handle. returning 0.f\n";


    return 0.f;
}








int XPLMGetDatai( XPLMDataRef dref_h ){

    // FXPLM_DebugLogHeader("XPLMGetDatai");
    // std::cout << " dref_h:" << dref_h;
    // std::cout << " dref_h->name:" << dref_h->drefName;
    // std::cout << "\n";

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);

        int ret=0;

        switch( dr->drefType ){
//            case dref_FrameRatePeriod:
//            {
//                auto dr_frp = reinterpret_cast<xp_dref_frp *>(dr);
//                ret = dr_frp->getFloat();
//            }
//                break;
            default:
                ret = dr->getInt();
                break;
        }

        // std::cout << "XPLMGetDatai: returning:" << ret << "\n";
        return ret;

    }

    // std::cout << "[" << global_target_plugin->m_pluginSig << "] " << "XPLMGetDatai: bad handle.\n";
    return 0;
}



void XPLMSetDatai( XPLMDataRef dref_h, int new_value ){

    FXPLM_DebugLogHeader("XPLMSetDatai");
    std::cout << " dref_h:" << dref_h;
    std::cout << " dref_h->name:" << dref_h->drefName;
    std::cout << " val:" << new_value;
    std::cout << "\n";

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setInt( new_value );

    }

};



XPLMDataRef XPLMFindDataRef( const char* dref_name ){

    // we only log 404 events

    auto dr = dref_factory::findDref( dref_name ); //can be nullptr ret
    if( dr ) {
        if ( global_target_plugin == nullptr ) {
            throw std::runtime_error("global_target_plugin is nullptr.");
        }
        dr->m_vecPluginConsumers.push_back(global_target_plugin);
        global_target_plugin->m_vecDrefs.push_back(dr);

        return dr;

    }else{
        FXPLM_DebugLogHeader("XPLMFindDataRef");
        std::cout << " dref:[" << dref_name << "]";
        std::cout << " 404";
        std::cout << "\n";

#if 0
        std::cout << "*** AUTO CREATING DREF ***\n";
        auto dr_hack = dref_factory::saveDref(dref_name,"hack", true);
        return dr_hack;
#else
        return nullptr;
#endif
    }



}



XPLMDataRef XPLMRegisterDataAccessor(
                         const char *         inDataName,
                         XPLMDataTypeID       inDataType,
                         int                  inIsWritable,
                         XPLMGetDatai_f       inReadInt,
                         XPLMSetDatai_f       inWriteInt,
                         XPLMGetDataf_f       inReadFloat,
                         XPLMSetDataf_f       inWriteFloat,
                         XPLMGetDatad_f       inReadDouble,
                         XPLMSetDatad_f       inWriteDouble,
                         XPLMGetDatavi_f      inReadIntArray,
                         XPLMSetDatavi_f      inWriteIntArray,
                         XPLMGetDatavf_f      inReadFloatArray,
                         XPLMSetDatavf_f      inWriteFloatArray,
                         XPLMGetDatab_f       inReadData,
                         XPLMSetDatab_f       inWriteData,
                         void *               inReadRefcon,
                         void *               inWriteRefcon)
{

	FXPLM_DebugLogHeader("XPLMRegisterDataAccessor");
    std::cout<<" dr_name:[" << inDataName << "]";
    std::cout << " type_id:" << inDataType;
    std::cout << " write:" << inIsWritable;
    std::cout << "\n\t";
    std::cout << " f_r_int:" << inReadInt;
    std::cout << " f_w_int:" << inWriteInt;
    std::cout << "\n\t";
    std::cout << " f_r_float:" << inReadFloat;
    std::cout << " f_w_float:" << inWriteFloat;
    std::cout << "\n\t";
    std::cout << " f_r_dbl:" << inReadDouble;
    std::cout << " f_w_dbl:" << inWriteDouble;
    std::cout << "\n\t";
    std::cout << " f_r_int[]:" << inReadIntArray;
    std::cout << " f_w_int[]:" << inWriteIntArray;
    std::cout << "\n\t";
    std::cout << " f_r_float[]:" << inReadFloatArray;
    std::cout << " f_w_float[]:" << inWriteFloatArray;
    std::cout << "\n\t";
    std::cout << " f_r_data:" << inReadData;
    std::cout << " f_w_data:" << inWriteData;
    std::cout << "\n\t";
    std::cout << " r_refcon:" << inReadRefcon;
    std::cout << " w_refcon:" << inWriteRefcon;
    std::cout << "\n\t";


    auto dr = dref_factory::saveDref(inDataName, "float");

    if( dr ){
        dr->m_vecPluginConsumers.push_back( global_target_plugin );
		global_target_plugin->m_vecDrefs.push_back(dr);
        std::cout << " ret:" << dr;
        std::cout << "\n";

    }else{
		//FXPLM_DebugLogHeader("XPLMRegisterDataAccessor");
		//std::cout << " [" << inDataName << "]";
        std::cout << " 500: dref_factory::saveDref() ret nullptr.\n";
    }

    return dr;

}


void XPLMUnregisterDataAccessor( XPLMDataRef inDataRef ){

    FXPLM_DebugLogHeader("NOP/ XPLMUnregisterDataAccessor"); //FIXME:
	std::cout << "\n";

};





int XPLMIsDataRefGood( XPLMDataRef dref ) {
    // This fn checks to see if the dref is orphaned.
    // https://developer.x-plane.com/sdk/XPLMDataAccess/#XPLMIsDataRefGood
    // ret 1 for valid dref - not orphaned.
    // ret 0 for orphaned.

    std::cout<<"FXPLM/ XPLMIsDatarefGood - doesnt track dref ownership\n"; //FIXME:
    return 1;
}



XPLMDataTypeID XPLMGetDataRefTypes( XPLMDataRef dref_h ) {
	static bool b_show_broken_msg_if_used = true;
	if(b_show_broken_msg_if_used){
		FXPLM_DebugLogHeader("HC/ XPLMGetDataRefTypes");
		std::cout<<" - half works\n";
		b_show_broken_msg_if_used = false;
	}

    if( dref_h ) {
        auto dr = reinterpret_cast<xp_dref*>(dref_h);

        switch( dr->drefType ) {
            case xp_dref_type::dref_Generic:
                return xplmType_Float;
                break;

            default:
                return xplmType_Unknown;
        }
    }

    return xplmType_Float;
}


void XPLMSetDatad( XPLMDataRef dref_h, double new_value ) {
    std::cout<<"FXPLM/ NOP/ XPLMSetDatad\n"; //FIXME
}

void XPLMSetDatab() {
    std::cout<<"FXPLM/ NOP/ XPLMSetDatab\n"; //FIXME
}


double XPLMGetDatad(  XPLMDataRef dref_h ) {
    std::cout<<"FXPLM/ XPLMGetDatad - broken!\n"; //FIXME

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);

        int ret=0;

        switch( dr->drefType ){
            //            case dref_FrameRatePeriod:
            //            {
            //                auto dr_frp = reinterpret_cast<xp_dref_frp *>(dr);
            //                ret = dr_frp->getFloat();
            //            }
            //                break;
            default:
                ret = 0.0; //dr->getDouble();
                break;
        }

        //        std::cout << "XPLMGetDataf: returning:" << ret << "\n";
        return ret;

    }

    std::cout << "XPLMGetDatad: bad handle.\n";
    return 0.0;

}

void XPLMGetDatab() {
    std::cout<<"FXPLM/ NOP/ XPLMGetDatab\n";
}


XPLM_API int        XPLMShareData(
                         const char *         inDataName,
                         XPLMDataTypeID       inDataType,
                         XPLMDataChanged_f    inNotificationFunc,
                         void *               inNotificationRefcon) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMShareData\n");
}



XPLM_API int        XPLMUnshareData(
                         const char *         inDataName,
                         XPLMDataTypeID       inDataType,
                         XPLMDataChanged_f    inNotificationFunc,
                         void *               inNotificationRefcon) {
    throw std::runtime_error("FXPLM/ NOP/ XPLMUnshareData\n");
}






int        XPLMCanWriteDataRef(
                         XPLMDataRef          inDataRef) {

    FXPLM_DebugLogHeader("HC/ XPLMCanWriteDataRef");
    std::cout<<" drh:[" << inDataRef << "]";
    std::cout<<" hc_ret:0";
    std::cout << "\n";

    return 0;
}

