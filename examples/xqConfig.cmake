############################################################################
# Copyright (c) 2016, Johan Mabille, Sylvain Corlay, Martin Renou          #
# Copyright (c) 2016, QuantStack                                           #
#                                                                          #
# Distributed under the terms of the BSD 3-Clause License.                 #
#                                                                          #
# The full license is in the file LICENSE, distributed with this software. #
############################################################################

# xeus cmake module
# This module sets the following variables in your project::
#
#   xeus_FOUND - true if xeus found on the system
#   xeus_INCLUDE_DIRS - the directory containing xeus headers
#   xeus_LIBRARY - the library for dynamic linking
#   xeus_STATIC_LIBRARY - the library for static linking


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was xqConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../miniconda3/envs/excuseme-right" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR};${CMAKE_MODULE_PATH}")



include(CMakeFindDependencyMacro)
find_dependency(xtl 0.7)
find_dependency(nlohmann_json 3.2.0)

# On Unix platforms, ZeroMQ is built with autotools and pkg-config is
# required to locate it.
if (WIN32)
    find_dependency(ZeroMQ 4.3.2)
else()
    # In order to not propagate the build-time requirement for pkg-config, we
    # do not propagate the dependency on ZeroMQ.

    #find_package(PkgConfig)
    #pkg_check_modules(ZeroMQ libzmq>=4.3.2 REQUIRED)
endif()

find_dependency(cppzmq 4.4.1)

if(UNIX AND NOT APPLE)
    find_dependency(LibUUID)
endif()

find_dependency(OpenSSL)

if(NOT TARGET qt AND NOT TARGET qt-static)
    include("${CMAKE_CURRENT_LIST_DIR}/xqTargets.cmake")

    if (TARGET qt AND TARGET qt-static)
        get_target_property(xq_INCLUDE_DIR qt INTERFACE_INCLUDE_DIRECTORIES)
        get_target_property(xq_LIBRARY qt LOCATION)
        get_target_property(xq_STATIC_LIBRARY qt-static LOCATION)
    elseif (TARGET qt)
        get_target_property(xq_INCLUDE_DIR qt INTERFACE_INCLUDE_DIRECTORIES)
        get_target_property(xq_LIBRARY qt LOCATION)
    elseif (TARGET qt-static)
        get_target_property(xq_INCLUDE_DIR qt-static INTERFACE_INCLUDE_DIRECTORIES)
        get_target_property(xq_STATIC_LIBRARY qt-static LOCATION)
        set(xq_LIBRARY ${xq_STATIC_LIBRARY})
    endif ()
endif()
