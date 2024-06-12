/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay, Martin Renou          *
* Copyright (c) 2016, QuantStack                                           *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XQ_HPP
#define XQ_HPP

#ifdef _WIN32
    #ifdef XQ_STATIC_LIB
        #define XQ_API
    #else
        #ifdef XQ_EXPORTS
            #define XQ_API __declspec(dllexport)
        #else
            #define XQ_API __declspec(dllimport)
        #endif
    #endif
#else
    #define XQ_API
#endif

// Project version
#define XQ_VERSION_MAJOR 0
#define XQ_VERSION_MINOR 2
#define XQ_VERSION_PATCH 0

// Binary version
#define XQ_BINARY_CURRENT 2
#define XQ_BINARY_REVISION 0
#define XQ_BINARY_AGE 0

#endif
