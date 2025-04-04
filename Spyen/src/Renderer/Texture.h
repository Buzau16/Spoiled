#pragma once
#include <string>
#include <cstdint>
#include <glm/glm.hpp>
#include "stb_image.h"

namespace Spyen
{
	struct TextureSpecs {
		int32_t Width, Height;
		int32_t BitDepth;
		GLenum Format;
	};

	class Texture
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

		  static std::shared_ptr<Texture> Create(const std::string& path);
		  static std::shared_ptr<Texture> Create(const TextureSpecs& specs);

	private:
		TextureSpecs m_Specs;
		uint32_t m_RendererID;
		
	};
}


