cmake_minimum_required(VERSION 2.6)
project(ATHENA_FRAMEWORK)

# Settings
if (NOT DEFINED ATHENA_FRAMEWORK_SCRIPTING)
    set(ATHENA_FRAMEWORK_SCRIPTING OFF CACHE BOOL "Enable scripting support (needs Athena-Scripting)")
endif()

if (NOT DEFINED ATHENA_FRAMEWORK_STATIC)
    set(ATHENA_FRAMEWORK_STATIC OFF CACHE BOOL "Build Athena-Framework as a static library")
endif()

if (NOT DEFINED ATHENA_FRAMEWORK_USE_DEFAULT_CONFIGURATION)
    set(ATHENA_USE_DEFAULT_CONFIGURATION ON CACHE BOOL "Use the default configuration of Athena-Framework")
endif()

# Set the output paths
if (NOT DEFINED ATHENA_BINARY_DIR)
    set(ATHENA_BINARY_DIR "${ATHENA_FRAMEWORK_BINARY_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ATHENA_FRAMEWORK_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ATHENA_FRAMEWORK_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ATHENA_FRAMEWORK_BINARY_DIR}/bin")
endif()

# Set the dependencies path
if (NOT DEFINED ATHENA_DEPENDENCIES_DIR)
    set(ATHENA_DEPENDENCIES_DIR "${ATHENA_FRAMEWORK_SOURCE_DIR}/dependencies")
endif()

# We only support Intel 32bits builds
if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "i386" CACHE INTERNAL "" FORCE)
    set(CMAKE_OSX_ARCHITECTURES_DEFAULT "ppc" CACHE INTERNAL "" FORCE)
endif()

# Setup the dependencies
if (NOT DEFINED ATHENA_MATH_STATIC)
    set(ATHENA_MATH_STATIC ON)
endif()

if (NOT DEFINED ATHENA_CORE_STATIC)
    set(ATHENA_CORE_STATIC ON)
endif()

if (NOT DEFINED ATHENA_ENTITIES_STATIC)
    set(ATHENA_ENTITIES_STATIC ON)
endif()

if (NOT DEFINED ATHENA_GRAPHICS_STATIC)
    set(ATHENA_GRAPHICS_STATIC ON)
endif()

if (NOT DEFINED ATHENA_PHYSICS_STATIC)
    set(ATHENA_PHYSICS_STATIC ON)
endif()

if (NOT DEFINED ATHENA_INPUTS_STATIC)
    set(ATHENA_INPUTS_STATIC ON)
endif()

# Import XMake
if (NOT EXISTS "${ATHENA_DEPENDENCIES_DIR}/xmake/XMake.cmake")
    message(FATAL_ERROR
"Missing dependency: XMake
Athena-Framework requires the following dependencies:
   - XMake
   - Athena-Math
   - Athena-Core
   - Athena-Entities
   - Athena-Graphics
   - Athena-Physics
   - Athena-Inputs
   - UnitTest++
   - Ogre
   - Bullet
   - FreeImage
   - FreeType
   - ZLib
   - zziplib
They are provided as GIT submodules of this repository.
Did you forgot to execute the following commands?
   git submodule init
   git submodule update")
endif()

include("${ATHENA_DEPENDENCIES_DIR}/xmake/XMake.cmake")

# Process the dependencies
add_subdirectory(dependencies)

# XMake settings
if (ATHENA_FRAMEWORK_STATIC)
    xmake_init_static(ATHENA_FRAMEWORK)
    xmake_add_link_paths(ATHENA_FRAMEWORK "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    xmake_add_link_targets(ATHENA_FRAMEWORK Athena-Framework "${XMAKE_ATHENA_GRAPHICS_LINK_TARGETS}" "${XMAKE_ATHENA_PHYSICS_LINK_TARGETS}" "${XMAKE_ATHENA_INPUTS_LINK_TARGETS}")
# else(APPLE)
#     xmake_init_framework(ATHENA_FRAMEWORK)
#     xmake_add_link_paths(ATHENA_FRAMEWORK "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
#     xmake_add_link_flags(ATHENA_FRAMEWORK "-F${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" "-framework Athena" ${XMAKE_OGRE_LINK_FLAGS})
else()
    xmake_init_dynamic(ATHENA_FRAMEWORK)
    xmake_add_link_paths(ATHENA_FRAMEWORK "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    xmake_add_link_targets(ATHENA_FRAMEWORK Athena-Framework)
endif()

xmake_add_include_paths(ATHENA_FRAMEWORK ${ATHENA_FRAMEWORK_SOURCE_DIR}/include
                                         ${XMAKE_ATHENA_GRAPHICS_INCLUDE_PATHS}
                                         ${XMAKE_ATHENA_PHYSICS_INCLUDE_PATHS}
                                         ${XMAKE_ATHENA_INPUTS_INCLUDE_PATHS})

if (APPLE AND NOT ATHENA_FRAMEWORK_STATIC)
    xmake_add_link_flags(ATHENA_FRAMEWORK "${XMAKE_ATHENA_GRAPHICS_LINK_FLAGS} ${XMAKE_ATHENA_PHYSICS_LINK_FLAGS} ${XMAKE_ATHENA_INPUTS_LINK_FLAGS}")
endif()

# Subdirectories to process
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(config)
add_subdirectory(unittests)
