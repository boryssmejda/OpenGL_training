cmake_minimum_required(VERSION 3.15)
project(OpenGLWithCherno)

	set(SOURCES main.cpp)
	add_executable(ExampleOpenGL ${SOURCES})
	set_target_properties(ExampleOpenGL PROPERTIES
		CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
	)

	add_subdirectory(${CMAKE_SOURCE_DIR}/dependencies/glfw/)



	set(
		CMAKE_PREFIX_PATH 
		"C:/glew-2.1.0-win32/glew-2.1.0"
		"C:/glfw-3.3.2.bin.WIN64/lib-vc2019"
	)
	set(
		CMAKE_LIBRARY_PATH 
		"C:/glew-2.1.0-win32/glew-2.1.0/lib/Release/x64"
		"C:/glfw-3.3.2.bin.WIN64/lib-vc2019"
	)
	find_package(GLEW REQUIRED)
	find_package(OpenGL REQUIRED)

	target_link_libraries(ExampleOpenGL
		PRIVATE 
		glfw 
		OpenGL::GL
		GLEW::GLEW
	)