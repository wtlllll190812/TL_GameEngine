#pragma once
#include <ctime>

class GameLoop
{
public:
	GameLoop(int);
	~GameLoop();
	bool endLoop;

	/// <summary>
	/// ���ûص�
	/// </summary>
	void SetAwakeCallback(void (*Awake)());

	/// <summary>
	/// ���ûص�
	/// </summary>
	void SetUpdateCallback(void (*Update)());
	
	/// <summary>
	/// ���ûص�
	/// </summary>
	void SetFixedUpdateCallback(void (*FixedUpdate)());
	
	/// <summary>
	/// ���ûص�
	/// </summary>
	void SetLateUpdateCallback(void (*LateUpdate)());

	/// <summary>
	/// ��ʼ��Ϸѭ��
	/// </summary>
	void StartLoop();
	float GetFPS();

private:
	/// <summary>
	/// ��ʼ���ص�
	/// </summary>
	void (*Awake)();
	/// <summary>
	/// update�ص�
	/// </summary>
	void (*Update)();
	/// <summary>
	/// fixedupdate�ص�
	/// </summary>
	void (*FixedUpdate)();
	/// <summary>
	/// lateUpdate�ص�
	/// </summary>
	void (*LateUpdate)();
	//void (*OnEnabled)();
	//void (*OnDisabled)();

	int frame;
};
