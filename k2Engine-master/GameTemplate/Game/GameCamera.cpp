#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"



bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(1.0f, 125.0f, -60.0f);
	//カメラの座標を取得する
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(m_nearClip);
	g_camera3D->SetFar(m_furClip);

	return true;
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{
	DeleteGO(this);
}


void GameCamera::Update()
{
	//注視点を計算する。
	Vector3 target = m_player->m_position;
	//プレイヤの注視点を設定。
	target.y += 90.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

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
	qRot.SetRotationDeg(axisX, 2.2f * y);
	qRot.Apply(m_toCameraPos);

	//視点を計算する。
	Vector3 pos = target+m_toCameraPos/m_half;

	//メインカメラに注視点と座標を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}