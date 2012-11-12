# List the source files
set(SRCS main.mm
         AppDelegate.mm
         MainGameState.mm
)

# Setup the search paths
set(INCLUDE_PATHS "${ATHENA_DEMO_OSX_EXTERNAL_WINDOW_SOURCE_DIR}/include"
                  "${XMAKE_BINARY_DIR}/include")

include_directories(${INCLUDE_PATHS})

xmake_import_search_paths(ATHENA_FRAMEWORK)
xmake_import_search_paths(OGRE)

# Create and link the executable
xmake_create_executable(ATHENA_DEMO_OSX_CREATED_WINDOW Athena-Demo-Created-Window ${SRCS})

xmake_project_link(ATHENA_DEMO_OSX_CREATED_WINDOW ATHENA_FRAMEWORK)
xmake_project_link(ATHENA_DEMO_OSX_CREATED_WINDOW OGRE)

xmake_add_to_property(ATHENA_DEMO_OSX_CREATED_WINDOW LINK_FLAGS "-framework CoreFoundation -framework Cocoa")

# Create .app bundle
set_property(TARGET Athena-Demo-Created-Window PROPERTY MACOSX_BUNDLE TRUE)

set_target_properties(Athena-Demo-Created-Window PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${ATHENA_DEMO_OSX_CREATED_WINDOW_SOURCE_DIR}/resources/Info.plist")

set(CONTENTS_PATH "${XMAKE_BINARY_DIR}/bin/Athena-Demo-Created-Window.app/Contents")

# Make sure the 'Resources' Directory is correctly created before we build
add_custom_command(TARGET Athena-Demo-Created-Window PRE_BUILD
                   COMMAND mkdir ARGS -p "${CONTENTS_PATH}/MacOS"
                   COMMAND mkdir ARGS -p "${CONTENTS_PATH}/Resources")

# Symlink the Frameworks
add_custom_command(TARGET Athena-Demo-Created-Window POST_BUILD
    COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Frameworks
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Ogre.framework ${CONTENTS_PATH}/Frameworks/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Cg.framework ${CONTENTS_PATH}/Frameworks/
)

# Symlink the configuration files
add_custom_command(TARGET Athena-Demo-Created-Window POST_BUILD
    COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Resources
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/plugins.cfg ${CONTENTS_PATH}/Resources/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/resources.cfg ${CONTENTS_PATH}/Resources/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/athena.cfg ${CONTENTS_PATH}/Resources/
)

# Symlink the plugins
add_custom_command(TARGET Athena-Demo-Created-Window POST_BUILD
    COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Plugins
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/RenderSystem_GL.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_BSPSceneManager.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_CgProgramManager.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_OctreeSceneManager.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_ParticleFX.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_PCZSceneManager.dylib ${CONTENTS_PATH}/Plugins/
)

# Symlink the dynamic libraries
add_custom_command(TARGET Athena-Demo-Created-Window POST_BUILD
    COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Libraries
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Math.${ATHENA_MATH_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Core.${ATHENA_CORE_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Entities.${ATHENA_ENTITIES_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Graphics.${ATHENA_GRAPHICS_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Physics.${ATHENA_PHYSICS_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Inputs.${ATHENA_INPUTS_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Scripting.${ATHENA_SCRIPTING_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libAthena-Framework.${ATHENA_FRAMEWORK_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/libv8.${V8_VERSION}.dylib ${CONTENTS_PATH}/Libraries/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/RenderSystem_GL.1.dylib ${CONTENTS_PATH}/Libraries/
)

# Set the RPATH
xmake_add_to_property(ATHENA_DEMO_OSX_CREATED_WINDOW LINK_FLAGS "-Wl,-rpath,@loader_path/../Frameworks,-rpath,@loader_path/../Libraries")
