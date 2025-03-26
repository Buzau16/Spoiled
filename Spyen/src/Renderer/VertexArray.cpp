#include "spypch.h"
#include "VertexArray.h"

namespace Spyen {

	static GLenum SpyenShaderDataTypeToGltype(ShaderDataType type) {
		switch (type)
		{
		case Spyen::ShaderDataType::Float:		return GL_FLOAT;
		case Spyen::ShaderDataType::Float2:		return GL_FLOAT;
		case Spyen::ShaderDataType::Float3:		return GL_FLOAT;
		case Spyen::ShaderDataType::Float4:		return GL_FLOAT;
		case Spyen::ShaderDataType::Mat4:		return GL_FLOAT;
		case Spyen::ShaderDataType::Int:		return GL_INT;
		case Spyen::ShaderDataType::Int2:		return GL_INT;
		case Spyen::ShaderDataType::Int3:		return GL_INT;
		case Spyen::ShaderDataType::Int4:		return GL_INT;
		case Spyen::ShaderDataType::Bool:		return GL_BOOL;

		}
	}

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::BindVertexBuffer(const std::unique_ptr<VertexBuffer>& vertexbuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexbuffer->Bind();

	}

}
