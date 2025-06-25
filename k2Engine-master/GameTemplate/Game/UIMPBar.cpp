#include "stdafx.h"
#include "UIMPBar.h"
#include "Player.h"
#include "Game.h"

namespace 
{
	//MPバーの座標
	Vector3 MP_POSITION = Vector3(-240.0f, -500.0f, 0.0f);
	//MPバーのスケール
	Vector3 MP_SCALE = Vector3(0.47f, 0.2f, 0.5f);
	//MPゲージピボット。
	Vector2 MP_PIVOT = Vector2(0.0f, 0.5f);
	//MPフレームの座標
	Vector3 MP_FRAME_POSITION = Vector3(0.0f, -500.0f, 0.0f);
	//MPフレームのスケール
	Vector3 MP_FRAME_SCALE = Vector3(0.5f, 0.3f, 0.5f);
	//MPバーの色
	Vector3 LIGHT_BLUE = Vector3(0.0f, 1.0f, 1.0f); // 水色
	//MPフレームの色
	Vector3 BLACK = Vector3(0.0f, 0.0f, 0.0f); // 黒色
	
}

UIMPBar::UIMPBar()
{

}

UIMPBar::~UIMPBar()
{

}

bool UIMPBar::Start()
{
	m_player = FindGO<Player>("player");

	// MPバーの初期化
	m_mpBar.Init("Assets/UI/white.DDS", 1024, 128);
	m_mpBar.SetPosition(MP_POSITION);
	m_mpBar.SetScale(MP_SCALE);
	m_mpBar.SetMulColor(LIGHT_BLUE);
	m_mpBar.SetPivot(MP_PIVOT);

	// MPフレームの初期化
	m_mpFrame.Init("Assets/UI/white.DDS", 1024, 128);
	m_mpFrame.SetPosition(MP_FRAME_POSITION);
	m_mpFrame.SetScale(MP_FRAME_SCALE);
	m_mpFrame.SetMulColor(BLACK);

	return true;
}

void UIMPBar::Update()
{
	int mpBar = m_player->m_playerMP;
	int mpMax = m_player->m_playerMaxMP;
	float wari = (float)mpBar / (float)mpMax;
	Vector3 scal = { 0.47f,0.2f,0.5f };
	scal.x *= wari;

	if (m_player->m_playerMP <= 100)
	{
		m_mpBar.SetScale(scal);
	}

	m_mpFrame.Update();
	m_mpBar.Update();
}

void UIMPBar::Render(RenderContext&rc)
{
	m_mpFrame.Draw(rc);

	if (m_player->m_playerMP >= 0)
	{
		m_mpBar.Draw(rc);
	}
	
}