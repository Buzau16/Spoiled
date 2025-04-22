#pragma once
#include "Renderer/BufferLayout.h"

namespace Spyen {
	class SPYEN_API VertexBuffer
	{
	public:
		VertexBuffer(const void* data, uint32_t size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;
		void SetData(const void* data, uint32_t size);
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
		const BufferLayout& GetLayout() const { return m_Layout; };
		uint32_t& GetRendererID() { return m_RendererID; }

		static std::shared_ptr<VertexBuffer> Create(const void* data, uint32_t size);
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

}