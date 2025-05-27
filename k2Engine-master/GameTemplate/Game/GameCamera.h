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
	void Render(RenderContext& rc);


	void LockCamera(bool isLock) 
	{ 
		m_isLocked = isLock;
	}

	//カメラの座標を取得。
	Vector3 GetCameraPos()const
	{
		return m_position;
	}

	//カメラの前方向を取得。
	Vector3 GetCameraForward()const
	{
		return m_cameraForward;
	}


public:
	//メンバ変数
	bool			m_isGameOver = false;				//ゲームオーバーか。
	bool			m_isCameraRotationFin = false;		//カメラの回転が終わったか。
	float			m_waitTime = 0.0f;					//待機時間。
	float			m_callGameOverTime = 0.0f;			//ゲームオーバーを呼び出すまでの時間。
private:
	GameOver*		m_gameOver;							//ゲームオーバー。
	Game*			m_game;								//ゲーム。
	RingBell*		m_ringBell;							//鐘。
	Player*			m_player;							//プレイヤー。
	Vector3			m_toCameraPos;						//カメラの座標。
	Vector3			m_position = Vector3::Zero;			//座標。
	Vector3			m_cameraForward = Vector3::Zero;	//カメラの前宝庫王。
	Vector3			m_PosMain = Vector3::One;			//本殿の方向の座標
	Vector3			cameraTargetLoakAt;					//ターゲットの方向に向いているか。
	Vector3			m_mainPos;							//本殿の位置。
	FontRender		m_notifyEnemyInMain;				//本殿に敵が入った時の通知。
	float			m_nearClip = 1.0f;					//ニアークリップ
	float			m_furClip = 20000.0f;				//ファークリップ。
	float			m_rotateTimer = 0.0f;				//回転する時間。
	float			m_rottatieDuration = 2.0f;			//2秒で回転。
	const int		m_half=2;							//半分。
	int				m_notifyx = 0.0f;					//通知のX座標。
	bool			m_isLocked = false;					//カメラが本殿を向いているか。
	bool 			m_isShowNotify;						//通知を表示するか。

};

