cmake_minimum_required(VERSION 3.8)
project(xq)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(XQ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(XQ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(XQ_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(nlohmann_json_REQUIRED_VERSION 3.2.0)
set(xtl_REQUIRED_VERSION 0.7)
set(cppzmq_REQUIRED_VERSION 4.4.1)
set(zeromq_REQUIRED_VERSION 4.3.2)

# Compilation options
option(XQ_DISABLE_ARCH_NATIVE "disable -march=native flag" OFF)
option(XQ_BUILD_SHARED_LIBS "Build XQ shared library." ON)
option(XQ_BUILD_STATIC_LIBS "Build XQ static library (default if BUILD_SHARED_LIBS is OFF)." ON)
option(XQ_STATIC_DEPENDENCIES "link statically with XQ dependencies" OFF)

# Versioning
# ==========

# Project version
file(STRINGS "${XQ_INCLUDE_DIR}/xq/xq.hpp" xq_version_defines
     REGEX "#define XQ_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${xq_version_defines})
    if(ver MATCHES "#define XQ_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(XQ_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XQ_VERSION
    ${XQ_VERSION_MAJOR}.${XQ_VERSION_MINOR}.${XQ_VERSION_PATCH})
message(STATUS "xeus version: v${XQ_VERSION}")

# Binary version
# See the following URL for explanations about the binary versionning
# https://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html#Updating-version-info
file(STRINGS "${XQ_INCLUDE_DIR}/xq/xq.hpp" xq_version_defines
    REGEX "#define XQ_BINARY_(CURRENT|REVISION|AGE)")
foreach(ver ${xq_version_defines})
    if(ver MATCHES "#define XQ_BINARY_(CURRENT|REVISION|AGE) +([^ ]+)$")
        set(XQ_BINARY_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(XQ_BINARY_VERSION
    ${XQ_BINARY_CURRENT}.${XQ_BINARY_REVISION}.${XQ_BINARY_AGE})
message(STATUS "xeus binary version: v${XQ_BINARY_VERSION}")


# Dependencies
# ============

find_package(Qt6Widgets ${Qt6_REQUIRED_VERSION} REQUIRED)
find_package(Qt6Core ${Qt6_REQUIRED_VERSION} REQUIRED)
# if (NOT TARGET Qt6)
# endif ()

if (NOT TARGET xeus AND NOT TARGET xeus-static)
    find_package(xeus ${xeus_REQUIRED_VERSION} REQUIRED)
endif ()

if (NOT TARGET nlohmann_json)
    find_package(nlohmann_json ${nlohmann_json_REQUIRED_VERSION} REQUIRED)
endif ()

if (NOT TARGET xtl)
    find_package(xtl ${xtl_REQUIRED_VERSION} REQUIRED)
endif ()

if (NOT TARGET cppzmq AND NOT TARGET cppzmq-static)
    find_package(cppzmq ${cppzmq_REQUIRED_VERSION} REQUIRED)
endif ()

if (NOT TARGET libzmq AND NOT TARGET libzmq-static)
    if (WIN32)
        find_package(zeromq ${zeromq_REQUIRED_VERSION} REQUIRED)
    else ()
        find_package(zeromq ${zeromq_REQUIRED_VERSION} QUIET)

        if (NOT ZeroMQ_FOUND)
            message(STATUS "CMake libzmq package not found, trying again with pkg-config")
            find_package(PkgConfig)
            pkg_check_modules(ZeroMQ libzmq>=${zeromq_REQUIRED_VERSION} REQUIRED)
            set(ZeroMQ_VERSION ${PC_LIBZMQ_VERSION})
            find_library(ZeroMQ_LIBRARY NAMES libzmq.so libzmq.dylib libzmq.dll
                 PATHS ${PC_LIBZMQ_LIBDIR} ${PC_LIBZMQ_LIBRARY_DIRS})
            find_library(ZeroMQ_STATIC_LIBRARY NAMES libzmq-static.a libzmq.a libzmq.dll.a
                 PATHS ${PC_LIBZMQ_LIBDIR} ${PC_LIBZMQ_LIBRARY_DIRS})
            message(STATUS "STATIC_LIBRARY" {ZeroMQ_LIBRARY})
            message(STATUS "STATIC_STATIC_LIBRARY" {ZeroMQ_STATIC_LIBRARY})
         endif ()
    endif ()
endif ()

if (NOT DEFINED OPENSSL_LIBRARY)
    set(OPENSSL_ROOT_DIR ${CMAKE_INSTALL_PREFIX})
    find_package(OpenSSL REQUIRED)
endif ()

# Source files
# ============

set(XQ_HEADERS
    ${XQ_INCLUDE_DIR}/xq/xq.hpp
    ${XQ_INCLUDE_DIR}/xq/xqServer.hpp
    ${XQ_INCLUDE_DIR}/xq/xqKernelModule.hpp
    ${XQ_INCLUDE_DIR}/xq/xqGenericApplication.hpp
    ${XQ_INCLUDE_DIR}/xq/xqGenericInterpreter.hpp
    )

set(XQ_SOURCES
    ${XQ_SOURCE_DIR}/xqServer.cpp
    ${XQ_SOURCE_DIR}/xqKernelModule.cpp
    ${XQ_SOURCE_DIR}/xqGenericApplication.cpp
    ${XQ_SOURCE_DIR}/xqGenericInterpreter.cpp
   )

# Targets and link
# ================

include(CheckCXXCompilerFlag)

string(TOUPPER "${CMAKE_BUILD_TYPE}" U_CMAKE_BUILD_TYPE)

if (NOT APPLE)
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif ()

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib; ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")

macro(xq_create_target target_name linkage output_name)
    string(TOUPPER "${linkage}" linkage_upper)

    if (NOT ${linkage_upper} MATCHES "^(SHARED|STATIC)$")
        message(FATAL_ERROR "Invalid library linkage: ${linkage}")
    endif ()

    # Output
    # ======

    add_library(${target_name} ${linkage_upper} ${XQ_SOURCES} ${XQ_HEADERS})

    if (APPLE)
        set_target_properties(
            ${target_name} PROPERTIES
            MACOSX_RPATH ON
        )
    else ()
        set_target_properties(
            ${target_name} PROPERTIES
            BUILD_WITH_INSTALL_RPATH 1
        )
    endif ()

    target_include_directories(
        ${target_name}
        PUBLIC $<BUILD_INTERFACE:${XQ_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
    )

    target_link_libraries(
        ${target_name}
        PUBLIC ${CPPZMQ_TARGET_NAME}
        PUBLIC nlohmann_json::nlohmann_json
        PUBLIC xtl
        PUBLIC xeus
        PUBLIC Qt6::Widgets
        PUBLIC Qt6::Core
    )

    target_link_libraries(${target_name} PUBLIC OpenSSL::Crypto)

    if (NOT MSVC)
        if (APPLE)
            target_link_libraries(${target_name} PUBLIC "-framework CoreFoundation")
        else ()
            if (XQ_STATIC_DEPENDENCIES)
                find_path(LIBUUID_INCLUDE_DIR uuid.h PATH_SUFFIXES uuid)
                find_library(LIBUUID_LIBRARY libuuid.a)
                target_include_directories(${target_name} PRIVATE ${LIBUUID_INCLUDE_DIR})
                target_link_libraries(${target_name} PUBLIC ${LIBUUID_LIBRARY}) 
                target_link_libraries(${target_name} PUBLIC ${sodium_LIBRARY_RELEASE})
            else ()
                find_package(LibUUID REQUIRED)
                target_link_libraries(${target_name} PUBLIC LibUUID::LibUUID)
            endif ()
        endif ()
    endif ()

    if (UNIX)
        # CMake does not compute the version number of so files as libtool
        # does on Linux. Strictly speaking, we should exclude FreeBSD and
        # Apple from this, but that would require having different version
        # numbers depending on the platform. We prefer to follow the
        # libtool pattern everywhere.
        math(EXPR XQ_BINARY_COMPATIBLE "${XQ_BINARY_CURRENT} - ${XQ_BINARY_AGE}")
        set_target_properties(
            ${target_name}
            PROPERTIES
            PUBLIC_HEADER "${XQ_HEADERS}"
            COMPILE_DEFINITIONS "XQ_EXPORTS"
            PREFIX ""
            VERSION "${XQ_BINARY_COMPATIBLE}.${XQ_BINARY_REVISION}.${XQ_BINARY_AGE}"
            SOVERSION ${XQ_BINARY_COMPATIBLE}
            OUTPUT_NAME "lib${output_name}"
        )
    else()
        set_target_properties(
            ${target_name}
            PROPERTIES
            PUBLIC_HEADER "${XQ_HEADERS}"
            COMPILE_DEFINITIONS "XQ_EXPORTS"
            PREFIX ""
            VERSION ${XQ_BINARY_VERSION}
            SOVERSION ${XQ_BINARY_CURRENT}
            OUTPUT_NAME "lib${output_name}"
        )
    endif()

    # Compilation flags
    # =================

    target_compile_features(${target_name} PRIVATE cxx_std_11)

    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
        CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR
        CMAKE_CXX_COMPILER_ID MATCHES "Intel")

        target_compile_options(${target_name} PUBLIC -Wunused-parameter -Wextra -Wreorder)

        if (NOT XQ_DISABLE_ARCH_NATIVE)
            target_compile_options(${target_name} PUBLIC -march=native)
        endif ()

        message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    endif()

    if (${linkage_upper} STREQUAL "STATIC")
        target_compile_definitions(${target_name} PUBLIC XQ_STATIC_LIB)
    endif ()

    if (MSVC)
        target_compile_definitions(${target_name} PUBLIC -DNOMINMAX)
        target_compile_options(${target_name} PUBLIC /DGUID_WINDOWS /MP /bigobj)
        target_compile_options(${target_name} PUBLIC /wd4251 /wd4996)
    elseif (APPLE)
        target_compile_definitions(${target_name} PUBLIC -DGUID_CFUUID)
    else ()
        target_compile_definitions(${target_name} PUBLIC -DGUID_LIBUUID)
    endif ()

    if (XQ_STATIC_DEPENDENCIES AND CMAKE_DL_LIBS)
        target_link_libraries(${target_name} PRIVATE ${CMAKE_DL_LIBS} util rt)
    endif ()

    TARGET_LINK_LIBRARIES(${target_name} ${QT_LIBRARIES})


endmacro()

set(xq_targets "")

if (XQ_BUILD_SHARED_LIBS)
    xq_create_target(xq SHARED xq)
    if(CMAKE_TARGET_SYSTEM MATCHES "Linux" AND OPENSSL_USE_STATIC_LIBS)
        # Do not reexport OpenSSL symbols from xq, for libraries
        #   Prevents conflicts with other versions of OpenSSL
        #   loaded in the same process namespace, which can cause
        #   crashes if the versions are not compatible.
        set_target_properties(xq PROPERTIES LINK_FLAGS "-Wl,--exclude-libs,libcrypto.a")
    endif()
    list(APPEND xq_targets xq)
endif ()

if (XQ_BUILD_STATIC_LIBS)
    # On Windows, a static library should use a different output name
    # to avoid the conflict with the import library of a shared one.
    if (CMAKE_HOST_WIN32)
        xq_create_target(xq-static STATIC xq-static)
    else ()
        xq_create_target(xq-static STATIC xq)
    endif ()

    list(APPEND xq_targets xq-static)
endif ()

# Installation
# ============

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(XQ_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE STRING "install path for xqConfig.cmake")

install(TARGETS ${xq_targets}
        EXPORT ${PROJECT_NAME}-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xq)

# Makes the project importable from the build directory
export(EXPORT ${PROJECT_NAME}-targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")

# Configure 'xqConfig.cmake' for a build tree
set(XQ_CONFIG_CODE "####### Expanded from \@XQ_CONFIG_CODE\@ #######\n")
set(XQ_CONFIG_CODE "${XQ_CONFIG_CODE}set(CMAKE_MODULE_PATH \"${CMAKE_CURRENT_SOURCE_DIR}/cmake;\${CMAKE_MODULE_PATH}\")\n")
set(XQ_CONFIG_CODE "${XQ_CONFIG_CODE}##################################################")
configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${PROJECT_BINARY_DIR})

# Configure 'xqConfig.cmake' for an install tree
set(XQ_CONFIG_CODE "")
configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${XQ_CMAKECONFIG_INSTALL_DIR})


write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${XQ_VERSION}
                                 COMPATIBILITY AnyNewerVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
              ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindLibUUID.cmake
              DESTINATION ${XQ_CMAKECONFIG_INSTALL_DIR})
install(EXPORT ${PROJECT_NAME}-targets
        FILE ${PROJECT_NAME}Targets.cmake
        DESTINATION ${XQ_CMAKECONFIG_INSTALL_DIR})
