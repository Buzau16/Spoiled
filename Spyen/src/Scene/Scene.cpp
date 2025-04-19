#include "spypch.h"
#include "Scene.h"


namespace Spyen {
	void Scene::OnRender()
	{
		SPY_CORE_INFO("Current scene object size: {0}", m_StaticGameObjects.size() + m_DynamicGameObjects.size());
		for (auto& obj : m_DynamicGameObjects) {
			obj->OnRender();
		}
		for (auto& obj : m_StaticGameObjects) {
			
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