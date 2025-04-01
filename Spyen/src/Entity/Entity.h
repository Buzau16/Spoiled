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
		float m_X, m_Y;
		float m_Scale;
		float m_Rotation;
		Color m_Color;
	};
}