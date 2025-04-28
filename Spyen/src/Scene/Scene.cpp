#include "spypch.h"
#include "Scene/Scene.h"


namespace Spyen {
	void Scene::OnRender()
	{
		for (auto& pair : m_DynamicGameObjects) {
			pair.second->OnRender();
		}
		for (auto& pair : m_StaticGameObjects) {
			pair.second->OnRender();
		}
	}
	void Scene::OnUpdate(Timestep ts)
	{
		for (auto& pair : m_DynamicGameObjects) {
			pair.second->OnUpdate(ts);
		}
	}
}