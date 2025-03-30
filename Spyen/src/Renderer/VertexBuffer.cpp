#include "spypch.h"
#include "VertexBuffer.h"

namespace Spyen {
	VertexBuffer::VertexBuffer(const void* data, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "Error in VertexBuffer creation: " << error << std::endl;
		}
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void VertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "Error in SetData: " << error << std::endl;
		}
	}
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
	{
		return std::make_shared<VertexBuffer>(data, size);
	}
}