#include "GameTimer.h"

namespace STL
{
	GameTimer::GameTimer()
		: secondsPerCount(0.0), deltaTime(-1.0), baseTime(0),
		pausedTime(0), prevTime(0), currentTime(0), isStopped(false)
	{
		int64 countsPerSecond = 0;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond); //���ػ�(�����е�) Ÿ�̸�(CPU Ŭ����ŭ�� �ػ�(1/3.6G ��))
		secondsPerCount = 1.0 / (double)countsPerSecond;
	}

	GameTimer::~GameTimer()
	{

	}

	float GameTimer::TotalTime() const
	{
		if (isStopped)
		{
			return static_cast<float>(((stopTime - pausedTime) - baseTime) * secondsPerCount);
		}

		return static_cast<float>(((currentTime - pausedTime) - baseTime) * secondsPerCount);
	}

	float GameTimer::DeltaTime() const
	{
		return static_cast<float>(deltaTime);
	}

	void GameTimer::Reset()
	{
		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		baseTime = currentTime;
		prevTime = currentTime;
		stopTime = 0;
		isStopped = false;
	}

	void GameTimer::Start()
	{
		int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime); // ���� �ð��� ��ȯ�ϴµ�, CPU Ŭ����ŭ�� �ػ�(1/3.6G ��)�� ��ȯ

		if (isStopped)
		{
			pausedTime += (startTime - stopTime);

			prevTime = startTime;
			stopTime = 0;
			isStopped = false;
		}
	}

	void GameTimer::Stop()
	{
		if (isStopped == false)
		{
			int64 currentTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

			stopTime = currentTime;
			isStopped = true;
		}
	}

	void GameTimer::Tick()
	{
		if (isStopped)
		{
			deltaTime = 0.0;
			return;
		}

		int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		this->currentTime = currentTime;

		deltaTime = (this->currentTime - prevTime) * secondsPerCount;

		prevTime = this->currentTime;

		if (deltaTime < 0.0)
		{
			deltaTime = 0.0;
		}
	}
	int64 GameTimer::ClockFrequency()
	{
		static int64 countsPerSecond = 0;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond); //���ػ�(�����е�) Ÿ�̸�(CPU Ŭ����ŭ�� �ػ�(1/3.6G ��))

		return countsPerSecond;
	}

	int64 GameTimer::Now()
	{
		static int64 currentTime = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		return currentTime;
	}
}