//
// Created by Ben on 28/12/2025.
//

#ifndef XPLM_GLUE_WINDOWEX_H
#define XPLM_GLUE_WINDOWEX_H


#include "XPLMDisplay.h"
#include <string>

class glue_WindowEx {
public:

	XPLMCreateWindow_t* m_params;

	//extra meta data that the SDK API needs but the params dont carry.
	std::string m_sWindowTitle;
	bool m_bPoppedOut=false;

	// performance timing data
	double m_bakeStart=0.0;
	double m_bakeStop=0.0;

	size_t z_index=0;

	explicit glue_WindowEx( XPLMCreateWindow_t* params );
	~glue_WindowEx();
};


#endif //XPLM_GLUE_WINDOWEX_H
