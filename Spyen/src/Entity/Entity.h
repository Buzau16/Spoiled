#pragma once
#include <glm/glm.hpp>
#include "Time/Timestep.h"
#include "Renderer/Texture.h"
#include "AssetManager/AssetManager.h"

namespace Spyen
{
	class Entity
	{
	public:
		Entity() = default;
		virtual ~Entity() = default;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnRender() = 0;

	protected:
		Vector2 m_Position;
		float m_Scale;
		float m_Rotation;
		Color m_Color;
		std::shared_ptr<Texture> m_Texture;
	};
}