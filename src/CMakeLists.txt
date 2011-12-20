# List the source files
set(SRCS Configuration.cpp
         Engine.cpp
         GameStates/GameStateManager.cpp
         Tasks/GameStateTask.cpp
         Tasks/GameStateStackTask.cpp
         Tasks/GraphicsTask.cpp
         Tasks/InputsTask.cpp
         Tasks/PhysicsTask.cpp
         Tasks/TaskEnd.cpp
         Tasks/TaskManager.cpp
         Tasks/TaskStart.cpp
)


# List the include paths
set(INCLUDE_PATHS "${ATHENA_FRAMEWORK_SOURCE_DIR}/include"
                  "${XMAKE_BINARY_DIR}/include")

include_directories(${INCLUDE_PATHS})

xmake_import_search_paths(ATHENA_GRAPHICS)
xmake_import_search_paths(ATHENA_PHYSICS)
xmake_import_search_paths(ATHENA_INPUTS)


# Declaration of the library
if (NOT ATHENA_FRAMEWORK_STATIC)
    xmake_create_dynamic_library(ATHENA_FRAMEWORK Athena-Framework 1.0.0 1.0.0 ${SRCS})
else()
    xmake_create_static_library(ATHENA_FRAMEWORK Athena-Framework ${SRCS})
endif()

xmake_project_link(ATHENA_FRAMEWORK ATHENA_GRAPHICS ATHENA_PHYSICS ATHENA_INPUTS)

xmake_add_to_list_property(ATHENA_FRAMEWORK COMPILE_DEFINITIONS "ATHENA_EXPORTS")


# Exportations
xmake_export_include_paths(ATHENA_FRAMEWORK ${INCLUDE_PATHS})
