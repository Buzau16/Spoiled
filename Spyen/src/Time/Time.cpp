#include "spypch.h"
#include "Time.h"


namespace Spyen {
	double Time::s_LastFrameTime = 0.0f;
	double Time::s_DeltaTime = 0.0f;

	void Time::UpdateTime()
	{
		double CurrentTime = glfwGetTime();
		s_DeltaTime = CurrentTime - s_LastFrameTime;
		s_LastFrameTime = CurrentTime;
	}

	float Time::DeltaTime()
	{
		return static_cast<float>(s_DeltaTime);
	}
}