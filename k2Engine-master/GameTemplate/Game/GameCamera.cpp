#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "RingBell.h"
#include "Game.h"
#include "GameOver.h"


bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(1.0f, 125.0f, -60.0f);
	//m_toCameraPos2はエネミーUI用に作成
	m_PosMain.Set(1.0f, 125.0f, -60.0f);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");
	m_ringBell = FindGO<RingBell>("ringbell");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(m_nearClip);
	g_camera3D->SetFar(m_furClip);

	//初期化。
	m_waitTime = 5.0f;
	m_notifyx = 1000.0f;

	return true;
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}


void GameCamera::Update()
{
	//注視点を計算する。
	Vector3 target = m_player->m_position;
	//プレイヤの注視点を設定。
	target.z += 30.0f;
	target.y += 100.0f;
	Vector3 toCameraPosOld = m_toCameraPos;
	if (!m_isGameOver)
	{
		//パッドの入力を使ってカメラを回す。
		float x = g_pad[0]->GetRStickXF();
		float y = g_pad[0]->GetRStickYF();

		//Y軸周りの回転
		Quaternion qRot;
		qRot.SetRotationDeg(Vector3::AxisY, 1.8f * x);
		qRot.Apply(m_toCameraPos);

		//X軸周りの回転。
		Vector3 axisX;
		axisX.Cross(Vector3::AxisY, m_toCameraPos);
		axisX.Normalize();
		qRot.SetRotationDeg(axisX, 2.4f * y);
		qRot.Apply(m_toCameraPos);
	}
	//ゲームオーバー時にカメラを本殿に向ける。
	else
	{
		//敵が来たことを通知する。
		m_notifyEnemyInMain.SetText(L"本殿に入られたぞ");
		m_notifyEnemyInMain.SetColor(g_vec4White);
		m_notifyEnemyInMain.SetScale(2);
		m_isShowNotify = true;

		if (m_isShowNotify)
		{
			m_notifyx -= 250 * g_gameTime->GetFrameDeltaTime();
			m_notifyEnemyInMain.SetPosition(m_notifyx, 400.0f, 0.0f);

			if (m_notifyx < -1400.0f)
			{
				m_isShowNotify = false;
			}
		}

		// 本殿の位置。
		m_mainPos = m_ringBell->GetPosition();

		// 注視点から本殿への方向。
		Vector3 toShrineDir = m_mainPos - target;
		toShrineDir.Normalize();


		// 現在のカメラ方向と距離。
		Vector3 currentDir = m_toCameraPos;
		float length = currentDir.Length();

		// 本殿方向を同じ距離に変換。
		Vector3 targetDir =toShrineDir * (- length);

		// 補間率。
		float t = 0.05f;

		//Lerp。
		m_toCameraPos = currentDir + (targetDir - currentDir) * t;

		m_isCameraRotationFin = true;

		m_callGameOverTime += g_gameTime->GetFrameDeltaTime();
		
		Vector3 position = target + m_PosMain;

		m_position = position;
		m_cameraForward = (target - position);
		m_cameraForward.Normalize();
	}

	Vector3 position = target + m_PosMain;

	m_position = position;
	m_cameraForward = (target - position);
	m_cameraForward.Normalize();

	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < m_cameraYMin)
	{
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > m_cameraYMax) 
	{
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos / m_half;
	//メインカメラに注視点と座標を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}

void GameCamera::Render(RenderContext& rc)
{
	m_notifyEnemyInMain.Draw(rc);
}