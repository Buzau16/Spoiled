#pragma once


namespace Spyen {
	class Time
	{
	public:
		Time() = default;
		~Time() = default;

		static void UpdateTime();
		static float DeltaTime();

	private:
		static double s_LastFrameTime;
		static double s_DeltaTime;
	};

}