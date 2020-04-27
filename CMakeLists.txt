cmake_minimum_required(VERSION 3.15)
project(OpenGLWithCherno)

	set(SOURCES main.cpp)
	
	if (MSVC)
		set(GLEW_USE_STATIC_LIBS 1)
	endif (MSVC)
	
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