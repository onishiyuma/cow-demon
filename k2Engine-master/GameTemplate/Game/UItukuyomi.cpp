#include "stdafx.h"
#include "UItukuyomi.h"
#include "Game.h"
#include "Player.h"

namespace 
{
	//ツクヨミ。
	const Vector3 RUNA_FREME_POSITION(815.0f, -425.0f, 0.0f);
	//ツクヨミの加護のフォント位置。
	const Vector3 RUNA_FONT_POSITION(780.0f, -405.0f, 0.0f);
	//白。
	const Vector4 WHITE(1.0f, 1.0f, 1.0f, 1.0f);
	//透明。
	const Vector4 TOUMEI(1.0f, 1.0f, 1.0f, 0.0f);
	//チャージ中の色。
	const Vector4 RUNA_COLOR(1.0f, 1.0f, 1.0f, 0.5f);
	//チャージ完了の色。
	const Vector4 RUNA_MAX_COLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

UItukuyomi::UItukuyomi()
{

}

UItukuyomi::~UItukuyomi()
{

}

bool UItukuyomi::Start()
{
	//インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");

	//ツクヨミゲージ画像。
	m_runaSprite.Init("Assets/UI/Tukuyomi 1.DDS", 230, 230);
	m_runaSprite.SetPosition(RUNA_FREME_POSITION);
	m_runaSprite.SetMulColor(RUNA_COLOR);

	//ツクヨミMAX。
	m_runaSpriteMax.Init("Assets/UI/TukuyomiMax 1.DDS", 230, 230);
	m_runaSpriteMax.SetPosition(RUNA_FREME_POSITION);
	m_runaSpriteMax.SetMulColor(RUNA_MAX_COLOR);

	//ツクヨミの加護のクールタイムの表記位置。
	m_fontRender.SetPosition(RUNA_FONT_POSITION);
	m_fontRender.SetColor(WHITE);
	m_fontRender.SetScale(1.0f);

	//初期化。
	m_countDownTimer = 40.0f;
	m_countDownTime = 1.0f;

	return true;
}

void UItukuyomi::Update()
{
	m_drawTime = m_player->m_tukuyomiBlessingCoolDown;
	m_runaMax = m_player->m_tukuyomiMax;

	Vector3 scale = { 1.0f,1.0f,1.0f };

	m_runaSpriteMax.SetScale(scale);

	//ツクヨミの加護のクールタイムが0以上の時、ツクヨミゲージを表示。
	if (!m_isReset) 
	{
		//通常カウントダウン処理。
		m_countDownTimer -= g_gameTime->GetFrameDeltaTime();

		if (m_countDownTimer <= 0.0f)
		{
			m_displayTime--;
			m_countDownTimer = 1.0f;
		}

		//待機状態へ。
		if (m_drawTime <= 0.0f) 
		{
			m_isReset = true;
		}
	}
	else 
	{
		//リセット処理。
		m_displayTime = 40;
		m_countDownTimer = 1.0f;
		m_isReset = false;
	}
	

	//表示更新。
	wchar_t timerText[16];
	swprintf(timerText, 16, L"%ds", m_displayTime);
	m_fontRender.SetText(timerText);

	m_runaSprite.Update();
	m_runaSpriteMax.Update();
}

void UItukuyomi::Render(RenderContext& rc)
{
	if (m_drawTime>=m_runaMax)
	{
		m_runaSprite.Draw(rc);
		if (m_player->m_enemyIsCanAttack)
		{
			m_fontRender.Draw(rc);
		}
	}
	else
	{
		m_runaSpriteMax.Draw(rc);
		
	}
}