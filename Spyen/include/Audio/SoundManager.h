#pragma once
#include <string>
#include "miniaudio/miniaudio.h"
#include "Audio/Sound.h"

// shenanigans
#ifdef PlaySound
#undef PlaySound
#endif

namespace Spyen {
	class SPYEN_API SoundManager {
	public:
		static void Init();
		static void Shutdown();
		
		static std::shared_ptr<Sound> LoadSound(const std::string& path);

		/// <summary>
		/// Plays a sound
		/// </summary>
		/// <param name="name: ">The name of the LOADED sound</param>
		static void PlaySound(const std::string& name);

	private:
		static ma_engine m_Engine;
	};
}