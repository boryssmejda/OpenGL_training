#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include "GL/glew.h"

class Rectangle
{
	unsigned int m_VAO, m_VBO;
	unsigned int m_shaderID;

    float m_rectangle[18] = {
        0.0f,  0.5f,   0.0f,    // first left
        0.0f,  -0.5f,   0.0f,    // first middle
        0.5f,   -0.5f,   0.0f,    // first right

        0.0f,  0.5f,   0.0f,    // second left
        0.5f,   0.5f,   0.0f,    // second middle
        0.5f,  -0.5f,  0.0f     // second right
    };


public:
    Rectangle();
    ~Rectangle();

    void setShader(int t_shaderID);
    void draw();
};


#endif // !_RECTANGLE_HPP_

