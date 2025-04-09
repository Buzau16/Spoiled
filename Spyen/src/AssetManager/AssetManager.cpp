#include "spypch.h"
#include "AssetManager/AssetManager.h"

namespace Spyen {
	std::unordered_map<std::string, std::shared_ptr<Texture>> AssetManager::m_Textures;
	std::shared_ptr<Texture> AssetManager::m_InvalidTexture;

	void AssetManager::Init()
	{
		SPY_CORE_INFO("Initializing AssetManager");

		m_InvalidTexture = Texture::Create(TextureSpecs{ 1,1, GL_RGBA });
		uint32_t invalidtx = 0xfff705f3;
		m_InvalidTexture->SetData(&invalidtx, sizeof(uint32_t));
	}

	void AssetManager::LoadTexture(const std::string& name, const std::string& path) {
		if (m_Textures.find(name) != m_Textures.end()) {
			SPY_CORE_ERROR("Texture: {0} already loaded at: {1}!", name, path);
			return;
		}

		auto texture = Texture::Create(path);
		if (!texture) {
			SPY_CORE_WARN("Texture: {0} failed to load at: {1}!", name, path);
			return;
		}

		m_Textures[name] = texture;
	}
	std::shared_ptr<Texture> AssetManager::GetTexture(const std::string& name)
	{
		if (m_Textures.find(name) == m_Textures.end()) {
			SPY_CORE_ERROR("Failed to get Texture {0}. Defaulted to invalid texture", name);
			return m_InvalidTexture;
			
		};
		return m_Textures.find(name)->second;
	}
}