#pragma once
#include "Core/Core.h"
#include <glm/glm.hpp>

namespace Spyen {
	class SPYEN_API Camera {
	public:
		Camera() = default;
		Camera(Vector2 pos, float zoom);
		~Camera() = default;

		void SetProjection(Vector2 params);
		glm::mat4& GetProjection() const;
		
		void SetPosition(const Vector2& pos);
		Vector2 GetPosition() const;

		void UpdateMatricies();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjMatrix;
		
		Vector2 m_Position;
		float m_Zoom;
	};
}