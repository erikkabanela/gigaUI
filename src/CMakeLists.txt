cmake_minimum_required(VERSION 3.20)
project(gigaUI C)

# Set C standard
set(CMAKE_C_STANDARD 17)

# Add source files
set(SOURCES
    main.c
    ../src/windows_helpers.c
    ../src/gigabutton.c
    ../src/gigatext.c
    ../src/gigaradiobutton.c
    ../src/gigacheckbox.c
    ../src/gigaslider.c
    ../src/gigatoggleswitch.c
    ../src/cjson/cJSON.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

if(WIN32)
	include_directories(${PROJECT_SOURCE_DIR}/../include)
	link_directories(${PROJECT_SOURCE_DIR}/../lib) # optional, not needed

    find_library(RAYLIB_LIB raylib PATHS "${PROJECT_SOURCE_DIR}/../lib" NO_DEFAULT_PATH)
    message(STATUS "Raylib found at: ${RAYLIB_LIB}")

    target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIB} opengl32 gdi32 winmm dwmapi)

elseif(UNIX)
    find_package(raylib REQUIRED)

	#include_directories(${PROJECT_SOURCE_DIR}/../include)
    #link_directories(${PROJECT_SOURCE_DIR}/../lib)

    target_link_libraries(${PROJECT_NAME} raylib m GL X11 pthread dl rt)
endif()