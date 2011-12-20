# Setup the search paths
xmake_import_search_paths(ATHENA_FRAMEWORK)
xmake_import_search_paths(UNITTEST_CPP)


# List the source files
set(SRCS main.cpp
         test_GameStateManager.cpp
         test_TaskManager.cpp
         mocks/mocks.cpp
)


# Declaration of the executable
xmake_create_executable(UNITTESTS_ATHENA_FRAMEWORK UnitTests-Athena-Framework ${SRCS})

xmake_project_link(UNITTESTS_ATHENA_FRAMEWORK UNITTEST_CPP)
xmake_project_link(UNITTESTS_ATHENA_FRAMEWORK ATHENA_FRAMEWORK)


# Run the unit tests
get_property(PATH TARGET UnitTests-Athena-Framework PROPERTY RUNTIME_OUTPUT_DIRECTORY)
add_custom_target(Run-UnitTests-Athena-Framework ALL UnitTests-Athena-Framework DEPENDS UnitTests-Athena-Framework WORKING_DIRECTORY ${PATH} COMMENT "Unit testing: Athena-Framework..." VERBATIM)
