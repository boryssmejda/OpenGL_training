#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
private:
	unsigned int m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

#endif // !VERTEX_ARRAY_HPP
