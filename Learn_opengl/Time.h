#pragma once
class Time
{
public:
	friend class GameLoop;


	/// <summary>
	/// ʱ����ʧ���ٶ�
	/// </summary>
	static float timeScale;
	/// <summary>
	/// ��Ϸ��ʼ���к��ʱ��
	/// </summary>
	static float GetTime() { return time; }
	/// <summary>
	/// ��Ϸ��ʼ���к��ʱ��
	/// </summary>
	static float GetUnscaledTime() { return unscaledTime; }
	/// <summary>
	/// ���һ��fixedTime��ʱ��
	/// </summary>
	static float GetFixedTime() { return fixedTime; }
	/// <summary>
	/// �����һ֡����ʱ��
	/// </summary>
	static float GetDeltaTime() { return deltaTime; }
	/// <summary>
	/// �����һ֡����ʱ��(����timescaleӰ��)
	/// </summary>
	static float GetUnscaledDeltaTime() { return unscaledDeltaTime; }
	/// <summary>
	/// ��Ϸ��ʼ֮���֡��
	/// </summary>
	static float GetFrameCount() { return frameCount; }

private:

	static float time;

	static float unscaledTime;

	static float fixedTime;

	static float deltaTime;

	static float unscaledDeltaTime;

	static float frameCount;
};

