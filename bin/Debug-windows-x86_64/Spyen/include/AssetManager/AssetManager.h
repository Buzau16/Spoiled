#pragma once
#pragma warning(push)
#pragma warning(disable: 4251)
#include "Core/Core.h"
#include "Renderer/Texture.h"
#include "Audio/Sound.h"
#include <filesystem>


namespace Spyen {
	class SPYEN_API AssetManager
	{
	public:
		AssetManager() = default;
		~AssetManager() = default;

		static void Init();

		/// <summary>
		/// Loads an asset from a path to memory
		/// </summary>
		/// <param name="name: ">the name that the texture will be saved as</param>
		/// <param name="path: ">the path to the texture</param>
		static void LoadTexture(const std::string& name, const std::string& path);

		/// <summary>
		/// Gets a texture
		/// </summary>
		/// <param name="name: ">the name of the texture prevously loaded</param>
		/// <returns>return a shared_ptr to the texture if its valid</returns>
		static std::shared_ptr<Texture> GetTexture(const std::string& name);

		/// <summary>
		/// Loads a sound from a path to memory
		/// </summary>
		/// <param name="name: ">the name that the sound will be saved as</param>
		/// <param name="path: ">the path to the sound</param>
		static void LoadSound(const std::string& name, const std::string& path);

		/// <summary>
		/// Gets a sound from the map
		/// </summary>
		/// <param name="name: ">the key into the map</param>
		/// <returns>Spyen::Sound</returns>
		static std::shared_ptr<Sound> GetSound(const std::string& name);


		// Used in the Spyen Engine... U can use this in your project but why?
		static void LookForAssetsDirectory();

		// Used in the Spyen Engine... U can use this in your project but why?
		static std::string& GetAssetsDirectory();
	};
}

#pragma warning(pop)
