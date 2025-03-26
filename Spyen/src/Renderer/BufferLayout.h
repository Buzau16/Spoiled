#pragma once
#include "Renderer/BufferElement.h"
#include <vector>

namespace Spyen {
	class BufferLayout
	{
	public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : m_Elements(elements) {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        inline uint32_t GetStride() const { return m_Stride; }

    private:
        void CalculateOffsetsAndStride() {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }

        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
	};
}

