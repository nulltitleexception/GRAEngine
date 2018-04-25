cmake_minimum_required(VERSION 3.6)
project(grae-engine)

if (WIN32)
    add_definitions(-D_WIN32)
    remove_definitions(-D_UNIX)
else()
    add_definitions(-D_UNIX)
    remove_definitions(-D_WIN32)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(GLFW_DIR C:/glfw-3.2.1)
set(GLAD_DIR C:/GLAD)
set(DEVIL_DIR C:/DevIL)

set(GRAE_HEADERS src)

include_directories(${GLFW_DIR}/include ${GLAD_DIR}/include ${DEVIL_DIR}/include ${GRAE_HEADERS})
link_directories(${GLFW_DIR}/lib ${DEVIL_DIR}/lib/x64/Release)

set(GLAD_FILES ${GLAD_DIR}/include/glad/glad.h ${GLAD_DIR}/include/KHR/khrplatform.h ${GLAD_DIR}/src/glad.c)
set(GLFW_FILES ${GLFW_DIR}/include/GLFW/glfw3.h)
set(DEVIL_FILES ${DEVIL_DIR}/include/IL/il.h)

set(INCLUDED_FILES ${GLFW_FILES} ${GLAD_FILES} ${DEVIL_FILES})

file(GLOB_RECURSE GRAE_SRC "src/*")
set(SOURCE_FILES ${GRAE_SRC})

add_library(grae-engine SHARED ${SOURCE_FILES} ${INCLUDED_FILES})
SET_TARGET_PROPERTIES(grae-engine PROPERTIES PREFIX "")
find_library(WS2_32_LIBRARY ws2_32)
target_link_libraries(grae-engine glfw3dll DevIL ws2_32)
target_compile_definitions(grae-engine PRIVATE)

INSTALL(
        TARGETS grae-engine
        DESTINATION ${CMAKE_SOURCE_DIR}/lib
)

INSTALL (
        DIRECTORY ${CMAKE_SOURCE_DIR}/src/
        DESTINATION ${CMAKE_SOURCE_DIR}/include
        FILES_MATCHING PATTERN "*.h*"
)

INSTALL (
        DIRECTORY ${GLFW_DIR}/lib/
        DESTINATION ${CMAKE_SOURCE_DIR}/lib
        FILES_MATCHING PATTERN "*.dll*"
)
INSTALL (
        DIRECTORY ${DEVIL_DIR}/lib/x64/Release/
        DESTINATION ${CMAKE_SOURCE_DIR}/lib
        FILES_MATCHING PATTERN "*.dll*"
)

INSTALL (
        DIRECTORY ${GLFW_DIR}/include/
        DESTINATION ${CMAKE_SOURCE_DIR}/include
        FILES_MATCHING PATTERN "*.h*"
)

INSTALL (
        DIRECTORY ${GLAD_DIR}/include/
        DESTINATION ${CMAKE_SOURCE_DIR}/include
        FILES_MATCHING PATTERN "*.h"
)

add_custom_target(
        install_${PROJECT_NAME}
        "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}"
)