#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"
#include "sound/SoundEngine.h"


bool GameOver::Start()
{
	//ゲームオーバーの画像を読み込む。
	m_spriteRender.Init("Assets/sprite/GameOver.DDS", 1920.0f, 1080.0f);

	g_soundEngine->ResistWaveFileBank(3,"Assets/sound/gameOver.wav");
	m_gameOverBGM = NewGO<SoundSource>(3);
	m_gameOverBGM->Init(3);
	m_gameOverBGM->Play(false);

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

	if (m_titleTime >= m_maxTitleTIme)
	{
		//タイトルに戻る処理。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			NewGO<Title>(0);

			DeleteGO(this);
		}
	}
}

void GameOver::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}