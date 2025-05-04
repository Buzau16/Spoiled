#include "spypch.h"
#include "AssetManager/AssetManager.h"
#include "Audio/SoundManager.h"

namespace Spyen {
	struct AssetManagerData
	{
		std::shared_ptr<Texture> InvalidTexture;
		std::string ShadersPath;

		std::unordered_map<std::string, std::shared_ptr<Texture>> Textures;
		std::unordered_map<std::string, std::shared_ptr<Sound>> Sounds;
	};

	static AssetManagerData s_Data;

	void AssetManager::Init()
	{
		SPY_CORE_INFO("Initializing AssetManager");

		//Create some 2x2 checkerboard texture
		s_Data.InvalidTexture = Texture::Create(TextureSpecs{ 2,2, GL_RGBA });
		uint32_t txData[4] = {
			0xff000000,
			0xfff214fa,
			0xfff214fa,
			0xff000000
		};
		s_Data.InvalidTexture->SetData(&txData, sizeof(txData));

	}

	void AssetManager::LoadSound(const std::string& name, const std::string& path)
	{
		SPY_CORE_INFO("Loading sound {0} AT {1}", name, path);
		if (s_Data.Sounds.find(name) != s_Data.Sounds.end()) {
			SPY_CORE_WARN("Sound: {0} already loaded at: {1}!", name, path);
			return;
		}

		s_Data.Sounds[name] = SoundManager::LoadSound(path);
	}

	std::shared_ptr<Sound> AssetManager::GetSound(const std::string& name)
	{
		if (!s_Data.Sounds.contains(name)) {
			SPY_CORE_INFO("Failed to find sound: {0}. Check if the sound is loaded and for any typos!", name);
			throw std::runtime_error("Sound not found: " + name);;
		}
		return s_Data.Sounds.find(name)->second;
	}

	void AssetManager::LookForAssetsDirectory()
	{
		std::filesystem::path startPath = std::filesystem::current_path();

		for (const auto& entry : std::filesystem::recursive_directory_iterator(startPath)) {
			if (entry.is_directory() && entry.path().filename() == "spyen") {
				s_Data.ShadersPath = entry.path().string() + "/shaders";
			}
		}
	}

	std::string& AssetManager::GetAssetsDirectory()
	{
		return s_Data.ShadersPath;
	}

	void AssetManager::LoadTexture(const std::string& name, const std::string& path) {
		SPY_CORE_INFO("Loading Texture: {0} AT {1}", name, path);
		if (s_Data.Textures.find(name) != s_Data.Textures.end()) {
			SPY_CORE_WARN("Texture: {0} already loaded at: {1}!", name, path);
			return;
		}

		auto texture = Texture::Create(path);
		if (!texture) {
			SPY_CORE_ERROR("Texture: {0} failed to load at: {1}!", name, path);
			return;
		}

		s_Data.Textures[name] = texture;
	}
	std::shared_ptr<Texture> AssetManager::GetTexture(const std::string& name)
	{
		if (s_Data.Textures.find(name) == s_Data.Textures.end()) {
			SPY_CORE_ERROR("Failed to get Texture {0}. Defaulted to a fallback texture. Did you load the texture? Also check for typos", name);
			return s_Data.InvalidTexture;
			
		};
		return s_Data.Textures.find(name)->second;
	}
}