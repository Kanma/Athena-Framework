# List the source files
set(SRCS Tasks/GraphicsTask.cpp
         Tasks/InputsTask.cpp
         Tasks/TaskEnd.cpp
         Tasks/TaskManager.cpp
         Tasks/TaskStart.cpp
)

# Precompiler definitions
add_definitions(-DATHENA_EXPORTS)

# List the include paths
xmake_include_directories(ATHENA_FRAMEWORK)

# Declaration of the library
if (NOT ATHENA_FRAMEWORK_STATIC)
    add_library(Athena-Framework SHARED ${SRCS})
    xmake_target_link_libraries(Athena-Framework ATHENA_GRAPHICS)
    xmake_target_link_libraries(Athena-Framework ATHENA_INPUTS)

    set_target_properties(Athena-Framework PROPERTIES OUTPUT_NAME "Athena")

    if (APPLE)
        set_target_properties(Athena-Framework PROPERTIES LINK_FLAGS "${XMAKE_OGRE_LINK_FLAGS} ${XMAKE_ATHENA_INPUTS_LINK_FLAGS} -Wl,-rpath,@loader_path/.,-rpath,@loader_path/../Frameworks")
    endif()

    # Set the INSTALL_PATH so that the dynamic library can be local
    set_target_properties(Athena-Framework PROPERTIES BUILD_WITH_INSTALL_RPATH ON
                                                      INSTALL_NAME_DIR "@rpath"
    )

    if (UNIX)
        set_target_properties(Athena-Framework PROPERTIES INSTALL_RPATH ".")
    endif()

else()
    add_library(Athena-Framework STATIC ${SRCS})
endif()
