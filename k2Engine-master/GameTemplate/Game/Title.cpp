#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Load.h"


bool Title::Start()
{
	//タイトルの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/cowDemonTitle.DDS", 1920.0f, 1080.0f);

	m_spriteSoul.Init("Assets/sprite/soulFade.DDS", 1920.0f, 1080.0f);

	m_spriteSoul.SetMulColor(m_soulColor);
	
	//文字の表示。
	m_fontRender.SetText(L"Please Press AnyKey");
	m_fontRender.SetPosition({ -250.0f,-300.0f,0.0f });
	m_fontRender.SetColor(m_fontColor);

	

	return true;
}

Title::Title()
{

}

Title::~Title()
{
	
}

void Title::Update()
{
	//タイマーを加算。
	m_timer+= g_gameTime->GetFrameDeltaTime();
	
	//タイトルのフェードインの処理。
	FadeIn();

	

	if (m_isFadeIn == true) {

		//フェードインが終わったらフォントのフェードインを行う。
		FontFade();

		if (m_fontFadeCount > 0) {

			//魂のフェードインを行う。
			SoulFade();

			if (m_timer >= m_maxTitleTime)
			{
				m_timer = m_maxTitleTime;

				//タイトルからインゲームへ移行。
				if (m_timer > 0.1f && g_pad[0]->IsPressAnyKey())
				{
					NewGO<Load>(1, "load");
					m_spriteRender.Update();
					//自身を削除する。
					DeleteGO(this);
				}
			}
		}
		

	}
	
	
}

void Title::FadeIn()
{
	//タイトルのフェードインの処理。
	if (!m_isFadeIn)
	{
		//フェードインの処理。
		m_titleColor.a += 0.01f * m_timer / m_maxTitleTime;
		m_spriteRender.SetMulColor(m_titleColor);

		if (m_titleColor.a >= 1.0f)
		{
			m_isFadeIn = true;
			m_titleColor.a = 1.0f;
			m_spriteRender.SetMulColor(m_titleColor);
		}
	}
	
}

void Title::FontFade()
{
	

	//フォントのフェードインの処理。
	if (!m_isFontFade)
	{
		m_fontColor.r += 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.g += 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.b += 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.a += 0.01f * m_timer / m_maxTitleTime;
		m_fontRender.SetColor(m_fontColor);
		if (m_fontColor.a >= 1.0f)
		{
			m_fontFadeCount++;
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
		m_fontColor.r -= 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.g -= 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.b -= 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.a -= 0.01f * m_timer / m_maxTitleTime;
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

void Title::SoulFade()
{
	//魂のフェードインの処理。
	if (!m_isSoulFade)
	{
		m_soulColor.r += 0.01f * m_timer / m_soulTime;
		m_soulColor.g += 0.01f * m_timer / m_soulTime;
		m_soulColor.b += 0.01f * m_timer / m_soulTime;
		m_soulColor.a += 0.01f * m_timer / m_soulTime;
		m_spriteSoul.SetMulColor(m_soulColor);
		if (m_soulColor.a >= 1.0f)
		{
			m_isSoulFade = true;
			m_soulColor.r = 1.0f;
			m_soulColor.g = 1.0f;
			m_soulColor.b = 1.0f;
			m_soulColor.a = 1.0f;
			m_spriteSoul.SetMulColor(m_soulColor);
		}
	}
	else
	{
		//魂のフェードアウトの処理。
		m_soulColor.r -= 0.01f * m_timer / m_soulTime;
		m_soulColor.g -= 0.01f * m_timer / m_soulTime;
		m_soulColor.b -= 0.01f * m_timer / m_soulTime;
		m_soulColor.a -= 0.01f * m_timer / m_soulTime;
		m_spriteSoul.SetMulColor(m_soulColor);
		if (m_soulColor.a <= 0.0f)
		{
			m_isSoulFade = false;
			m_soulColor.r = 0.0f;
			m_soulColor.g = 0.0f;
			m_soulColor.b = 0.0f;
			m_soulColor.a = 0.0f;
			m_spriteSoul.SetMulColor(m_soulColor);
		}
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_spriteSoul.Draw(rc);
	m_fontRender.Draw(rc);
}