#include "spypch.h"
#include "Renderer/VertexBuffer.h"

namespace Spyen {
	VertexBuffer::VertexBuffer(const void* data, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

		GLenum error = glGetError();
		SPY_CORE_ASSERT(error == GL_NO_ERROR, "Failed to create vertex buffer. With error code {0}", error);
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
		SPY_CORE_ASSERT(error == GL_NO_ERROR, "Failed to set data to vertex buffer. With error code {0}", error);
	}
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size)
	{
		return std::make_shared<VertexBuffer>(data, size);
	}
}