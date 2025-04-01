#pragma once


namespace Spyen {
	class Timestep
	{
	public:
		Timestep(float time) : m_DeltaTime(time) {}
		~Timestep() = default;

		operator float() { return m_DeltaTime; };
		float GetTime() { return m_DeltaTime; };

	private:
		float m_LastFrameTime;
		float m_DeltaTime;
	};
}