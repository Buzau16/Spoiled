#include "spypch.h"
#include "Renderer/Camera.h"


namespace Spyen {
	Camera::Camera(Vector2 pos, float zoom)
		: m_Position(pos),
		  m_Zoom(zoom),
		  m_ViewMatrix(glm::mat4(1.0f)),
		  m_ProjMatrix(glm::mat4(1.0f))
	{}

	void Camera::SetProjection(Vector2 params)
	{
		m_ViewMatrix = glm::ortho(0.f, 1.f, 1.f, 0.f, -1.f, 1.f);
	}

}