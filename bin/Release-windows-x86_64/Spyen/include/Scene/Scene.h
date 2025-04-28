#pragma once

#pragma warning(push)
#pragma warning(disable: 4251)
#include "Core/Core.h"
#include "GameObjects/GameObject.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include "Core/WeakPtr.h"



namespace Spyen {
	class SPYEN_API Scene
	{
	public:
		Scene(const char* name) : m_Name(name) {};
		void OnRender();
		void OnUpdate(Timestep ts);
		inline std::string& GetName() { return m_Name; };

		template<typename T, typename... Args>
		void AddObject(const char* name, Args... args) {
			if constexpr (std::is_base_of_v <StaticGameObject, T>) {
				SPY_CORE_INFO("Adding StaticGameObject: {} in scene {}", name, m_Name);
				auto obj = std::make_shared<T>(std::forward<Args>(args)...);
				obj->OnCreate();
				obj->SetName(name);
				m_StaticGameObjects[name] = obj;
			}
			if constexpr (std::is_base_of_v <DynamicGameObject, T>) {
				SPY_CORE_INFO("Adding DynamicGameObject: {} in scene {}", name, m_Name);
				auto obj = std::make_shared<T>(std::forward<Args>(args)...);
				obj->OnCreate();
				obj->SetName(name);
				m_DynamicGameObjects[name] = obj;
			}
		}

		void RemoveObjectByName(const std::string& name) {
			m_StaticGameObjects.erase(name);
			m_DynamicGameObjects.erase(name);
			SPY_CORE_INFO("Deleting Object {}", name);
		}


		Spyen::weak_ptr<GameObject> GetObjectByName(const char* name) {
			if (m_StaticGameObjects.contains(name)) {
				return Spyen::weak_ptr<GameObject>(m_StaticGameObjects[name]);
			}
			if (m_DynamicGameObjects.contains(name)) {
				return Spyen::weak_ptr<GameObject>(m_DynamicGameObjects[name]);
			}

			SPY_CORE_ERROR("Failed to find Object {} in scene {}", name, m_Name );
		}

		static std::shared_ptr<Scene> Create(const char* name) {
			return std::make_shared<Scene>(name);
		}

	private:

		std::unordered_map<std::string, std::shared_ptr<StaticGameObject>> m_StaticGameObjects;
		std::unordered_map<std::string, std::shared_ptr<DynamicGameObject>> m_DynamicGameObjects;
		std::string m_Name;
	};
}

#pragma warning(pop)