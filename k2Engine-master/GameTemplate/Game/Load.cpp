#include "stdafx.h"
#include "Load.h"
#include "Game.h"
#include "Tutorial.h"
#include "GameManagement.h"
 
namespace
{
	//フォントの座標。
    const Vector3 FONTRENDER_PSOITION = Vector3{ 850.0f, -430.0f, 0.0f };
	//ロードゲージの進行速度。
    const float LOAD_SPEED = 0.1f;
	//ロードゲージの最大値。
    const float MAX_LOAD = 1.0f;
	//ロードゲージの最小値。
    const float MIN_LOAD = 0.0f;
	//ロードゲージの高さ。
    const float GAUGE_HEIGHT = 150.0f;
}

bool Load::Start()  
{  
    //ロード画像。  
    //m_spriteLoad.Init("Assets/sprite/Load.dds", 1920, 1080);
    m_spriteLoad_1.Init("Assets/sprite/Load_1.dds", 1920, 1080);
    m_spriteLoad_2.Init("Assets/sprite/Load_2.dds", 1920, 1080);
    m_spriteLoad_3.Init("Assets/sprite/Load_3.dds", 1920, 1080);

    tipsList.push_back(&m_spriteLoad_1);
    tipsList.push_back(&m_spriteLoad_2);
    tipsList.push_back(&m_spriteLoad_3);

    //マスク画像。  
    m_spriteMask.Init("Assets/sprite/Black.dds", 100, 150);  
    m_spriteMask.SetPivot(Vector2(0.5f, 0.0f));  

    //ゲージ画像。  
    m_spriteLoadGage.Init("Assets/sprite/gauge.dds", 150, 150);  
    m_spriteLoadGage.SetPosition(FONTRENDER_PSOITION);

    //初期化。  
    m_load = 1.0f;  

    m_gameManagement = FindGO<GameManagement>("gameManagement");

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
    if (m_isLoading)
    {
        m_load -= LOAD_SPEED;
        if (m_load <= MIN_LOAD)
        {
            m_load = MIN_LOAD;
            m_isLoading = false;

            if (m_gameManagement->m_isGame) {
                m_game = NewGO<Game>(0, "game");
            }
            else if (m_gameManagement->m_isOperation) {
                m_tutorial = NewGO<Tutorial>(0, "tutorial");
            }
        }
    }
    else
    {
        m_load += LOAD_SPEED;
        if (m_load >= MAX_LOAD)
        {
            m_load = MAX_LOAD;
        }
    }

    // ロードゲージ処理
    if (m_loadingProgress < MAX_LOAD)
    {
        m_loadingProgress += LOAD_SPEED * g_gameTime->GetFrameDeltaTime();

        if (m_loadingProgress >= MAX_LOAD)
        {
            m_loadingProgress = MAX_LOAD;
            m_isdrawUI = true;

            if (m_gameManagement->m_isGame && m_game) {
                m_game->m_isLoad = false;
            }
            else if (m_gameManagement->m_isOperation && m_tutorial) {
                m_tutorial->m_isLoad = false;
            }

            DeleteGO(this);
        }
    }

    // マスク位置の更新
    float offsetY = m_loadingProgress * GAUGE_HEIGHT;
    m_spriteMask.SetPosition(Vector3(850.0f, -500.0f + offsetY, 0.0f));

    // 各種スプライトの更新
    m_spriteLoadGage.Update();
    m_spriteMask.Update();
}

void Load::Tips()
{
    m_tipTimer += g_gameTime->GetFrameDeltaTime();

    //いずれかのボタンを押してTips更新。
    if (g_pad[0]->IsTriggerAnyKey())
    {
        //Tipsの表示時間をリセット。
        m_tipTimer = 0.0f;
        //更新。
        m_currentTipsIndex = (m_currentTipsIndex + 1) % tipsList.size();
    }

    //時間でもTipsを更新。
    if (m_tipTimer > m_tipsInterval)
    {
        //Tipsの表示時間をリセット。
        m_tipTimer = 0.0f;
        //更新。
        m_currentTipsIndex = (m_currentTipsIndex + 1) % tipsList.size();
    }
}

void Load::Render(RenderContext& rc)
{
    if (!tipsList.empty())
    {
        tipsList[m_currentTipsIndex]->Draw(rc);
    }
    m_spriteLoadGage.Draw(rc);
    m_spriteMask.Draw(rc);}