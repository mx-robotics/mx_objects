cmake_minimum_required(VERSION 3.0)
project(MXObjects )
set(MXOBJECTS_MAJOR_VERSION 0)
set(MXOBJECTS_MINOR_VERSION 1)
set(MXOBJECTS_PATCH_VERSION 0)
set(MXOBJECTS_VERSION
  ${MXOBJECTS_MAJOR_VERSION}.${MXOBJECTS_MINOR_VERSION}.${MXOBJECTS_PATCH_VERSION})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/MXObjects)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# set up include-directories
include_directories("${PROJECT_SOURCE_DIR}/common/include")  # to find foo/config.h

add_subdirectory(common)


# The interesting stuff goes here
# ===============================

# Add all targets to the build-tree export set
export(TARGETS mx_objects demo_mx_objects
  FILE "${PROJECT_BINARY_DIR}/MXObjectsTargets.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE MXObjects)

# Create the MXObjectsConfig.cmake and MXObjectsConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(MXObjectsConfig.cmake.in
  "${PROJECT_BINARY_DIR}/MXObjectsConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${MXOBJECTS_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(MXObjectsConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MXObjectsConfig.cmake" @ONLY)
# ... for both
configure_file(MXObjectsConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/MXObjectsConfigVersion.cmake" @ONLY)

# Install the MXObjectsConfig.cmake and MXObjectsConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/MXObjectsConfig.cmake"
  "${PROJECT_BINARY_DIR}/MXObjectsConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
  
# Install the export set for use with the install-tree
install(EXPORT MXObjectsTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
