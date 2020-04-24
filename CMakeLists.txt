cmake_minimum_required(VERSION 3.15)
project(OpenGLWithCherno)

	set(SOURCES main.cpp)

	SET(CMAKE_PREFIX_PATH 
		"C:/GLEW/GLEW/include"
		"C:/dev/lib/cmake/glfw3/"
		"C:/GLEW/GLEW/lib/Release/x64/"
	)
	
	SET(CMAKE_LIBRARY_PATH
		"C:/GLEW/GLEW/lib/Release/x64/"
		"C:/dev/lib/" 
	)

	SET(GLEW_USE_STATIC_LIBS 1)
	SET(GLEW_VERBOSE 1)
	find_package(GLEW REQUIRED)
	
	find_package(OpenGL REQUIRED)
	find_package(glfw3 CONFIG REQUIRED)

	add_executable(ExampleOpenGL ${SOURCES})
	set_target_properties(ExampleOpenGL PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
	)

	target_link_libraries(ExampleOpenGL
		PRIVATE 
		glfw 
		OpenGL::GL
		GLEW::GLEW
	)

	target_compile_definitions(ExampleOpenGL PRIVATE GLEW_STATIC)
	
	foreach(var IN LISTS CMAKE_PREFIX_PATH)
		message(STATUS "----->${var}")
	endforeach()