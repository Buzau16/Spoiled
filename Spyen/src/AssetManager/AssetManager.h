#pragma once
#include "Renderer/Texture.h"

namespace Spyen {
	class AssetManager
	{
	public:
		AssetManager() = default;
		~AssetManager() = default;

		static void Init();

		template<typename T>
		static void Load(const std::string& name, const std::string& path)
		{
			if (std::is_same_v<T, Texture>) {
				LoadTexture(name, path);
				return;
			}
			
			SPY_CORE_ERROR("Error in Spyen::AssetManager::Load: Template argument not valid!");
		}

		template<typename T>
		static std::shared_ptr<T> Get(const std::string& name) {
			if (std::is_same_v< T, Texture>) {
				return GetTexture(name);
			}
			SPY_CORE_CRITICAL("Error in Spyen::AssetManager::Get. Template arugument not valid!");
		}

	private:
		static void LoadTexture(const std::string& name, const std::string& path);
		static std::shared_ptr<Texture> GetTexture(const std::string& name);
		static std::shared_ptr<Texture> m_InvalidTexture;

		static std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
	};
}
