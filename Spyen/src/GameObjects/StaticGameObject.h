#pragma once
#include <glm/glm.hpp>
#include "Time/Timestep.h"
#include "Renderer/Texture.h"
#include "AssetManager/AssetManager.h"
#include "GameObject.h"

namespace Spyen {
	class StaticGameObject : public GameObject
	{
	public:
		StaticGameObject() = default;
		virtual ~StaticGameObject() = default;
		virtual void OnRender() = 0;
		virtual void OnCreate() = 0;
	};
}


