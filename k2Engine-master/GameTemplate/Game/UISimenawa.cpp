#include "stdafx.h"
#include "UISimenawa.h"
#include "Player.h"
#include "Game.h"

namespace
{
	//ゲージのピボット。
	const Vector2 GAGE_PIVOT = { 0.5f, 0.0f };
	//文字の大きさ。
	float FONT_SCALE = 1.0f;
	//大きさ。
	Vector3 SCALE = { 1.0f, 1.51f, 1.0f };
	//しめ縄。
	Vector3 ROPE_FREME_POSITION = { 435.0f, -425.0f, 0.0f };
	//しめ縄ゲージ。
	Vector3 ROPE_GAUGE_POSITION = { 435.0f, -486.0f, 0.0f };
	//しめ縄フォント位置。
	Vector3 ROPE_FONT_POSITION = { 409.0f, -405.0f, 0.0f };
	//緑。
	Vector4 GREEN = { 0.0f,1.0f,0.0f,1.0f };
	//薄い緑。
	Vector4 LIGHT_GREEN = { 0.0f, 1.0f, 0.0f, 0.2f };
	//白。
	Vector4 WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };
	//黒。
	Vector4 BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };
	//透明。
	Vector4 TOUMEI = { 0.0f, 0.0f, 0.0f, 0.0f };
}

UISimenawa::UISimenawa()
{

}

UISimenawa::~UISimenawa()
{

}

bool UISimenawa::Start()
{
	//インスタンスアドレスを検索。
	m_player=FindGO<Player>("player");

	//ロープゲージの画像。
	m_ropeGage.Init("Assets/UI/White.DDS", 120, 14);
	m_ropeGage.SetPosition(ROPE_GAUGE_POSITION);
	m_ropeGage.SetPivot(GAGE_PIVOT);

	//ロープの画像。
	m_ropeSprite.Init("Assets/UI/aitemskil1.DDS", 130, 130);
	m_ropeSprite.SetPosition(ROPE_FREME_POSITION);
	
	//文字の大きさ、座標、色を設定。
	m_fontRender.SetScale(FONT_SCALE);
	m_fontRender.SetPosition(ROPE_FONT_POSITION);
	m_fontRender.SetColor(TOUMEI);


	return true;
}

void UISimenawa::Update()
{
	//しめ縄の時間が0になったら、しめ縄のゲージを非表示にする。
	UpdateShimenawaGaugeVisibility();
}

void UISimenawa::UpdateShimenawaGaugeVisibility()
{
	//しめ縄の時間が0になったら、しめ縄のゲージを非表示にする。
	m_ropeTimer = m_player->m_shimenawaGetTime;
	float wari = (float)m_ropeTimer / 2.6;
	Vector3 scal = SCALE;
	scal.y *= wari;

	if (m_ropeTimer <= m_player->m_collectTime)
	{
		m_ropeGage.SetScale(scal);
		m_ropeGage.SetMulColor(LIGHT_GREEN);
		m_fontRender.SetColor(WHITE);
	}
	else
	{
		m_ropeGage.SetMulColor(GREEN);
		m_fontRender.SetColor(TOUMEI);
	}

	if (!m_isReset) 
	{
		//通常カウントダウン処理。
		m_ShimenawaUseTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_ShimenawaUseTimer <= 0.0f) 
		{
			m_displayTime--;
			m_ShimenawaUseTimer = 1.0f;
		}

		//0になったら待機状態へ。
		if (m_ropeTimer <= 0)
		{
			m_isReset = true;
		}
	}
	else 
	{
		//リセット処理。
		m_displayTime = 15;
		m_ShimenawaUseTimer = 1.0f;
		m_isReset = false;
	}

	//カウントダウンを表示。
	wchar_t timerText[16];
	swprintf(timerText, 16, L"%ds", m_displayTime);

	m_fontRender.SetText(timerText);
	m_ropeSprite.Update();
	m_ropeGage.Update();
}

void UISimenawa::Render(RenderContext& rc)
{
	if (m_ropeTimer > 0) 
	{
		m_ropeGage.Draw(rc);
		m_fontRender.Draw(rc);
	}

	m_ropeSprite.Draw(rc);
}