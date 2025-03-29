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

    void VertexArray::BindVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer)
    {
					glBindVertexArray(m_RendererID);
					vertexbuffer->Bind();

					const auto& layout = vertexbuffer->GetLayout();
					for (const auto& element : layout) {
						uint8_t count = 0;
						switch (element.Type)
						{
						case ShaderDataType::Float:  
						case ShaderDataType::Float2: 
						case ShaderDataType::Float3: 
						case ShaderDataType::Float4:
							glEnableVertexAttribArray(m_VertexBufferIndex);
							glVertexAttribPointer(m_VertexBufferIndex, 
								element.GetComponentCount(),
								SpyenShaderDataTypeToGltype(element.Type),
								element.Normalized ? GL_TRUE : GL_FALSE,
								layout.GetStride(),
								(const void*)element.Offset);
							m_VertexBufferIndex++;
							break;
						case ShaderDataType::Int:    
						case ShaderDataType::Int2:   
						case ShaderDataType::Int3:   
						case ShaderDataType::Int4:   
						case ShaderDataType::Bool: 
							glEnableVertexAttribArray(m_VertexBufferIndex);
							glVertexAttribIPointer(m_VertexBufferIndex,
								element.GetComponentCount(),
								SpyenShaderDataTypeToGltype(element.Type),
								layout.GetStride(),
								(const void*)element.Offset);
							m_VertexBufferIndex++;
							break;
						case ShaderDataType::Mat4:
							count = element.GetComponentCount();
							for (uint8_t i = 0; i < count; i++)
							{
								glEnableVertexAttribArray(m_VertexBufferIndex);
								glVertexAttribPointer(m_VertexBufferIndex,
									count,
									SpyenShaderDataTypeToGltype(element.Type),
									element.Normalized ? GL_TRUE : GL_FALSE,
									layout.GetStride(),
									(const void*)(element.Offset + sizeof(float) * count * i));
								glVertexAttribDivisor(m_VertexBufferIndex, 1);
								m_VertexBufferIndex++;
							}
							break;
						default:
							assert(false && "Unkown ShaderDataType!");
						}
					}
		m_VertexBuffers.push_back(vertexbuffer);
    }

	void VertexArray::BindIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer)
	{
		glBindVertexArray(m_RendererID);
		indexbuffer->Bind();

		m_IndexBuffer = indexbuffer;
	}

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		return std::make_shared<VertexArray>();
	}

}
