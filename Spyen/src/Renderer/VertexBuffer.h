#pragma once
#include "Renderer/BufferLayout.h"

namespace Spyen {

	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, uint32_t size);
		~VertexBuffer();

		void Bind();
		void Unbind();
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
		const BufferLayout& GetLayout() { return m_Layout; };
		static std::shared_ptr<VertexBuffer> Create(const void* data, uint32_t size);
		uint32_t& GetRendererID() { return m_RendererID; };

		void SetData(const void* data, uint32_t size);

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

}
