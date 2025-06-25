#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Load.h"
#include "Operation.h"
#include "sound/SoundEngine.h"
#include "GameManagement.h"


bool Title::Start()
{
	//タイトルの背景画像を読み込む
	m_spriteBack.Init("Assets/sprite/Black.DDS", 1920.0f, 1080.0f);

	m_spriteBack.SetPosition(m_backPos);

	//タイトルの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/cowDemonTitle.DDS", 1920.0f, 1080.0f);

	m_spriteSoul.Init("Assets/sprite/soulFade.DDS", 1920.0f, 1080.0f);

	m_spriteSoul.SetMulColor(m_soulColor);
	
	//文字の表示。
	m_fontRender.SetText(L"A ゲームスタート");
	m_fontRender.SetPosition({ -200.0f,-250.0f,0.0f });
	m_fontRender.SetColor(m_fontColor);

	m_fontDescription.SetText(L"B 操作説明");
	m_fontDescription.SetPosition({ -200.0f,-350.0f,0.0f });
	m_fontDescription.SetColor(m_fontColor);


	//タイトルのBGMを読み込む。

	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title.wav");

	//タイトルのBGMを再生する。
	m_titleBGM = NewGO<SoundSource>(1);
	m_titleBGM->Init(1);
	m_titleBGM->Play(true);

	m_gameManagement = FindGO<GameManagement>("gameManagement");
	

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

	m_spriteBack.Update();
	m_spriteRender.SetPosition(m_backPos);

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
				if (m_timer > 0.1f && g_pad[0]->IsPress(enButtonA))
				{
					if (m_gameManagement->m_isGame == false) {

						m_gameManagement->m_isGame = true;
						NewGO<Load>(1, "load");
						m_spriteRender.Update();
						DeleteGO(m_titleBGM);
						//自身を削除する。
						DeleteGO(this);

					}
				}
				//タイトルからチュートリアルへ移行。
				else if(m_timer > 0.1f && g_pad[0]->IsPress(enButtonB)) 
				{
					if (m_gameManagement->m_isOperation == false) {

						m_gameManagement->m_isOperation = true;
						NewGO<Operation>(1, "operation");
						m_spriteRender.Update();
						DeleteGO(m_titleBGM);
						//自身を削除する。
						DeleteGO(this);

					}
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

		m_fontDescriptionColor.r += 0.01f * m_timer / m_maxTitleTime;
		m_fontDescriptionColor.g += 0.01f * m_timer / m_maxTitleTime;
		m_fontDescriptionColor.b += 0.01f * m_timer / m_maxTitleTime;
		m_fontDescriptionColor.a += 0.01f * m_timer / m_maxTitleTime;

		m_fontRender.SetColor(m_fontColor);
		m_fontDescription.SetColor(m_fontDescriptionColor);
		if (m_fontColor.a >= 1.0f)
		{
			m_fontFadeCount++;
			m_isFontFade = true;
			m_fontColor.r = 1.0f;
			m_fontColor.g = 1.0f;
			m_fontColor.b = 1.0f;
			m_fontColor.a = 1.0f;
			m_fontDescriptionColor.r = 1.0f;
			m_fontDescriptionColor.g = 1.0f;
			m_fontDescriptionColor.b = 1.0f;
			m_fontDescriptionColor.a = 1.0f;
			m_fontRender.SetColor(m_fontColor);
			m_fontDescription.SetColor(m_fontDescriptionColor);
		}
	}
	else
	{
		//フォントのフェードアウトの処理。
		m_fontColor.r -= 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.g -= 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.b -= 0.01f * m_timer / m_maxTitleTime;
		m_fontColor.a -= 0.01f * m_timer / m_maxTitleTime;

		m_fontDescriptionColor.r -= 0.01f * m_timer / m_maxTitleTime;
		m_fontDescriptionColor.g -= 0.01f * m_timer / m_maxTitleTime;
		m_fontDescriptionColor.b -= 0.01f * m_timer / m_maxTitleTime;
		m_fontDescriptionColor.a -= 0.01f * m_timer / m_maxTitleTime;

		m_fontRender.SetColor(m_fontColor);
		m_fontDescription.SetColor(m_fontDescriptionColor);
		if (m_fontColor.a <= 0.0f)
		{
			m_isFontFade = false;
			m_fontColor.r = 0.0f;
			m_fontColor.g = 0.0f;
			m_fontColor.b = 0.0f;
			m_fontColor.a = 0.0f;
			m_fontDescriptionColor.r = 0.0f;
			m_fontDescriptionColor.g = 0.0f;
			m_fontDescriptionColor.b = 0.0f;
			m_fontDescriptionColor.a = 0.0f;
			m_fontRender.SetColor(m_fontColor);
			m_fontDescription.SetColor(m_fontDescriptionColor);
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
	m_spriteBack.Draw(rc);
	m_spriteRender.Draw(rc);
	m_spriteSoul.Draw(rc);
	m_fontRender.Draw(rc);
	m_fontDescription.Draw(rc);
}