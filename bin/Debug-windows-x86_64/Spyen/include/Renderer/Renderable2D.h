#pragma once
#include "Core/Structs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer/Texture.h"
#include "GameObjects/StaticGameObject.h"
#include "GameObjects/DynamicGameObject.h"
#include "Core/Log.h"
#include <memory>


namespace Spyen {
	struct Renderable2D {
		glm::mat4 transform = glm::mat4(1.0f);
		std::shared_ptr<Texture> texture = nullptr;
		Color color = {1.0f, 1.0, 1.0f, 1.0f};
		bool isStatic = false;
	};

	template<typename T>
	Renderable2D CreateRenderable2D(const T& object) {
		if (std::is_same_v<T, StaticGameObject>) {
			Renderable2D rend;
			rend.transform = glm::translate(rend.transform, glm::vec3(object.GetPosition().x, object.GetPosition().y, 0.0f));
			rend.transform = glm::rotate(rend.transform, glm::radians(object.GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
			rend.transform = glm::scale(rend.transform, glm::vec3(glm::vec2(object.GetScale()), 1.0f));
			rend.texture = object.GetTexture();
			rend.color = object.GetColor();
			rend.isStatic = true;
			return rend;
		}
		if (std::is_same_v<T, DynamicGameObject>) {
			Renderable2D rend;
			rend.transform = glm::translate(rend.transform, glm::vec3(object.GetPosition().x, object.GetPosition().y, 0.0f));
			rend.transform = glm::rotate(rend.transform, glm::radians(object.GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
			rend.transform = glm::scale(rend.transform, glm::vec3(glm::vec2(object.GetScale()), 1.0f));
			rend.texture = object.GetTexture();
			rend.color = object.GetColor();
			rend.isStatic = false;
			return rend;
		}

		SPY_CORE_CRITICAL("Unkown Renderable2D argument!");
		return Renderable2D{};
	}
}