#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"
#include "Game.h"


bool GameClear::Start()
{
	//ゲームクリアの画像を読み込む
	m_spriteRender.Init("Assets/sprite/Clear.DDS", 1920.0f, 1080.0f);
	
	m_background.Init("Assets/sprite/white.DDS", 1920.0f, 1080.0f);
	m_background.SetScale({ 2.0f, 2.0f, 1.0f });

	m_fontRender.SetText(L"A タイトルに戻る");
	m_fontRender.SetPosition({ -200.0f,-250.0f,0.0f });
	m_fontRender.SetColor(m_fontColor);
	
	return true;
}

GameClear::GameClear()
{

}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	m_titleTime += g_gameTime->GetFrameDeltaTime();

	m_background.Update();
	m_spriteRender.Update();

	SpriteFade();

	if (m_isSpriteFade) 
	{
		FontFade();
	}
	
	if (m_titleTime >= m_maxTitleTime)
	{
		//タイトルに戻る処理。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			NewGO<Title>(0);

			DeleteGO(this);
		}
	}
}

void GameClear::FontFade()
{
	//フォントのフェードインの処理。
	if (!m_isFontFade)
	{

		m_fontColor.a += 0.01f * m_fadeTime / m_fadeMaxTime;

		m_fontRender.SetColor(m_fontColor);
		if (m_fontColor.a >= 1.0f)
		{
			m_isFontFade = true;
			m_fontColor.a = 1.0f;
			m_fontRender.SetColor(m_fontColor);
		}
	}
	else
	{
		//フォントのフェードアウトの処理。
		m_fontColor.a -= 0.01f * m_fadeTime / m_fadeMaxTime;

		m_fontRender.SetColor(m_fontColor);
		if (m_fontColor.a <= 0.0f)
		{
			m_isFontFade = false;
			m_fontColor.a = 0.0f;
			m_fontRender.SetColor(m_fontColor);
		}
	}
}

void GameClear::SpriteFade()
{
		//スプライトのフェードインの処理。
	if (!m_isSpriteFade)
	{
		m_spriteColor.r += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteColor.g += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteColor.b += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteColor.a += 0.01f * m_fadeTime / m_fadeMaxTime;
		m_spriteRender.SetMulColor(m_spriteColor);
		if (m_spriteColor.a >= 1.0f)
		{
			m_isSpriteFade = true;
			m_spriteColor.r = 1.0f;
			m_spriteColor.g = 1.0f;
			m_spriteColor.b = 1.0f;
			m_spriteColor.a = 1.0f;
			m_spriteRender.SetMulColor(m_spriteColor);
		}
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_background.Draw(rc);
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}