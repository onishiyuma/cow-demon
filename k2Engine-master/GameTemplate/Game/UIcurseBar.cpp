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
	m_curseFrame.Init("Assets/UI/Red.DDS", 1024, 128);
	m_curseFrame.SetPosition(HP_FREME_POSITION);
	m_curseFrame.SetScale(HP_FRAME_SCAL);
	m_curseFrame.SetMulColor(BLACK);

	//呪いの抵抗ゲージ
	m_curseSprit.Init("Assets/UI/Red.DDS", 102.4, 50);
	m_curseSprit.SetPosition(HP_POSITION);

	m_curseSprit.SetPivot(HP_PIVOT);
	return true;
}

void UIcurseBar::Update()
{
	int newCurseGage = m_player->m_playerHP;
	float wari = (float)newCurseGage / 21;
	Vector3 scal = { 1.0f,1.0f,1.0f };
	scal.x *= wari;

	if (m_player->m_playerHP <= 100) {
		m_curseSprit.SetScale(scal);
	}
	else {

	}

	m_curseFrame.Update();
	m_curseSprit.Update();
}

void UIcurseBar::Render(RenderContext& rc)
{
	m_curseFrame.Draw(rc);
	if (m_player->m_playerHP > 0) {
		m_curseSprit.Draw(rc);
	}
}