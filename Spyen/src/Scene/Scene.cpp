#include "spypch.h"
#include "Scene.h"


namespace Spyen {
	void Scene::OnRender()
	{
		SPY_CORE_INFO("static obj size: {0}", m_StaticGameObjects.size());
		for (auto& obj : m_StaticGameObjects) {
			SPY_CORE_INFO("Rendering static obj");
			obj->OnRender();
		}

		for (auto& obj : m_DynamicGameObjects) {
			SPY_CORE_INFO("Rendering dinamic obj");
			obj->OnRender();
		}
	}
	void Scene::OnUpdate(Timestep ts)
	{
		for (auto& obj : m_DynamicGameObjects) {
			obj->OnUpdate(ts);
		}
	}
	void Scene::AddObject(const std::shared_ptr<StaticGameObject>& obj)
	{
		obj->OnCreate();
		m_StaticGameObjects.push_back(obj);
	}

	void Scene::AddObject(const std::shared_ptr<DynamicGameObject>& obj)
	{
		obj->OnCreate(); 
		m_DynamicGameObjects.push_back(obj);
	}
}