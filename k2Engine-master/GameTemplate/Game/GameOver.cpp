#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"
#include "sound/SoundEngine.h"


bool GameOver::Start()
{
	m_backGround.Init("Assets/sprite/Black.DDS", 1920.0f, 1080.0f);

	//ゲームオーバーの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/Over.DDS", 1920.0f, 1080.0f);

	m_soul.Init("Assets/UI/gage.DDS", 150, 150);
	m_soul.SetPosition(m_soulPos);

	m_fontRender.SetText(L"A タイトルに戻る");
	m_fontRender.SetPosition({ -200.0f,-250.0f,0.0f });
	m_fontRender.SetColor(m_fontColor);

	g_soundEngine->ResistWaveFileBank(3,"Assets/sound/gameOver.wav");
	m_gameOverBGM = NewGO<SoundSource>(3);
	m_gameOverBGM->Init(3);
	m_gameOverBGM->Play(false);

	m_game = FindGO<Game>("Game");

	return true;
}

GameOver::GameOver()
{

}

GameOver::~GameOver()
{
	DeleteGO(m_gameOverBGM);
}

void GameOver::Update()
{
	m_titleTime +=g_gameTime->GetFrameDeltaTime();

	m_backGround.Update();
	m_spriteRender.Update();
	m_soul.Update();

	SoulFade();

	if (m_isSoulFade) {
		SpriteFade();
	}
	
	if (m_isSpriteFade) {
		FontFade();
	}

	if (m_titleTime >= m_maxTitleTIme)
	{
		//タイトルに戻る処理。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			NewGO<Title>(0);
			DeleteGO(m_game);
			DeleteGO(this);
		}
	}
}

void GameOver::SoulFade()
{
	if (!m_isSoulFade) {
		m_soulColor.r -= 0.01f * m_soulTime / m_soulMaxTime;
		m_soulColor.g -= 0.01f * m_soulTime / m_soulMaxTime;
		m_soulColor.b -= 0.01f * m_soulTime / m_soulMaxTime;
		m_soulColor.a -= 0.01f * m_soulTime / m_soulMaxTime;
		m_soul.SetMulColor(m_soulColor);
		if (m_color.a <= 0.0f)
		{
			m_isSoulFade = true;
			m_soulColor.r = 0.0f;
			m_soulColor.g = 0.0f;
			m_soulColor.b = 0.0f;
			m_soulColor.a = 0.0f;
			m_soul.SetMulColor(m_soulColor);
		}
	}
}

void GameOver::FontFade()
{
	//フォントのフェードインの処理。
	if (!m_isFontFade)
	{
		
		m_fontColor.r += 0.01f * m_fontTime / m_fontMaxTime;
		m_fontColor.g += 0.01f * m_fontTime / m_fontMaxTime;
		m_fontColor.b += 0.01f * m_fontTime / m_fontMaxTime;
		m_fontColor.a += 0.01f * m_fontTime / m_fontMaxTime;

		m_fontRender.SetColor(m_fontColor);
		if (m_fontColor.a >= 1.0f)
		{
			m_isFontFade = true;
			m_fontColor.r = 1.0f;
			m_fontColor.g = 1.0f;
			m_fontColor.b = 1.0f;
			m_fontColor.a = 1.0f;
			m_fontRender.SetColor(m_fontColor);
		}
	}
	else
	{
		//フォントのフェードアウトの処理。
		m_fontColor.r -= 0.01f * m_fontTime / m_fontMaxTime;
		m_fontColor.g -= 0.01f * m_fontTime / m_fontMaxTime;
		m_fontColor.b -= 0.01f * m_fontTime / m_fontMaxTime;
		m_fontColor.a -= 0.01f * m_fontTime / m_fontMaxTime;

		m_fontRender.SetColor(m_fontColor);
		if (m_fontColor.a <= 0.0f)
		{
			m_isFontFade = false;
			m_fontColor.r = 0.0f;
			m_fontColor.g = 0.0f;
			m_fontColor.b = 0.0f;
			m_fontColor.a = 0.0f;
			m_fontRender.SetColor(m_fontColor);
		}
	}
}

void GameOver::SpriteFade()
{
	m_color.r += 0.01f * m_sprTime / m_sprMaxTime;
	m_color.g += 0.01f * m_sprTime / m_sprMaxTime;
	m_color.b += 0.01f * m_sprTime / m_sprMaxTime;
	m_color.a += 0.01f * m_sprTime / m_sprMaxTime;
	m_spriteRender.SetMulColor(m_color);
	if (m_color.a >= 1.0f) {
		m_color.r = 1.0f;
		m_color.g = 1.0f;
		m_color.b = 1.0f;
		m_color.a = 1.0f;
		m_spriteRender.SetMulColor(m_color);
		m_isSpriteFade = true;
	}

}

void GameOver::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
	m_soul.Draw(rc);
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}