#include "stdafx.h"
#include "UIcurseBar.h"
#include "Player.h";
#include "Game.h";

namespace
{
	//HPゲージ
	Vector3 HP_POSITION = Vector3(-245.0f, -450.0f, 0.0f);
	//HPフレーム
	Vector3 HP_FREME_POSITION = Vector3(0.0f, -450.0f, 0.0f);
	//HPフレームスケール
	Vector3 HP_FRAME_SCAL = Vector3(0.5f, 0.5f, 0.5f);
	//HPゲージスケール
	Vector3 HP_SCAL = Vector3(0.2f, 0.5f, 0.5f);
	//HPゲージピボット
	Vector2 HP_PIVOT = Vector2(0.0f, 0.5f);
	//黒
	Vector4 BLACK = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

UIcurseBar::UIcurseBar()
{

}

UIcurseBar::~UIcurseBar()
{

}

bool UIcurseBar::Start()
{
	m_player = FindGO<Player>("player");
	//呪の抵抗フレーム
	m_CurseFrame.Init("Assets/UI/Red.DDS", 1024, 128);
	m_CurseFrame.SetPosition(HP_FREME_POSITION);
	m_CurseFrame.SetScale(HP_FRAME_SCAL);
	m_CurseFrame.SetMulColor(BLACK);

	//呪いの抵抗ゲージ
	m_CurseSprit.Init("Assets/UI/Red.DDS", 102.4, 50);
	m_CurseSprit.SetPosition(HP_POSITION);

	m_CurseSprit.SetPivot(HP_PIVOT);
	return true;
}

void UIcurseBar::Update()
{
	int newCurseGage = m_player->m_playerHP;
	float wari = (float)newCurseGage / 21;
	Vector3 scal = { 1.0f,1.0f,1.0f };
	scal.x *= wari;

	if (m_player->m_playerHP <= 100) {
		m_CurseSprit.SetScale(scal);
	}
	else {

	}

	m_CurseFrame.Update();
	m_CurseSprit.Update();
}

void UIcurseBar::Render(RenderContext& rc)
{
	m_CurseFrame.Draw(rc);
	if (m_player->m_playerHP > 0) {
		m_CurseSprit.Draw(rc);
	}
}