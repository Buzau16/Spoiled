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
		void AddObject(const std::shared_ptr<StaticGameObject>& obj);
		void AddObject(const std::shared_ptr<DynamicGameObject>& obj);

	private:
		std::vector<std::shared_ptr<StaticGameObject>> m_StaticGameObjects;
		std::vector<std::shared_ptr<DynamicGameObject>> m_DynamicGameObjects;
	};
}

