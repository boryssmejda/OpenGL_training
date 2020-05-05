#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GL/glew.h>
class IndexBuffer;
class VertexArray;
class Shader;

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:

    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};


#endif // !RENDERER_HPP



