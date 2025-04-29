#include "spypch.h"
#include "Audio/AudioEngine.h"

namespace Spyen {
	ma_result AudioEngine::m_Result;
	ma_engine AudioEngine::m_Engine;
	ma_decoder AudioEngine::m_Decoder;

	
	void AudioEngine::Init()
	{
		m_Result = ma_engine_init(NULL, &m_Engine);
		if (m_Result != MA_SUCCESS) {
			//SPY_CORE_CRITICAL("Failed to initilize the audio engine: {}", m_Result);
		}
	}
	void AudioEngine::Shutdown()
	{
		ma_engine_uninit(&m_Engine);
	}
}
