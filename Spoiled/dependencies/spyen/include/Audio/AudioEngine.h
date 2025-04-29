#pragma once
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

namespace Spyen {
	struct Sound {
		std::filesystem::path m_SoundPath;

	};

	class AudioEngine
	{
	public:

		static void Init();
		static void PlaySound(std::shared_ptr<Sound> sound);
		static void Shutdown();

	private:
		static ma_result m_Result;
		static ma_engine m_Engine;
		static ma_decoder m_Decoder;

	};

}

