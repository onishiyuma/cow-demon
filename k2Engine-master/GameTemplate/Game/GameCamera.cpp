#include "stdafx.h"
#include "GameCamera.h"


GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{
	DeleteGO(this);
}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(1.0f, 125.0f, -60.0f);
	//カメラの座標を取得。
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	//カメラのニアクリップとファークリップを
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(2000.0f);

	return true;
}

void GameCamera::Update()
{

}