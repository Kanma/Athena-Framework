# Setup the search paths
xmake_include_directories(ATHENA_FRAMEWORK)
xmake_include_directories(UNITTEST_CPP)

# List the source files
file(GLOB SRCS main.cpp
               test_GameStateManager.cpp
               test_TaskManager.cpp
               mocks/mocks.cpp
)

# List the link directories
xmake_link_directories(ATHENA_FRAMEWORK)

# Create and link the executable
add_executable(UnitTests-Athena-Framework ${SRCS})

xmake_target_link_libraries(UnitTests-Athena-Framework UNITTEST_CPP)
xmake_target_link_libraries(UnitTests-Athena-Framework ATHENA_FRAMEWORK)

# Set the RPATH
if (APPLE)
    set_target_properties(UnitTests-Athena-Framework PROPERTIES LINK_FLAGS "-Wl,-rpath,@loader_path/.")
elseif (UNIX)
    set_target_properties(UnitTests-Athena-Framework PROPERTIES INSTALL_RPATH ".")
endif()

# Run the unit tests
get_property(PATH TARGET UnitTests-Athena-Framework PROPERTY RUNTIME_OUTPUT_DIRECTORY)
add_custom_target(Run-UnitTests-Athena-Framework ALL UnitTests-Athena-Framework DEPENDS UnitTests-Athena-Framework WORKING_DIRECTORY ${PATH} COMMENT "Unit testing: Athena-Framework..." VERBATIM)
