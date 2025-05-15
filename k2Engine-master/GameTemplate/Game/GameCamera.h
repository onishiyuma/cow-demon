#pragma once

class Player;
class RingBell;
class Game;
class GameOver;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	// 本殿方向に補間する処理
	void LerpToMain();
	
	void LockCamera(bool isLock) 
	{ 
		m_isLocked = isLock;
	}

	//繝｡繝ｳ繝仙､画焚縲・
	GameOver* m_gameOver;
	Game* m_game;
	RingBell* m_ringBell;
	Player* m_player;//繝励Ξ繧､繝､繝ｼ縲・
	Vector3 m_toCameraPos;//豕ｨ隕也せ縺九ｉ隕也せ縺ｫ蜷代°縺・・繧ｯ繝医Ν縲・
	float m_nearClip = 1.0f;//繝九い繝ｼ繧ｯ繝ｪ繝・・
	float m_furClip = 20000.0f;//繝輔ぃ繝ｼ繧ｯ繝ｪ繝・・
	const int m_half=2;//蜊雁・縺ｫ縺吶ｋ
	bool m_isLocked = false;//繧ｫ繝｡繝ｩ繧貞●豁｢縺吶ｋ繧医≧繝輔Λ繧ｰ縲・
	bool m_isGameOver = false;//ゲームオーバーか。
	bool m_isCameraRotationFin=false;//カメラの回転が終わったか。
	float m_rotateTimer = 0.0f;//回転する時間。
	float m_rottatieDuration = 2.0f;//2秒で回転。
	float m_callGameOverTime = 0.0f;//ゲームオーバーを呼び出すまでの時間。
	Vector3 cameraTargetLoakAt;
	Vector3 m_mainPos;//本殿の位置。
};

