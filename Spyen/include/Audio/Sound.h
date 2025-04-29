#pragma once
#include <miniaudio/miniaudio.h>

namespace Spyen {
	class Sound
	{
	public:
		Sound() = default;
		Sound(const std::string& path);
		~Sound() {
			ma_sound_uninit(&m_Sound);
		}
	private:
		ma_sound m_Sound;
		ma_decoder m_Decoder;
	};

}
