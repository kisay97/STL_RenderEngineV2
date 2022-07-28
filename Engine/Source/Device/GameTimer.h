#pragma once

#include <Core/Core.h>

namespace STL
{
	class ENGINE_API GameTimer
	{
	public: 
		GameTimer();
		~GameTimer();

		float TotalTime() const;
		float DeltaTime() const;

		void Reset();
		void Start();
		void Stop();
		void Tick();
		int64 ClockFrequency();
		int64 Now();

	private:
		double secondsPerCount;
		double deltaTime;

		int64 baseTime;
		int64 pausedTime;
		int64 stopTime;
		int64 prevTime;
		int64 currentTime;

		bool isStopped;
	};
}