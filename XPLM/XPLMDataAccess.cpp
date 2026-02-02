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

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setFloat( new_values[0] );

    }

}


void XPLMSetDatavi( XPLMDataRef dref_h, int* new_values, int offset, int count ){

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setFloat( new_values[0] ); //FIXME

    }

}




void XPLMSetDataf( XPLMDataRef dref_h, float new_value ){
//    std::cout << "!XPLMSetDataf\n"; //FIXME

    //if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setFloat( new_value );

    //}


}



int XPLMGetDatavi( XPLMDataRef dref_h, int* buffer, int offset, int count ){

	//XP11 sample values: 0,0,0,0

#if 0 //FIXME: log muted
    FXPLM_DebugLogHeader("HC/ XPLMGetDatavi");
    std::cout << " dref_h:" << dref_h;
	std::cout << " buff:" << buffer;
	std::cout << " offset:" << offset;
	std::cout << " count:" << count;
	std::cout << "\n";
#endif

//	auto drh = (xp_dref*)dref_h;
//	std::cout << " dr_name:[" << drh->drefName << "]\n";

	if( buffer == nullptr ){
		return 4;
	}

    // prob only used for view matrix at this stage
    buffer[0] = 0; //left
    buffer[1] = 0; //bottom
    buffer[2] = 0; //right
    buffer[3] = 0; //top

    return 4;
}




void XPLMGetDatavf( XPLMDataRef dref_h, float* buffer, int offset, int count ){

//    std::cout << "XPLMGetDatavf\n";
//    std::cout << " dref_h " << dref_h << "\n";
//    std::cout << " buffer " << buffer << "\n";
//    std::cout << " offset " << offset << "\n";
//    std::cout << " count  " << count << "\n";

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
    // std::cout << "XPLMGetDatai\n";

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
//    std::cout << "XPLMSetDatai\n";

    if( dref_h ){
        auto dr = reinterpret_cast<xp_dref*>(dref_h);
        dr->setInt( new_value );

    }

};



XPLMDataRef XPLMFindDataRef( const char* dref_name ){

    FXPLM_DebugLogHeader("XPLMFindDataRef");
    std::cout << " dref:[" << dref_name << "]\n";

    const std::string search_name = std::string(dref_name);
    xp_dref *dr = dref_factory::findDref( search_name );

    if ( dr ) {
        if ( global_target_plugin == nullptr ) {
            std::cout<<"FXPLM/ XPLMFindDataRef: global_target_plugin is nullptr. :(  ------------------------\n";
            throw std::runtime_error("global_target_plugin is nullptr.");
        }
        dr->m_vecPluginConsumers.push_back(global_target_plugin);
        global_target_plugin->m_vecDrefs.push_back(dr);

    }else
    {
        FXPLM_DebugLogHeader("XPLMFindDataRef");
        std::cout << " 404:[" << dref_name << "]";
        std::cout << "\n";

        //global_target_plugin->m_plugin_is_enabled = false;
        // global_target_plugin->call_disable();
    }

    return dr;

}



void XPLMRegisterDataAccessor(
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

        std::cout<<" dr_name:[" << inDataName << "]\n";
        auto dr = dref_factory::saveDref(inDataName, "custom");

        if( dr ){
        	dr->m_vecPluginConsumers.push_back( global_target_plugin );
			global_target_plugin->m_vecDrefs.push_back(dr);
        }else{
			FXPLM_DebugLogHeader("XPLMRegisterDataAccessor");
			std::cout << " 404:[" << inDataName << "]";
			std::cout << "\n";
        }

        //throw std::runtime_error("custom drefs not supported. :(");
		//std::cout << ("\tcustom drefs not supported. :(\n");

    }


void XPLMUnregisterDataAccessor( XPLMDataRef inDataRef ){

FXPLM_DebugLogHeader("NOP/ XPLMUnregisterDataAccessor"); //FIXME:
	std::cout << "\n";

};






int XPLMIsDataRefGood( XPLMDataRef dref ) {
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








