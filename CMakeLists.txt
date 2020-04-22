cmake_minimum_required(VERSION 3.12)
project(OpenGLWithCherno)

#set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}")
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR}")
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})


set(SOURCES main.cpp)
add_executable(ExamplepenGL ${SOURCES})

find_package(glfw CONFIG)
find_package(OpenGL REQUIRED)

target_link_libraries(ExamplepenGL glfw::glfw OpenGL::GL)
