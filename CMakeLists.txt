cmake_minimum_required(VERSION 3.12)
project(OpenGLWithCherno)

set(EXEC_NAME ExampleOpenGL)
set(SOURCES main.cpp)
add_executable(${EXEC_NAME} ${SOURCES})
set_target_properties(${EXEC_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw/)

find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} glfw OpenGL::GL)

