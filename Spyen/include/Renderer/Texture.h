#pragma once
#include "Core/Core.h"
#include <string>
#include <cstdint>
#include <glm/glm.hpp>
#include "stb_image.h"


namespace Spyen
{
	struct TextureSpecs {
		int32_t Width = 1, Height = 1;
		int32_t BitDepth = 4;
		unsigned int Format = 0x1908;
	};

	class SPYEN_API Texture
	{
	public:
		  Texture(const std::string& path);
		  Texture(const TextureSpecs& specs);
		  ~Texture();
		  void Bind(uint32_t slot = 0) const;
		  void Unbind(uint32_t slot = 0) const;
		  uint32_t GetWidth() const { return m_Specs.Width; }
		  uint32_t GetHeight() const { return m_Specs.Height; }
		  uint32_t GetRendererID() const { return m_RendererID; }

		  void SetData(void* data, uint32_t size);
		  void SetData(void* data, uint32_t size, uint32_t x, uint32_t y, uint32_t xOff, uint32_t yOff);

		  static std::shared_ptr<Texture> Create(const std::string& path);
		  static std::shared_ptr<Texture> Create(const TextureSpecs& specs);

		  bool operator==(const Texture& other) const
		  {
			  return m_RendererID == other.GetRendererID();
		  }

	private:
		TextureSpecs m_Specs;
		uint32_t m_RendererID;
		unsigned int m_InternalFormat, m_DataFormat;
	};
}


