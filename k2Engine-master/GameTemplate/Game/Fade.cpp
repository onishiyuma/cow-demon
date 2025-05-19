#include "stdafx.h"
#include "Fade.h"
#include "Game.h"

bool Fade::Start()
{
    //ロード画像。
    m_spriteLoad.Init("Assets/sprite/Load.dds",1920,1080);

    //マスク画像。
    m_spriteMask.Init("Assets/sprite/Black.dds", 100, 150);
    m_spriteMask.SetPivot(Vector2(0.5f, 0.0f));

    //ゲージ画像。
    m_spriteLoadGage.Init("Assets/sprite/gauge.dds", 150, 150);
    m_spriteLoadGage.SetPosition(Vector3(850.0f, -430.0f, 0.0f));

    //表示する文字をセットする。
    m_fontRender.SetText(L"Tips:火打石を集めて灯籠を灯すことによって敵に攻撃できるぞ！");
    m_fontRender.SetPosition(-500.0f, -300.0f, 0.0f);

    m_load = 1.0f;

	return true;
}

Fade::Fade()
{
    
}

Fade::~Fade()
{

}

void Fade::Update()
{
    // ゲージ進行。
    LoadingProgress();
}

void Fade::LoadingProgress()
{
    // フェード制御。
    if (m_isFadingOut) 
    {
        m_load -= 0.01f;
        if (m_load <= 0.0f) 
        {
            NewGO<Game>(0, "game");
            m_load = 0.0f;
            m_isFadingOut = false;
        }
    }
    else
    {
        m_load += 0.01f;
        if (m_load >= 1.0f)
        {
            m_load = 1.0f;
        }
    }

    //ロードのゲージ処理。
    if (m_loadingProgress < 1.0f)
    {
        m_loadingProgress += 0.1f * g_gameTime->GetFrameDeltaTime();
        if (m_loadingProgress > 1.0f)
        {
            m_loadingProgress = 1.0f;
            m_drawUI = true;
            DeleteGO(this);
        }
    }

    // マスク位置の更新。
    float fullHeight = 150.0f;
    float offsetY = m_loadingProgress * fullHeight;
    m_spriteMask.SetPosition(Vector3(850.0f, -500.0f + offsetY, 0.0f));

    //各種アップデート。
    m_spriteLoadGage.Update();
    m_spriteMask.Update();
}

void Fade::Render(RenderContext& rc)
{
    m_spriteLoad.Draw(rc);
    m_spriteLoadGage.Draw(rc);
    m_spriteMask.Draw(rc);
    m_fontRender.Draw(rc);
}


