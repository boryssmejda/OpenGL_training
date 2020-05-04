#include "Renderer.hpp"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << std::hex << error << ")" << std::dec << std::endl;
        std::cout << "Error observed in " << function << " " << file << " : " << line << '\n';
        return false;
    }
    return true;
}