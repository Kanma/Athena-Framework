# List the headers files
set(HEADERS ${XMAKE_BINARY_DIR}/include/Athena/Config.h
           ../include/Athena/Configuration.h
           ../include/Athena/Engine.h
           ../include/Athena/Prerequisites.h
           ../include/Athena/GameStates/GameStateManager.h
           ../include/Athena/GameStates/IGameState.h
           ../include/Athena/Tasks/GameStateTask.h
           ../include/Athena/Tasks/GameStateStackTask.h
           ../include/Athena/Tasks/GraphicsTask.h
           ../include/Athena/Tasks/InputsTask.h
           ../include/Athena/Tasks/PhysicsTask.h
           ../include/Athena/Tasks/Task.h
           ../include/Athena/Tasks/TaskEnd.h
           ../include/Athena/Tasks/TaskManager.h
           ../include/Athena/Tasks/TaskStart.h
)


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
    xmake_create_dynamic_library(ATHENA_FRAMEWORK Athena-Framework
                                 "${ATHENA_FRAMEWORK_VERSION_MAJOR}.${ATHENA_FRAMEWORK_VERSION_MINOR}.${ATHENA_FRAMEWORK_VERSION_PATCH}"
                                 "${ATHENA_FRAMEWORK_VERSION_MAJOR}.${ATHENA_FRAMEWORK_VERSION_MINOR}.${ATHENA_FRAMEWORK_VERSION_PATCH}"
                                 ${HEADERS} ${SRCS})

    xmake_add_to_list_property(ATHENA_FRAMEWORK COMPILE_DEFINITIONS "ATHENA_FRAMEWORK_EXPORTS")
else()
    xmake_create_static_library(ATHENA_FRAMEWORK Athena-Framework ${HEADERS} ${SRCS})
endif()

xmake_project_link(ATHENA_FRAMEWORK ATHENA_GRAPHICS ATHENA_PHYSICS ATHENA_INPUTS)


# Exportations
xmake_export_include_paths(ATHENA_FRAMEWORK ${INCLUDE_PATHS})
