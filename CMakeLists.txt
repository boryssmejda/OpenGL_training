cmake_minimum_required(VERSION 3.2)
project(OpenGLWithCherno)

set(SOURCES main.cpp)
add_executable(ExamplepenGL ${SOURCES})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

message("${CONAN_LIBS}")
target_link_libraries(ExamplepenGL ${CONAN_LIBS})
target_link_libraries(ExamplepenGL OpenGL::GL)