cmake_minimum_required(VERSION 3.17)
project(XPLM VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)


IF( APPLE )
# Universal build (optional)
#set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "")
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "")
ENDIF( APPLE )


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_definitions(-DGL_SILENCE_DEPRECATION)



IF( APPLE )
    add_definitions( -DAPL=1 )
ENDIF( APPLE )


IF( APPLE )
    add_definitions( -DAPL=1 )

    set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0")

    find_library(SECURITY_FRAMEWORK Security)
    find_library(SYSTEMCONFIGURATION_FRAMEWORK SystemConfiguration)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(COREGRAPHICS_LIBRARY CoreGraphics)
    find_library(APPKIT_LIBRARY AppKit)
    find_library(QUARTZCORE_LIBRARY QuartzCore)

    SET( LIBS_MAC
            ${OPENGL_LIBRARIES}
            ${GLUT_LIBRARY}
#            glfw3

#            ${SECURITY_FRAMEWORK}
#            ${SYSTEMCONFIGURATION_FRAMEWORK}
#            ${IOKIT_FRAMEWORK}
#            ${COREFOUNDATION_LIBRARY}
#            ${COREGRAPHICS_LIBRARY}
#            ${APPKIT_LIBRARY}
#            ${QUARTZCORE_LIBRARY}

    )

ENDIF( APPLE )









# Linux
IF(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set(CMAKE_CXX_FLAGS "-O0 -rdynamic -ldl -fPIC -Wall")

ENDIF(CMAKE_SYSTEM_NAME STREQUAL Linux)




#set( IMGUI_ROOT "third_party/imgui-docking"
#)
#
#set( INC_IMGUI
#        ${IMGUI_ROOT}
#        ${IMGUI_ROOT}/backends/
#        third_party/imgui-filebrowser-master
#
#)


set( INC_STBTT third_party/stb_truetype )

set( INC_GLFW "../glfw/include" )
set( INC_JSON third_party/json-develop/include)

INCLUDE_DIRECTORIES(
        #/opt/homebrew/Cellar/glfw/3.3.8/include
        ${INC_GLFW}
        ${OPENGL_INCLUDE_DIRS}
        ${GLUT_INCLUDE_DIRS}

        ${INC_IMGUI}
        ${INC_JSON}

        ${INC_STBTT}

        #../gz_core/gz_api

        third_party/glew-2.2.0/include
        third_party/stb_image

)


#we're not ready for this.
#trying to link with gz_core/gz_api lib results in weird
#missing symbols from the host app. solve another day.
set( INC_GZ_CORE ../gz_core/gz_api )
include_directories( ${INC_GZ_CORE} )


set( LNK_GLFW "../glfw/build_mac/src" )
set( LNK_GLEW "third_party/glew-2.2.0/lib" )

LINK_DIRECTORIES(
        ${LNK_GLFW}
        ${LNK_GLEW}
)




# Sources / headers
set(PUBLIC_HEADERS
        XPLM/XPLM.h
)
set(SRCS

        third_party/timer/src/Timer.cpp
        third_party/timer/src/Timer.h

        XPLM/xp_dref.cpp
        XPLM/xp_dref.hpp


        XPLM/XPLMDataAccess.cpp
        XPLM/XPLMDataAccess.h

        XPLM/XPLMDisplay.cpp
        XPLM/XPLMDisplay.h

        XPLM/XPLMGraphics.cpp
        XPLM/XPLMGraphics.h

        XPLM/XPLMPlanes.cpp
        XPLM/XPLMPlanes.h

        XPLM/XPLMPlugin.cpp
        XPLM/XPLMPlugin.h

        XPLM/XPLMProcessing.cpp
        XPLM/XPLMProcessing.h

        XPLM/XPLMUtilities.cpp
        XPLM/XPLMUtilities.h

        XPLM/XPLM.cpp
        XPLM/XPLM.h

        XPLM/XPLMMenus.cpp
        XPLM/XPLMMenus.h

        XPLM/XPLMNavigation.cpp
        XPLM/XPLMNavigation.h

        XPLM/XPLMCamera.cpp
        XPLM/XPLMCamera.h

        XPLM/XPLMInstance.cpp
        XPLM/XPLMInstance.h

        XPLM/XPLMScenery.cpp
        XPLM/XPLMScenery.h

        XPLM/XPLMMap.cpp
        XPLM/XPLMMap.h



        XPLM/glue_CmdCustom.hpp
        XPLM/glue_Dataref.hpp
        XPLM/glue_DrawCallbackHost.hpp

        XPLM/DataRefsTxtParse.h     XPLM/DataRefsTxtParse.cpp
        XPLM/glue_Plugin.cpp        XPLM/glue_Plugin.hpp

        XPLM/glue_FBO.hpp           XPLM/glue_FBO.cpp
        XPLM/glue_AvionicsHost.cpp  XPLM/glue_AvionicsHost.hpp
        XPLM/glue_WindowEx.cpp      XPLM/glue_WindowEx.h
        XPLM/glue_Menus.cpp         XPLM/glue_Menus.h
        XPLM/PluginContextGuard.h

)


SUBDIRS(
        gz_core
)


SET( USE_LIBS
        ${LIBS_MAC}
        ${LIBS_LIN}
        # These are for Linux, might throw mac errors?

        GLEW
        #gz_api
        gzcore

        #imgui_lib
        #shim
)


#set(PROJECT_NAME XPLM)


add_library(XPLM SHARED ${SRCS} ${PUBLIC_HEADERS})

target_link_libraries( ${PROJECT_NAME}  ${USE_LIBS} )




IF( APPLE )
set_target_properties(XPLM PROPERTIES
        FRAMEWORK TRUE
        # Bundle / versioning
        MACOSX_FRAMEWORK_IDENTIFIER com.x-plugins.XPLM
        MACOSX_FRAMEWORK_BUNDLE_VERSION ${PROJECT_VERSION}
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        # Headers placed into Headers/ in the framework
        #PUBLIC_HEADER "${PUBLIC_HEADERS}"
        # If you have a custom Info.plist, uncomment:
        # MACOSX_FRAMEWORK_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Info.plist"
        # Avoid accidental signing during local builds
        XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
)

target_include_directories(XPLM
        PUBLIC
        #$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:Headers>
)

# Visibility (optional): default to hidden; mark API with visibility("default")
# target_compile_options(MyFramework PRIVATE -fvisibility=hidden)

# Install the framework
#install(TARGETS XPLM
#        FRAMEWORK DESTINATION Library/Frameworks
#)
install(TARGETS XPLM
        FRAMEWORK DESTINATION "/Users/br/XP12_Libs/Resources/plugins"
        )

ENDIF( APPLE )





IF(CMAKE_SYSTEM_NAME STREQUAL Linux)
    set_target_properties(XPLM PROPERTIES
            OUTPUT_NAME "XPLM_64"
            PREFIX ""
    )

ENDIF(CMAKE_SYSTEM_NAME STREQUAL Linux)









# Example build:
# cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# cmake --build build --config Release