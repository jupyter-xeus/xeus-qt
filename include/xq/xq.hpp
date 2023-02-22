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
#define XQ_VERSION_MINOR 1
#define XQ_VERSION_PATCH 0

// Binary version
#define XQ_BINARY_CURRENT 1
#define XQ_BINARY_REVISION 0
#define XQ_BINARY_AGE 0

// Kernel protocol version
#define XQ_KERNEL_PROTOCOL_VERSION_MAJOR 0
#define XQ_KERNEL_PROTOCOL_VERSION_MINOR 1

// Composing the protocol version string from major, and minor
#define XQ_CONCATENATE(A, B) XQ_CONCATENATE_IMPL(A, B)
#define XQ_CONCATENATE_IMPL(A, B) A##B
#define XQ_STRINGIFY(a) XQ_STRINGIFY_IMPL(a)
#define XQ_STRINGIFY_IMPL(a) #a

#define XQ_KERNEL_PROTOCOL_VERSION XQ_STRINGIFY(XQ_CONCATENATE(    XQ_KERNEL_PROTOCOL_VERSION_MAJOR,\
                                                    XQ_CONCATENATE(.,  XQ_KERNEL_PROTOCOL_VERSION_MINOR)))

#endif
