#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "trase" for configuration ""
set_property(TARGET trase APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(trase PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libtrase.a"
  )

list(APPEND _cmake_import_check_targets trase )
list(APPEND _cmake_import_check_files_for_trase "${_IMPORT_PREFIX}/lib/libtrase.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
