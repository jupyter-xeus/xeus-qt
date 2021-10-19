/***********************************************************************************
* Copyright (c) 2016, Johan Mabille, Loic Gouarin, Sylvain Corlay, Wolf Vollprecht *
* Copyright (c) 2016, QuantStack                                                   *
*                                                                                  *
* Distributed under the terms of the BSD 3-Clause License.                         *
*                                                                                  *
* The full license is in the file LICENSE, distributed with this software.         *
************************************************************************************/

#ifndef XQSE_ME_CONFIG_HPP
#define XQSE_ME_CONFIG_HPP

// Project version
#define XQSE_ME_VERSION_MAJOR 0
#define XQSE_ME_VERSION_MINOR 10
#define XQSE_ME_VERSION_PATCH 0

// Composing the version string from major, minor and patch
#define XQSE_ME_CONCATENATE(A, B) XQSE_ME_CONCATENATE_IMPL(A, B)
#define XQSE_ME_CONCATENATE_IMPL(A, B) A##B
#define XQSE_ME_STRINGIFY(a) XQSE_ME_STRINGIFY_IMPL(a)
#define XQSE_ME_STRINGIFY_IMPL(a) #a

#define XQSE_ME_VERSION XQSE_ME_STRINGIFY(XQSE_ME_CONCATENATE(XQSE_ME_VERSION_MAJOR,   \
                       XQSE_ME_CONCATENATE(.,XQSE_ME_CONCATENATE(XQSE_ME_VERSION_MINOR,   \
                                              XQSE_ME_CONCATENATE(.,XQSE_ME_VERSION_PATCH)))))

#ifdef _WIN32
    #ifdef XQSE_ME_EXPORTS
        #define XQSE_ME_API __declspec(dllexport)
    #else
        #define XQSE_ME_API __declspec(dllimport)
    #endif
#else
    #define XQSE_ME_API
#endif

#endif
