if (ATHENA_FRAMEWORK_USE_DEFAULT_CONFIGURATION)

    # Plugins folder
    set(CONFIG_PLUGIN_FOLDER "./")


    # Resource folders
    set(CONFIG_DEMOS_MEDIA_PATH "${ATHENA_FRAMEWORK_SOURCE_DIR}/demos/media")
    set(CONFIG_ATHENA_MEDIA_PATH "${ATHENA_FRAMEWORK_SOURCE_DIR}/media")


    # Render systems
    set(CONFIG_RENDERSYSTEM_D3D9 "")
    set(CONFIG_RENDERSYSTEM_D3D11 "")
    set(CONFIG_RENDERSYSTEM_GL "")

    if (OGRE_BUILD_RENDERSYSTEM_D3D9)
        set(CONFIG_RENDERSYSTEM_D3D9 "\"RenderSystem_Direct3D9\",")
    endif()

    if (OGRE_BUILD_RENDERSYSTEM_D3D11)
        set(CONFIG_RENDERSYSTEM_D3D11 "\"RenderSystem_Direct3D11\",")
    endif()

    if (OGRE_BUILD_RENDERSYSTEM_GL)
        set(CONFIG_RENDERSYSTEM_GL "\"RenderSystem_GL\",")
    endif()


    # Generate the configuration files
    configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/athena.cfg.in
                   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/athena.cfg)

    if (ATHENA_BUILD_DEMOS)
        configure_file(${ATHENA_FRAMEWORK_SOURCE_DIR}/config/demos.cfg.in
                       ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/demos.cfg)
    endif()
endif()
