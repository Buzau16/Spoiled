#pragma once
#include <glm/glm.hpp>
#include "Time/Timestep.h"
#include "Renderer/Texture.h"
#include "AssetManager/AssetManager.h"


namespace Spyen {
	class StaticGameObject
	{
	public:
		StaticGameObject() = default;
		virtual ~StaticGameObject() = default;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnRender() = 0;

		/////// Getters
		Vector2 GetPosition() const { return m_Position; };
		float GetRotation() const { return m_Rotation; };
		float GetScale() const { return m_Scale; };
		Color GetColor() const { return m_Color; };
		std::shared_ptr<Texture> GetTexture() const { return m_Texture; };


	protected:

		Vector2 m_Position;
		float m_Rotation;
		float m_Scale;
		Color m_Color;
		std::shared_ptr<Texture> m_Texture = nullptr;
	};
}


