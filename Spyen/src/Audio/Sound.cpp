#include "spypch.h"
#include "Audio/Sound.h"

namespace Spyen {
    Sound::Sound(const std::string& path, ma_engine* engine)
    {
        ma_result result = ma_sound_init_from_file(engine, path.c_str(), MA_SOUND_FLAG_DECODE, NULL, NULL, &m_Sound);
        if (result != MA_SUCCESS) {
            SPY_CORE_ERROR("Failed to load sound at : {0}. Error code : ? ? ? ", path);
            return;
        }
        //SPY_CORE_ASSERT(result == MA_SUCCESS, "Failed to load sound at: {0}. Error code: ???", path);
    }
    void Sound::Play()
    {
        ma_sound_start(&m_Sound);
    }
    void Sound::Stop()
    {
        ma_sound_stop(&m_Sound);
    }
}
