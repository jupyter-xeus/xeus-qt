#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "xq" for configuration ""
set_property(TARGET xq APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(xq PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libxq.1.0.0.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/libxq.1.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS xq )
list(APPEND _IMPORT_CHECK_FILES_FOR_xq "${_IMPORT_PREFIX}/lib/libxq.1.0.0.dylib" )

# Import target "xq-static" for configuration ""
set_property(TARGET xq-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(xq-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libxq.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS xq-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_xq-static "${_IMPORT_PREFIX}/lib/libxq.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
