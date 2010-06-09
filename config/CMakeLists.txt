set(CONFIG_PLUGIN_FOLDER "./")

file(RELATIVE_PATH CONFIG_MEDIA_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" "${ATHENA_FRAMEWORK_SOURCE_DIR}/README")
string(REPLACE "README" "media" CONFIG_MEDIA_PATH ${CONFIG_MEDIA_PATH})

configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/athena.cfg.in
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/athena.cfg)

configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/plugins.cfg.in
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins.cfg)

configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/resources.cfg.in
               ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources.cfg)
