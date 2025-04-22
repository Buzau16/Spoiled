#pragma once
#include "Time/Timestep.h"
#include "Renderer/Texture.h"
#include "AssetManager/AssetManager.h"
#include "GameObject.h"

namespace Spyen {
	class SPYEN_API StaticGameObject : public GameObject
	{
	public:
		StaticGameObject() = default;
		virtual ~StaticGameObject() = default;
		virtual void OnRender() = 0;
		virtual void OnCreate() = 0;
	};
}


