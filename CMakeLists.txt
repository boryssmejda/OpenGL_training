cmake_minimum_required(VERSION 3.12)
project(OpenGLWithCherno)

#set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}")
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR}")
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})


set(EXEC_NAME ExampleOpenGL)
set(SOURCES main.cpp)
add_executable(${EXEC_NAME} ${SOURCES})

find_package(glfw CONFIG)
find_package(OpenGL REQUIRED)

#target_link_libraries(${EXEC_NAME} glfw::glfw OpenGL::GL)
target_link_libraries(${EXEC_NAME} glfw::glfw OpenGL::OpenGL OpenGL::EGL)
