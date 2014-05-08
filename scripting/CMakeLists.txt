# Setup the search paths
xmake_import_search_paths(ATHENA_SCRIPTING)
xmake_import_search_paths(ATHENA_FRAMEWORK)


# List the source files
set(SRCS module.cpp
         time.cpp
)

set(JS_SRCS ""
)


# Declaration of the module
xmake_create_dynamic_library(ATHENA_FRAMEWORK_SCRIPTING_MODULE Athena-Framework-Scripting-module
                            "${ATHENA_FRAMEWORK_VERSION_MAJOR}.${ATHENA_FRAMEWORK_VERSION_MINOR}.${ATHENA_FRAMEWORK_VERSION_PATCH}"
                            "${ATHENA_FRAMEWORK_VERSION_MAJOR}.${ATHENA_FRAMEWORK_VERSION_MINOR}.${ATHENA_FRAMEWORK_VERSION_PATCH}"
                             ${SRCS})

xmake_project_link(ATHENA_FRAMEWORK_SCRIPTING_MODULE ATHENA_FRAMEWORK ATHENA_SCRIPTING)

create_scripting_module(ATHENA_FRAMEWORK_SCRIPTING_MODULE "Athena" "${JS_SRCS}")
