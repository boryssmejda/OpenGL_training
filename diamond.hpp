#ifndef _DIAMOND_HPP_
#define _DIAMOND_HPP_

#include <GL/glew.h>

class Diamond
{
	unsigned int m_VAO, m_VBO;
    unsigned int m_shaderID;

    float m_diamond[18] = {
        -1.0f,  0.0f,   0.0f,    // first left
        -0.5f,  0.5f,   0.0f,    // first middle
        0.0f,   0.0f,   0.0f,    // first right

        -1.0f,  0.0f,   0.0f,    // second left
        0.0f,   0.0f,   0.0f,    // second middle
        -0.5f,  -0.5f,  0.0f     // second right
    };
public:
    Diamond();
    ~Diamond();

    void draw();
    void update();
    void setShader(unsigned int t_shaderID);
};

#endif // !_DIAMOND_HPP_


