#pragma once
#include <glm/glm.hpp>
#include "Time/Timestep.h"
#include "Renderer/Texture.h"
#include "AssetManager/AssetManager.h"
#include "GameObject.h"

namespace Spyen {
	class DynamicGameObject : public GameObject
	{
	public:
		DynamicGameObject() = default;
		virtual ~DynamicGameObject() = default;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnRender() = 0;
		virtual void OnCreate() = 0;

		////////////// Utility Functions //////////////
		void Translate(Vector2 translation) { m_Position += translation; };
		void Translate(float x, float y) { m_Position.x += x; m_Position.y += y; };
		void Rotate(float rotation) { m_Rotation += rotation; };
		void Scale(float scale) { m_Scale += scale; };
	};

}