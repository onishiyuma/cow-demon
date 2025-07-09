#include "stdafx.h"
#include "UIcurseBar.h"
#include "Player.h";
#include "Game.h";

namespace
{
	//HPバーの座標。
	const Vector3 HP_POSITION = { -245.0f, -450.0f, 0.0f };
	//フレームの座標。
	const Vector3 HP_FRAME_POSITION = { 0.0f, -450.0f, 0.0f };
	//フレームの大きさ。
	const Vector3 HP_FRAME_SCALE = { 0.5f, 0.5f, 0.5f };
	//HPバーの大きさ。
	const Vector3 HP_SCAL = { 0.2f, 0.5f, 0.5f };
	//HPバーのベースとなる大きさ。
	const Vector3 CURSE_BAR_SCALE_BASE = { 1.0f,1.0f,1.0f };
	//HPバーのピボット。
	const Vector2 HP_PIVOT{ 0.0f, 0.5f };
	//プレイヤーの体力が危ない。
	const int PLAYER_HP_DENGER = 30;
}

UIcurseBar::UIcurseBar()
{

}

UIcurseBar::~UIcurseBar()
{

}

bool UIcurseBar::Start()
{
	//インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");

	//呪の抵抗フレーム。
	m_curseFrame.Init("Assets/UI/white.DDS", 1024, 128);
	m_curseFrame.SetPosition(HP_FRAME_POSITION);
	m_curseFrame.SetScale(HP_FRAME_SCALE);
	m_curseFrame.SetMulColor(g_vec4Black);

	//呪いの抵抗ゲージ。
	m_curseSprit.Init("Assets/UI/white.DDS", 102.4, 50);
	m_curseSprit.SetPosition(HP_POSITION);
	m_curseSprit.SetPivot(HP_PIVOT);
	return true;
}

void UIcurseBar::Update()
{
	//呪いの抵抗ゲージのスケールを変更。
	int newCurseGage = m_player->m_playerHP;
	float wari = (float)newCurseGage / 21.0;
	Vector3 scal = CURSE_BAR_SCALE_BASE;
	scal.x *= wari;

	if (m_player->m_playerHP <= m_player->m_playerMaxHP)
	{
		m_curseSprit.SetScale(scal);
	}


	// プレイヤーが毒状態なら紫色にする。
	if (m_player->m_playerState)
	{
		m_curseSprit.SetMulColor(g_vec4Purple);
	}
	//プレイヤーのHPが30以上の場合は緑色にする。
	else if (m_player->m_playerHP>= PLAYER_HP_DENGER)
	{
		m_curseSprit.SetMulColor(g_vec4Green);
	}
	//プレイヤーのHPが30未満の場合は赤色にする。
	else
	{
		m_curseSprit.SetMulColor(g_vec4Red);
	}

	m_curseFrame.Update();
	m_curseSprit.Update();
}

void UIcurseBar::Render(RenderContext& rc)
{
	m_curseFrame.Draw(rc);
	if (m_player->m_playerHP >= 0)
	{
		m_curseSprit.Draw(rc);
	}
}