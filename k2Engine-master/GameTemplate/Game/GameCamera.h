#pragma once

class Player;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	

	//メンバ変数
	GameCamera* m_gameCamera;//カメラ。
	Player* m_player;//プレイヤー。
	Vector3 m_toCameraPos;//注視点から視点に向かうベクトル。
	int m_nearClip = 1.0f;//ニアークリップ
	int m_furClip = 20000.0f;//ファークリップ
	const int m_half=2;//半分にする

	
};

