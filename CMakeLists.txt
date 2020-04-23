cmake_minimum_required(VERSION 3.15)
project(OpenGLWithCherno)

	foreach(path ${CMAKE_PREFIX_PATH})
		message(STATUS "${path}")
	endforeach()

	foreach(path ${CMAKE_LIBRARY_PATH})
		message(STATUS "${path}")
	endforeach()

	set(SOURCES main.cpp)
	
	message("----->>> ${CMAKE_PREFIX_PATH}")
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