#pragma once
#include "GameObjects/StaticGameObject.h"
#include "GameObjects/DynamicGameObject.h"
#include "Renderer/Renderer.h"

namespace Spyen {
	class Scene
	{
	public:
		void OnRender();
		void OnUpdate(Timestep ts);
		void AddObject(std::unique_ptr<StaticGameObject> obj);
		void AddObject(std::unique_ptr<DynamicGameObject> obj);

	private:
		std::vector<std::unique_ptr<StaticGameObject>> m_StaticGameObjects;
		std::vector<std::unique_ptr<DynamicGameObject>> m_DynamicGameObjects;
	};
}

