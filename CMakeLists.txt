cmake_minimum_required(VERSION 3.15)
project(OpenGLWithCherno)

	set(SOURCES 
        main.cpp
        src/debugHelper.cpp
        src/Shader.cpp
        stb_image.cpp
    )
    
    set(HEADERS
        include/debugHelper.hpp
        include/Shader.hpp
        stb_image.h
    )
	
	if (MSVC)
		set(GLEW_USE_STATIC_LIBS 1)
	endif (MSVC)
	
	find_package(GLEW REQUIRED)
	find_package(OpenGL REQUIRED)
	find_package(glfw3 CONFIG REQUIRED)

	add_executable(ExampleOpenGL ${SOURCES} ${HEADERS})
	set_target_properties(ExampleOpenGL PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
	)
    
    target_include_directories(ExampleOpenGL 
        PRIVATE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
    )
    
    
	target_link_libraries(ExampleOpenGL
		PRIVATE 
		glfw 
		OpenGL::GL
		GLEW::GLEW
	)

	target_compile_definitions(ExampleOpenGL PRIVATE GLEW_STATIC)
    