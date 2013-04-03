project(ATHENA_DEMO_OGRE_HEAD)


# List the source files
set(SRCS "${ATHENA_DEMO_OGRE_HEAD_SOURCE_DIR}/MainGameState.cpp"
)

# List the header files
set(HEADERS "${ATHENA_DEMO_OGRE_HEAD_SOURCE_DIR}/MainGameState.h"
)

create_demo_created_window(ATHENA_DEMO_OGRE_HEAD Athena-Demo-OgreHead "${SRCS}" "${HEADERS}"
                           "${ATHENA_DEMO_OGRE_HEAD_SOURCE_DIR}")

create_demo_external_window(ATHENA_DEMO_OGRE_HEAD Athena-Demo-OgreHead "${SRCS}" "${HEADERS}"
                            "${ATHENA_DEMO_OGRE_HEAD_SOURCE_DIR}")
