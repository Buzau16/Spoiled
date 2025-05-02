#include "spypch.h"
#define MINIAUDIO_IMPLEMENTATION
#include "Audio/SoundManager.h"
#include "AssetManager/AssetManager.h"
#include <memory>


namespace Spyen {
	ma_engine SoundManager::m_Engine;

	void SoundManager::Init()
	{
		SPY_CORE_INFO("Initializing the SoundManager");
		ma_result res = ma_engine_init(NULL, &m_Engine);
		SPY_CORE_ASSERT(res == MA_SUCCESS, "Failed to intialize audio engine");

	}
	void SoundManager::Shutdown()
	{
		ma_engine_uninit(&m_Engine);
	}
	std::shared_ptr<Sound> SoundManager::LoadSound(const std::string& path)
	{
		return Sound::Create(path, &m_Engine);
	}
	void SoundManager::PlaySound(const std::string& name)
	{
		auto sound = AssetManager::GetSound(name);
		sound->Play();
	}
}