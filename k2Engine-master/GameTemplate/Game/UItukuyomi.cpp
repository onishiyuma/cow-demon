#include "stdafx.h"
#include "UItukuyomi.h"
#include "Game.h"
#include "Player.h"

namespace 
{
	//ツクヨミ
	Vector3 RUNA_FREME_POSITION = Vector3(815.0f, -425.0f, 0.0f);
	//ツクヨミの加護のフォント位置
	Vector3 RUNA_FONT_POSITION = Vector3(780.0f, -405.0f, 0.0f);
	//白
	Vector4 WHITE = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//透明
	Vector4 TOUMEI = Vector4(1.0f, 1.0f, 1.0f, 0.0f);

}

UItukuyomi::UItukuyomi()
{

}

UItukuyomi::~UItukuyomi()
{

}

bool UItukuyomi::Start()
{
	m_player = FindGO<Player>("player");
	//ツクヨミゲージ0
	m_runaSprite.Init("Assets/UI/Tukuyomi 1.DDS", 230, 230);
	m_runaSprite.SetPosition(RUNA_FREME_POSITION);
	m_runaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

	//ツクヨミMAX
	m_runaSprite2.Init("Assets/UI/TukuyomiMax 1.DDS", 230, 230);
	m_runaSprite2.SetPosition(RUNA_FREME_POSITION);
	m_runaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

	//ツクヨミの加護のクールタイムの表記位置
	m_fontRender.SetPosition(RUNA_FONT_POSITION);
	m_fontRender.SetColor(WHITE);
	m_fontRender.SetScale(1.0f);

	return true;
}

void UItukuyomi::Update()
{
	m_fadeTime = m_player->m_tukuyomiBlessingCoolDown;
	m_runaMax = m_player->m_tukuyomiMax;

	Vector3 scale = { 1.0f,1.0f,1.0f };

	m_runaSprite2.SetScale(scale);

		if (!m_ResetFrag) {
			// 通常カウントダウン処理
			m_countDownTimer -= g_gameTime->GetFrameDeltaTime();

			if (m_countDownTimer <= 0.0f) {
				m_displayTime--;
				m_countDownTimer = 1.0f;
			}

			// 0になったら待機状態へ
			if (m_fadeTime <= 0) {
				m_ResetFrag = true;
			}
		}
		else {

			// リセット処理
			m_displayTime = 40;
			m_countDownTimer = 1.0f;
			m_ResetFrag = false;

		}
	

	// 表示更新
	wchar_t timerText[16];
	swprintf(timerText, 16, L"%ds", m_displayTime);
	m_fontRender.SetText(timerText);

	m_runaSprite.Update();
	m_runaSprite2.Update();
}

void UItukuyomi::Render(RenderContext& rc)
{
	if (m_fadeTime >=m_runaMax)
	{
		m_runaSprite.Draw(rc);
		if (m_player->m_enemyIsCanAttack == true)
		{
			m_fontRender.Draw(rc);
		}
	}

	else
	{
		m_runaSprite2.Draw(rc);
		
	}
}