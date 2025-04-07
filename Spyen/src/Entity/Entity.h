#pragma once
#include <glm/glm.hpp>
#include "Time/Timestep.h"

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
	};
}