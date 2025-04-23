#pragma once

class Player;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	
	void LockCamera(bool isLock) 
	{ 
		m_isLocked = isLock;
	}

	//メンバ変数。
	Player* m_player;//プレイヤー。
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル。
	float m_nearClip = 1.0f;//ニアークリップ
	float m_furClip = 20000.0f;//ファークリップ
	const int m_half=2;//半分にする
	int m_nearClip = 1.0f;//ニアークリップ
	int m_furClip = 20000.0f;//ファークリップ
	const float m_half=2;//半分にする
	bool m_isLocked = false;//カメラを停止するようフラグ。
};

