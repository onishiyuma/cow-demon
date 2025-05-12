#pragma once

class LoadManager:public IGameObject
{
public:
	LoadManager();
	~LoadManager();

	bool Star();
	void Update();

	//現在のロード進捗。
	static void SetProgress(float progress);
	static float GetProgress();

	//ロード完了を通知する。
	static void Finish();
	static bool IsFinished();

	static float m_progress;
	static bool m_finished;
};

