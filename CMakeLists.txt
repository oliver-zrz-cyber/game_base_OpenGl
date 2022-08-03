cmake_minimum_required(VERSION 3.21)
project(open_gl_install)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_OSX_ARCHITECTURES  "arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)

set(LOCAL_H /opt/homebrew/include)
include_directories(${LOCAL_H})

set(GLEW_H /opt/homebrew/Cellar/glew/2.2.0_1/include/GL)
set(GLFW_H /opt/homebrew/Cellar/glfw/3.3.7/include/GLFW)
set(ASSIMP_H /opt/homebrew/Cellar/assimp/5.2.3/include/assimp)
link_directories(${GLEW_H} ${GLFW_H} ${ASSIMP_H})

set(GLEW_LINK /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
set(GLFW_LINK /opt/homebrew/Cellar/glfw/3.3.7/lib/libglfw.3.dylib)
set(ASSIMP_LINK /opt/homebrew/Cellar/assimp/5.2.3/lib/libassimp.5.2.0.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK} ${ASSIMP_LINK})

add_executable(OpenGL glad.c main.cpp shader.h)

if (APPLE)
    target_link_libraries(OpenGL "-framework OpenGL")
    target_link_libraries(OpenGL "-framework GLUT")
endif ()