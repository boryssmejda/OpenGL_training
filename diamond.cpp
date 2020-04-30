#include "diamond.hpp"
#include <iostream>
#include <cmath>

void Diamond::changeRadius()
{
	if (m_expansionDirection == RadiusExpansionDirection::DECREASING)
	{
		m_radius -= m_radiusDecrement;
		if (m_radius < m_minRadius)
		{
			m_radius = m_minRadius;
			m_expansionDirection = RadiusExpansionDirection::INCREASING;
		}
	}
	else
	{
		m_radius += m_radiusDecrement;
		if (m_radius > m_maxRadius)
		{
			m_radius = m_maxRadius;
			m_expansionDirection = RadiusExpansionDirection::DECREASING;
		}
	}
}

Diamond::Diamond()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_diamond), m_diamond, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Diamond::~Diamond()
{
	std::cout << "Freeing resources for diamond\n";
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteProgram(m_shaderID);
}

void Diamond::draw()
{
	glUseProgram(m_shaderID);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	//glBindVertexArray(0);
}

void Diamond::update(double t_timeIncrement)
{
	static double currentTime;

	changeRadius();

	for (int i = 0; i < 6; ++i)
	{
		double currentAngle = angleVelocity * currentTime + m_phaseShift[i];
		//currentAngle = (currentAngle > 2 * m_pi ? 0.0 : currentAngle);

		m_diamond[3 * i] = m_radius * std::cos(currentAngle);
		m_diamond[3 * i + 1] = m_radius * std::sin(currentAngle);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_diamond), m_diamond, GL_DYNAMIC_DRAW);

	currentTime += t_timeIncrement;
}

void Diamond::setShader(unsigned int t_shaderID)
{
	m_shaderID = t_shaderID;
}
