if (ATHENA_FRAMEWORK_USE_DEFAULT_CONFIGURATION)
    set(CONFIG_PLUGIN_FOLDER "./")

    if (APPLE)
        file(RELATIVE_PATH CONFIG_ATHENA_MEDIA_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/appname" "${ATHENA_FRAMEWORK_SOURCE_DIR}/README")
    else()
        file(RELATIVE_PATH CONFIG_ATHENA_MEDIA_PATH "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" "${ATHENA_FRAMEWORK_SOURCE_DIR}/README")
    endif()

    string(REPLACE "README" "demos/media" CONFIG_DEMOS_MEDIA_PATH ${CONFIG_ATHENA_MEDIA_PATH})
    string(REPLACE "README" "media" CONFIG_ATHENA_MEDIA_PATH ${CONFIG_ATHENA_MEDIA_PATH})

    configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/athena.cfg.in
                   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/athena.cfg)

    configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/plugins.cfg.in
                   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins.cfg)

    if (ATHENA_BUILD_DEMOS)
        configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/resources_demos.cfg.in
                       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources.cfg)
    else()
        configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/resources.cfg.in
                       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources.cfg)
    endif()
endif()
