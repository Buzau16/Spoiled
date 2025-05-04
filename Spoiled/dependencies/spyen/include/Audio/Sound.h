#pragma once
#include "Core/Core.h"
#include <miniaudio/miniaudio.h>
#include <string>



namespace Spyen {
	/// <summary>
	/// Basic sound interface. NOT TO BE USED DIRECTLY!
	/// </summary>
	class SPYEN_API Sound
	{
	public:
		Sound() = default;
		Sound(const std::string& path, ma_engine* engine);
		~Sound() {
			ma_sound_uninit(&m_Sound);
			Stop();
		}

		void Play();
		void Stop();

		static std::shared_ptr<Sound> Create(const std::string& path, ma_engine* m_Engine) {
			return std::make_shared<Sound>(path, m_Engine);
		};

	private:
		ma_sound m_Sound;
	};

}
