#pragma once
class Time
{
public:
	friend class GameLoop;

	/// <summary>
	/// ʱ����ʧ���ٶ�
	/// </summary>
	static double timeScale;
	/// <summary>
	/// ��Ϸ��ʼ���к��ʱ��
	/// </summary>
	static double GetTime() { return time; }
	/// <summary>
	/// ��Ϸ��ʼ���к��ʱ��
	/// </summary>
	static double GetUnscaledTime() { return unscaledTime; }
	/// <summary>
	/// ���һ��fixedTime��ʱ��
	/// </summary>
	static double GetFixedTime() { return fixedTime; }
	/// <summary>
	/// �����һ֡����ʱ��
	/// </summary>
	static double GetDeltaTime() { return deltaTime; }
	/// <summary>
	/// �����һ֡����ʱ��(����timescaleӰ��)
	/// </summary>
	static double GetUnscaledDeltaTime() { return unscaledDeltaTime; }
	/// <summary>
	/// ��Ϸ��ʼ֮���֡��
	/// </summary>
	static double GetFrameCount() { return frameCount; }

private:

	static double time;

	static double unscaledTime;

	static double fixedTime;

	static double deltaTime;

	static double unscaledDeltaTime;

	static double frameCount;
};
