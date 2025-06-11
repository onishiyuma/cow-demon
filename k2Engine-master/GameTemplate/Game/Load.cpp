#include "stdafx.h"
#include "Load.h"
#include "Game.h"
 
namespace
{
    Vector3 FONTRENDER_PSOITION = Vector3{ -600.0f, -300.0f, 0.0f };
}

bool Load::Start()  
{  
    //ロード画像。  
    m_spriteLoad.Init("Assets/sprite/Load.dds",1920,1080);  

    //マスク画像。  
    m_spriteMask.Init("Assets/sprite/Black.dds", 100, 150);  
    m_spriteMask.SetPivot(Vector2(0.5f, 0.0f));  

    //ゲージ画像。  
    m_spriteLoadGage.Init("Assets/sprite/gauge.dds", 150, 150);  
    m_spriteLoadGage.SetPosition(Vector3(850.0f, -430.0f, 0.0f));  

    // Tipsリストを初期化  
    tipsList = {
        L"Tips「5時まで本殿を守り続けるとゲームクリアだ」",
        L"Tips「火打石を集めて灯籠を灯すことによって敵に攻撃できるぞ」",
        L"Tips「本殿にある鐘を鳴らすことで回復できるぞ」"
    };

    std::wstring wstr(tipsList[m_currentTipsIndex].begin(), tipsList[m_currentTipsIndex].end());
    m_fontRenderTips.SetText(wstr.c_str());
	m_fontRenderTips.SetPosition(FONTRENDER_PSOITION);

    //初期化。  
    m_load = 1.0f;  

    return true;  
}

Load::Load()
{
    
}

Load::~Load()
{

}

void Load::Update()
{
    //ゲージ進行。
    LoadingProgress();

    Tips();
}

void Load::LoadingProgress()
{
    //ロード制御。
    if (m_isFadingOut) 
    {
        m_load -= 0.1f;
        if (m_load <= 0.0f) 
        {
            m_game=NewGO<Game>(0, "game");
            m_load = 0.0f;
            m_isFadingOut = false;
        }
    }
    else
    {
        m_load += 0.1f;
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
            m_game->m_isLoad = false;
            DeleteGO(this);
        }
    }

    //マスク位置の更新。
    float fullHeight = 150.0f;
    float offsetY = m_loadingProgress * fullHeight;
    m_spriteMask.SetPosition(Vector3(850.0f, -500.0f + offsetY, 0.0f));

    //各種アップデート。
    m_spriteLoadGage.Update();
    m_spriteMask.Update();
}

void Load::Tips()
{
	//時間経過でTipsを更新。
    if (g_pad[0]->IsTriggerAnyKey())
    {
        //Tipsの表示時間をリセット。
        m_tipTimer = 0.0f;
        //Tipsのインデックスを更新。
        m_currentTipsIndex = (m_currentTipsIndex + 1) % tipsList.size();
        //表示するTipsを更新。
        std::wstring wstr(tipsList[m_currentTipsIndex].begin(), tipsList[m_currentTipsIndex].end());
        m_fontRenderTips.SetText(wstr.c_str());
    }
}

void Load::Render(RenderContext& rc)
{
    m_spriteLoad.Draw(rc);
    m_spriteLoadGage.Draw(rc);
    m_spriteMask.Draw(rc);
    m_fontRenderTips.Draw(rc);
}