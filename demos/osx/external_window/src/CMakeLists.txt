# List the source files
set(SRCS main.mm
         AppDelegate.mm
         MainGameState.mm
)

# List the Interface Builder Files
set(XIBS Application
)

# Setup the search paths
set(INCLUDE_PATHS "${ATHENA_DEMO_OSX_EXTERNAL_WINDOW_SOURCE_DIR}/include"
                  "${OGRE_SOURCE_DIR}/RenderSystems"
                  "${XMAKE_BINARY_DIR}/include")

include_directories(${INCLUDE_PATHS})

xmake_import_search_paths(ATHENA_FRAMEWORK)
xmake_import_search_paths(OGRE)

# Create and link the executable
xmake_create_executable(ATHENA_DEMO_OSX_EXTERNAL_WINDOW Athena-Demo-External-Window ${SRCS})

xmake_project_link(ATHENA_DEMO_OSX_EXTERNAL_WINDOW ATHENA_FRAMEWORK)
xmake_project_link(ATHENA_DEMO_OSX_EXTERNAL_WINDOW OGRE)
xmake_project_link(ATHENA_DEMO_OSX_EXTERNAL_WINDOW RENDERSYSTEM_GL)

xmake_add_to_property(ATHENA_DEMO_OSX_EXTERNAL_WINDOW LINK_FLAGS "-framework CoreFoundation -framework Cocoa")

# Create .app bundle
set_property(TARGET Athena-Demo-External-Window PROPERTY MACOSX_BUNDLE TRUE)

set_target_properties(Athena-Demo-External-Window PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${ATHENA_DEMO_OSX_EXTERNAL_WINDOW_SOURCE_DIR}/resources/Info.plist")

set(CONTENTS_PATH "${XMAKE_BINARY_DIR}/bin/Athena-Demo-External-Window.app/Contents")

# Make sure we can find the 'ibtool' program. If we can NOT find it we
# skip generation of this project
find_program(IBTOOL ibtool HINTS "/usr/bin" "${OSX_DEVELOPER_ROOT}/usr/bin")
if (${IBTOOL} STREQUAL "IBTOOL-NOTFOUND")
    message(SEND_ERROR "ibtool can not be found and is needed to compile the .xib files. It should have been installed with 
                        the Apple developer tools. The default system paths were searched in addition to ${OSX_DEVELOPER_ROOT}/usr/bin")
endif()

# Make sure the 'Resources' Directory is correctly created before we build
add_custom_command(TARGET Athena-Demo-External-Window PRE_BUILD
                   COMMAND mkdir ARGS -p "${CONTENTS_PATH}/MacOS"
                   COMMAND mkdir ARGS -p "${CONTENTS_PATH}/Resources")

# Compile the .xib files using the 'ibtool' program with the destination being the app package
foreach(xib ${XIBS})
    add_custom_command(TARGET Athena-Demo-External-Window POST_BUILD
                       COMMAND ${IBTOOL} --errors --warnings --notices --output-format human-readable-text 
                               --compile "${CONTENTS_PATH}/Resources/${xib}.nib"
                               "${ATHENA_DEMO_OSX_EXTERNAL_WINDOW_SOURCE_DIR}/resources/${xib}.xib"
                       COMMENT "Compiling resources/${xib}.xib")

endforeach()

# Symlink the Frameworks
add_custom_command(TARGET Athena-Demo-External-Window POST_BUILD
    COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Frameworks
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Ogre.framework ${CONTENTS_PATH}/Frameworks/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Cg.framework ${CONTENTS_PATH}/Frameworks/
)

# Symlink the configuration files
add_custom_command(TARGET Athena-Demo-External-Window POST_BUILD
    COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Resources
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/plugins.cfg ${CONTENTS_PATH}/Resources/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/resources.cfg ${CONTENTS_PATH}/Resources/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/athena.cfg ${CONTENTS_PATH}/Resources/
)

# Symlink the plugins
add_custom_command(TARGET Athena-Demo-External-Window POST_BUILD
    COMMAND mkdir ARGS -p ${CONTENTS_PATH}/Plugins
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/RenderSystem_GL.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_BSPSceneManager.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_CgProgramManager.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_OctreeSceneManager.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_ParticleFX.dylib ${CONTENTS_PATH}/Plugins/
    COMMAND ln ARGS -s -f ${XMAKE_BINARY_DIR}/bin/Plugin_PCZSceneManager.dylib ${CONTENTS_PATH}/Plugins/
)

# Symlink the dynamic libraries
get_target_property(ATHENA_MATH_VERSION Athena-Math SOVERSION)
get_target_property(ATHENA_CORE_VERSION Athena-Core SOVERSION)
get_target_property(ATHENA_ENTITIES_VERSION Athena-Entities SOVERSION)
get_target_property(ATHENA_GRAPHICS_VERSION Athena-Graphics SOVERSION)
get_target_property(ATHENA_PHYSICS_VERSION Athena-Physics SOVERSION)
get_target_property(ATHENA_INPUTS_VERSION Athena-Inputs SOVERSION)
get_target_property(ATHENA_SCRIPTING_VERSION Athena-Scripting SOVERSION)
get_target_property(ATHENA_FRAMEWORK_VERSION Athena-Framework SOVERSION)
get_target_property(V8_VERSION v8 SOVERSION)

add_custom_command(TARGET Athena-Demo-External-Window POST_BUILD
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
xmake_add_to_property(ATHENA_DEMO_OSX_EXTERNAL_WINDOW LINK_FLAGS "-Wl,-rpath,@loader_path/../Frameworks,-rpath,@loader_path/../Libraries")
