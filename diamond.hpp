#ifndef _DIAMOND_HPP_
#define _DIAMOND_HPP_

#include <GL/glew.h>

class Diamond
{
	unsigned int m_VAO, m_VBO;
    unsigned int m_shaderID;

    float m_diamond[18] = {
        -0.5f,  0.0f,   0.0f,    // first left
        0.0f,  0.5f,   0.0f,    // first middle
        0.5f,   0.0f,   0.0f,    // first right

        -0.5f,  0.0f,   0.0f,    // second left
        0.0f,  -0.5f,   0.0f,    // second middle
        0.5f,   0.0f,   0.0f     // second right
    };

    enum class RadiusExpansionDirection {
        INCREASING, DECREASING
    };

    RadiusExpansionDirection m_expansionDirection = RadiusExpansionDirection::DECREASING;
    const double m_pi = 3.14159265358979323846;
    const float m_maxRadius = 0.5f;
    const float m_minRadius = 0.05f;
    const float m_radiusDecrement = 0.01f;
    float m_radius = m_maxRadius;
    
    const float angleVelocity = -m_pi;
    const double m_phaseShift[6] = {
        m_pi,
        m_pi/2.0,
        0.0,
        m_pi,
        -m_pi/2.0,
        0.0
    };

    void changeRadius();

public:
    Diamond();
    ~Diamond();

    void draw();
    void update(double t_timeIncrement);
    void setShader(unsigned int t_shaderID);
};

#endif // !_DIAMOND_HPP_


