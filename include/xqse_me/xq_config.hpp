/***********************************************************************************
* Copyright (c) 2016, Johan Mabille, Loic Gouarin, Sylvain Corlay, Wolf Vollprecht *
* Copyright (c) 2016, QuantStack                                                   *
*                                                                                  *
* Distributed under the terms of the BSD 3-Clause License.                         *
*                                                                                  *
* The full license is in the file LICENSE, distributed with this software.         *
************************************************************************************/

#ifndef XEUS_QT_CONFIG_HPP
#define XEUS_QT_CONFIG_HPP

// Project version
#define XEUS_QT_VERSION_MAJOR 0
#define XEUS_QT_VERSION_MINOR 10
#define XEUS_QT_VERSION_PATCH 0

// Composing the version string from major, minor and patch
#define XEUS_QT_CONCATENATE(A, B) XEUS_QT_CONCATENATE_IMPL(A, B)
#define XEUS_QT_CONCATENATE_IMPL(A, B) A##B
#define XEUS_QT_STRINGIFY(a) XEUS_QT_STRINGIFY_IMPL(a)
#define XEUS_QT_STRINGIFY_IMPL(a) #a

#define XEUS_QT_VERSION XEUS_QT_STRINGIFY(XEUS_QT_CONCATENATE(XEUS_QT_VERSION_MAJOR,   \
                       XEUS_QT_CONCATENATE(.,XEUS_QT_CONCATENATE(XEUS_QT_VERSION_MINOR,   \
                                              XEUS_QT_CONCATENATE(.,XEUS_QT_VERSION_PATCH)))))

#ifdef _WIN32
    #ifdef XEUS_QT_EXPORTS
        #define XEUS_QT_API __declspec(dllexport)
    #else
        #define XEUS_QT_API __declspec(dllimport)
    #endif
#else
    #define XEUS_QT_API
#endif

#endif
