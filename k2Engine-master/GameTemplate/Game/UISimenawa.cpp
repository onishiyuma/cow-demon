#include "stdafx.h"
#include "UISimenawa.h"
#include "Player.h"
#include "Game.h"

namespace
{
	//しめ縄
	Vector3 ROPE_FREME_POSITION = Vector3(435.0f, -425.0f, 0.0f);
	//しめ縄ゲージ
	Vector3 ROPE_GAUGE_POSITION = Vector3(435.0f, -486.0f, 0.0f);
	//しめ縄フォント位置
	Vector3 ROPE_FONT_POSITION = Vector3(400.0f, -405.0f, 0.0f);
	//緑
	Vector4 GREEN = Vector4(0.0f,1.0f,0.0f,1.0f);
	//薄い緑
	Vector4 LIGHT_GREEN = Vector4(0.0f, 1.0f, 0.0f, 0.2f);
	//白
	Vector4 WHITE = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//透明
	Vector4 TOUMEI = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
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

	//ロープゲージ
	m_ropeGage.Init("Assets/UI/White.DDS", 120, 14);
	m_ropeGage.SetPosition(ROPE_GAUGE_POSITION);
	m_ropeGage.SetPivot(Vector2{ 0.5f, 0.0f });

	//ロープの画像
	m_ropeSprite.Init("Assets/UI/aitemskil1.DDS", 130, 130);
	m_ropeSprite.SetPosition(ROPE_FREME_POSITION);
	
	m_fontRender.SetScale(1.0);
	m_fontRender.SetPosition(ROPE_FONT_POSITION);
	m_fontRender.SetColor(TOUMEI);


	return true;
}

void UISimenawa::Update()
{

	m_ropeTimer = m_player->m_shimenawaGetTime;
	float wari = (float)m_ropeTimer / 2.6;
	Vector3 scal = { 1.0f,1.51f,1.0f };
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

	if (!m_ResetFrag) {
		// 通常カウントダウン処理
		m_countDownTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_countDownTimer <= 0.0f) {
			m_displayTime--;
			m_countDownTimer = 1.0f;
		}

		// 0になったら待機状態へ
		if (m_ropeTimer<= 0) {
			m_ResetFrag = true;
		}
	}
	else {
		
			// リセット処理
			m_displayTime = 15;
			m_countDownTimer = 1.0f;
			m_ResetFrag = false;
		
	}

	// 表示更新
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