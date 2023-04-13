MESSAGE("FINDING HAGAME2 LIB")
# set(CMAKE_FIND_DEBUG_MODE TRUE)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
# The places to look for the tinyxml2 folders

set(
        FIND_HAGAME2_PATHS
        /home/henry/development/games/HaGameLite
)

find_path(
        HAGAME2_INCLUDE_DIR hagame.h
        PATH_SUFFIXES include
        PATHS ${FIND_HAGAME2_PATHS}
)
if(EMSCRIPTEN)
    MESSAGE("EMSCRIPTEN")
    find_library(HAGAME2_LIBRARY
            NAMES HaGame2
            PATH_SUFFIXES wasm
            PATHS ${FIND_HAGAME2_PATHS}
            )
else()
    MESSAGE("UNIX")
    find_library(HAGAME2_LIBRARY
            NAMES HaGame2
            PATH_SUFFIXES lib
            PATHS ${FIND_HAGAME2_PATHS}
            )
endif()

MESSAGE("${FIND_HAGAME2_PATHS}/thirdparty/box2d/build/bin/")

find_library(BOX2D_LIBRARY
        NAMES box2d
        PATH_SUFFIXES lib
        PATHS ${FIND_HAGAME2_PATHS}/thirdparty/box2d/build/bin/
        )

# add_subdirectory(${FIND_HAGAME2_PATHS}/thirdparty/box2d/)

include_directories("${FIND_HAGAME2_PATHS}/thirdparty/entt/src/")
include_directories("${FIND_HAGAME2_PATHS}/thirdparty/box2d/include/")

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

MESSAGE("FIND_HAGAME2_PATHS = ${FIND_HAGAME2_PATHS}")
MESSAGE("HAGAME2_INCLUDE_DIR = ${HAGAME2_INCLUDE_DIR}")
MESSAGE("HAGAME2_LIBRARY = ${HAGAME2_LIBRARY}")
MESSAGE("BOX2D_LIBRARY = ${BOX2D_LIBRARY}")