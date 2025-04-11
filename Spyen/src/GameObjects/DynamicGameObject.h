#pragma once
#include <glm/glm.hpp>
#include "Time/Timestep.h"
#include "Renderer/Texture.h"
#include "AssetManager/AssetManager.h"

namespace Spyen {
	class DynamicGameObject
	{
	public:
		DynamicGameObject() = default;
		virtual ~DynamicGameObject() = default;
		virtual void OnUpdate(Timestep ts) = 0;
		virtual void OnRender() = 0;
		virtual void OnCreate() = 0;

		////////////// Getters //////////////
		Vector2 GetPosition() const { return m_Position; };
		float GetRotation() const { return m_Rotation; };
		float GetScale() const { return m_Scale; };
		Color GetColor() const { return m_Color; };
		std::shared_ptr<Texture> GetTexture() const { return m_Texture; };

		////////////// Setters //////////////
		void SetPosition(Vector2 position) { m_Position = position; };
		void SetPosition(float x, float y) { m_Position.x = x; m_Position.y = y; };
		void SetRotation(float rotation) { m_Rotation = rotation; };
		void SetScale(float scale) { m_Scale = scale; };
		void SetColor(Color color) { m_Color = color; };
		void SetColor(float r, float g, float b, float a = 1.0f) { m_Color.r = r; m_Color.g = g; m_Color.b = b, m_Color.a = a; };
		void SetTexture(std::shared_ptr<Texture> texture) { m_Texture = texture; };

		////////////// Utility Functions //////////////
		void Translate(Vector2 translation) { m_Position += translation; };
		void Translate(float x, float y) { m_Position.x += x; m_Position.y += y; };
		void Rotate(float rotation) { m_Rotation += rotation; };
		void Scale(float scale) { m_Scale += scale; };

	protected:

		Vector2 m_Position;
		float m_Rotation;
		float m_Scale;
		Color m_Color;
		std::shared_ptr<Texture> m_Texture = nullptr;
	};

}