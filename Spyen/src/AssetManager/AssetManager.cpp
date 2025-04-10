#include "spypch.h"
#include "AssetManager/AssetManager.h"

namespace Spyen {
	std::unordered_map<std::string, std::shared_ptr<Texture>> AssetManager::m_Textures;
	std::shared_ptr<Texture> AssetManager::m_InvalidTexture;

	void AssetManager::Init()
	{
		SPY_CORE_INFO("Initializing AssetManager");

		//Create some 2x2 checkerboard texture
		m_InvalidTexture = Texture::Create(TextureSpecs{ 2,2, GL_RGBA });		
		uint32_t txData[4] = {
			0xff000000,
			0xfff214fa,
			0xfff214fa,
			0xff000000
		};
		m_InvalidTexture->SetData(&txData, sizeof(txData));
	}

	void AssetManager::LoadTexture(const std::string& name, const std::string& path) {
		SPY_CORE_INFO("Loading Texture: {0} AT {1}", name, path);
		if (m_Textures.find(name) != m_Textures.end()) {
			SPY_CORE_WARN("Texture: {0} already loaded at: {1}!", name, path);
			return;
		}

		auto texture = Texture::Create(path);
		if (!texture) {
			SPY_CORE_ERROR("Texture: {0} failed to load at: {1}!", name, path);
			return;
		}

		m_Textures[name] = texture;
	}
	std::shared_ptr<Texture> AssetManager::GetTexture(const std::string& name)
	{
		if (m_Textures.find(name) == m_Textures.end()) {
			SPY_CORE_ERROR("Failed to get Texture {0}. Defaulted to a fallback texture. Did you load the texture? Also check for typos", name);
			return m_InvalidTexture;
			
		};
		return m_Textures.find(name)->second;
	}
}