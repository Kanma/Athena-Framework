function(create_demo_created_window PROJECT_NAME DEMO_NAME SRCS HEADERS INCLUDE_PATHS)

    # List the OSX-specific header files
    set(OSX_HEADERS ${ATHENA_DEMOS_SOURCE_DIR}/osx/created_window/include/AppDelegate.h
    )

    # List the OSX-specific source files
    set(OSX_SRCS ${ATHENA_DEMOS_SOURCE_DIR}/osx/created_window/src/main.mm
                 ${ATHENA_DEMOS_SOURCE_DIR}/osx/created_window/src/AppDelegate.mm
    )

    # Setup the search paths
    set(INCLUDE_PATHS ${INCLUDE_PATHS}
                      "${ATHENA_DEMOS_SOURCE_DIR}/osx"
                      "${XMAKE_BINARY_DIR}/include")

    include_directories(BEFORE ${INCLUDE_PATHS})

    xmake_import_search_paths(ATHENA_FRAMEWORK)
    xmake_import_search_paths(OGRE)

    # Create and link the executable
    xmake_create_executable(${PROJECT_NAME} ${DEMO_NAME} ${SRCS} ${OSX_SRCS} ${HEADERS} ${OSX_HEADERS})

    xmake_project_link(${PROJECT_NAME} ATHENA_FRAMEWORK)
    xmake_project_link(${PROJECT_NAME} OGRE)

    xmake_add_to_property(${PROJECT_NAME} LINK_FLAGS "-framework CoreFoundation -framework Cocoa")

    # Create .app bundle
    set_property(TARGET ${DEMO_NAME} PROPERTY MACOSX_BUNDLE TRUE)

    configure_file("${ATHENA_DEMOS_SOURCE_DIR}/osx/created_window/resources/Info.plist.in"
                   "${XMAKE_BINARY_DIR}/generated/Athena-Demos/${DEMO_NAME}/Info.plist")

    set_target_properties(${DEMO_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${XMAKE_BINARY_DIR}/generated/Athena-Demos/${DEMO_NAME}/Info.plist")

    set(CONTENTS_PATH "${XMAKE_BINARY_DIR}/bin/${DEMO_NAME}.app/Contents")

    # Make sure the 'Resources' Directory is correctly created before we build
    add_custom_command(TARGET ${DEMO_NAME} PRE_BUILD
                       COMMAND mkdir ARGS -p "${CONTENTS_PATH}/MacOS"
                       COMMAND mkdir ARGS -p "${CONTENTS_PATH}/Resources")

    # Symlink the Frameworks
    add_custom_command(TARGET ${DEMO_NAME} POST_BUILD
        COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Frameworks
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Ogre.framework ${CONTENTS_PATH}/Frameworks/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Cg.framework ${CONTENTS_PATH}/Frameworks/
    )

    # Symlink the configuration files
    add_custom_command(TARGET ${DEMO_NAME} POST_BUILD
        COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Resources
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/plugins.cfg ${CONTENTS_PATH}/Resources/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/resources.cfg ${CONTENTS_PATH}/Resources/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/athena.cfg ${CONTENTS_PATH}/Resources/
    )

    # Symlink the plugins
    add_custom_command(TARGET ${DEMO_NAME} POST_BUILD
        COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Plugins
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/RenderSystem_GL.dylib ${CONTENTS_PATH}/Plugins/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_BSPSceneManager.dylib ${CONTENTS_PATH}/Plugins/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_CgProgramManager.dylib ${CONTENTS_PATH}/Plugins/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_OctreeSceneManager.dylib ${CONTENTS_PATH}/Plugins/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_ParticleFX.dylib ${CONTENTS_PATH}/Plugins/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_PCZSceneManager.dylib ${CONTENTS_PATH}/Plugins/
    )

    # Symlink the dynamic libraries
    add_custom_command(TARGET ${DEMO_NAME} POST_BUILD
        COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Libraries
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Math.${ATHENA_MATH_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Core.${ATHENA_CORE_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Entities.${ATHENA_ENTITIES_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Graphics.${ATHENA_GRAPHICS_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Physics.${ATHENA_PHYSICS_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Inputs.${ATHENA_INPUTS_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Scripting.${ATHENA_SCRIPTING_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-GUI.${ATHENA_GUI_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Framework.${ATHENA_FRAMEWORK_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libv8.${V8_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libRocketCore.${LIBROCKET_CORE_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libRocketControls.${LIBROCKET_CONTROLS_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libRocketDebugger.${LIBROCKET_DEBUGGER_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
        COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/RenderSystem_GL.1.dylib ${CONTENTS_PATH}/Libraries/
    )

    # Set the RPATH
    xmake_add_to_property(${PROJECT_NAME} LINK_FLAGS "-Wl,-rpath,@loader_path/../Frameworks,-rpath,@loader_path/../Libraries")

endfunction()
