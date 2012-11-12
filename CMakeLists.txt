cmake_minimum_required(VERSION 2.6)
project(ATHENA_FRAMEWORK)


##########################################################################################
# Settings

if (NOT DEFINED ATHENA_FRAMEWORK_USE_DEFAULT_CONFIGURATION)
    set(ATHENA_FRAMEWORK_USE_DEFAULT_CONFIGURATION ON CACHE BOOL "Use the default configuration of Athena-Framework")
endif()

if (NOT DEFINED ATHENA_BUILD_DEMOS)
    set(ATHENA_BUILD_DEMOS OFF CACHE BOOL "Build the demos of the Athena Game Framework")
endif()


##########################################################################################
# Library version

set(ATHENA_FRAMEWORK_VERSION_MAJOR 1)
set(ATHENA_FRAMEWORK_VERSION_MINOR 1)
set(ATHENA_FRAMEWORK_VERSION_PATCH 0)
set(ATHENA_FRAMEWORK_VERSION_SUFFIX " (Dev)")


##########################################################################################
# XMake-related settings

# Set the output paths
if (NOT DEFINED XMAKE_BINARY_DIR)
    set(XMAKE_BINARY_DIR "${ATHENA_FRAMEWORK_BINARY_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${XMAKE_BINARY_DIR}/bin")
endif()

# Set the dependencies path
if (NOT DEFINED XMAKE_DEPENDENCIES_DIR)
    set(XMAKE_DEPENDENCIES_DIR "${ATHENA_FRAMEWORK_SOURCE_DIR}/dependencies")
endif()


##########################################################################################
# XMake importation

if (NOT EXISTS "${XMAKE_DEPENDENCIES_DIR}/XMake/XMake.cmake")
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

include("${XMAKE_DEPENDENCIES_DIR}/XMake/XMake.cmake")


##########################################################################################
# Process subdirectories

add_subdirectory(dependencies)

if (DEFINED ATHENA_SCRIPTING_ENABLED AND ATHENA_SCRIPTING_ENABLED)
    set(ATHENA_FRAMEWORK_SCRIPTING ON)
else()
    set(ATHENA_FRAMEWORK_SCRIPTING OFF)
endif()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(config)
add_subdirectory(unittests)

if (DEFINED ATHENA_SCRIPTING_ENABLED AND ATHENA_SCRIPTING_ENABLED)
    add_subdirectory(scripting)
endif()

if (DEFINED ATHENA_BUILD_DEMOS)
    add_subdirectory(demos)
endif()
