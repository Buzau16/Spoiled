#include "spypch.h"
#include "IndexBuffer.h"

namespace Spyen {
	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_STATIC_DRAW);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "Error in IndexBuffer creation: " << error << std::endl;
		}
	}
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::cout << "Error in IndexBuffer bind: " << error << std::endl;
		}
	}
	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		return std::make_shared<IndexBuffer>(indices, count);
	}
}
