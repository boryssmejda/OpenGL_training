#include "rectangle.hpp"

Rectangle::Rectangle()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_rectangle), m_rectangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

Rectangle::~Rectangle()
{
	glDeleteProgram(m_shaderID);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void Rectangle::setShader(int t_shaderID)
{
	m_shaderID = t_shaderID;
}

void Rectangle::draw()
{
	glBindVertexArray(m_VAO);
	glUseProgram(m_shaderID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
