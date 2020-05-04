#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

#endif // !VERTEX_BUFFER_HPP
