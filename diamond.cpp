#include "diamond.hpp"
#include <iostream>

Diamond::Diamond()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_diamond), m_diamond, GL_STATIC_DRAW);

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

void Diamond::update()
{
}

void Diamond::setShader(unsigned int t_shaderID)
{
	m_shaderID = t_shaderID;
}
