#include "stdafx.h"
#include "Tutorial.h"
#include "GameManagement.h"
#include "GameCamera.h"
#include "Player.h"
#include "Enemy.h"
#include "BackGround.h"
#include "CrossHair.h"
#include "UItukuyomi.h"
#include "UIskill.h"
#include "UISimenawa.h"
#include "UIcurseBar.h"
#include "UIheal.h"
#include "SpriteAttack.h"
#include "SpriteSkil.h"
#include "SpriteSimenawa.h"
#include "SpriteTukuyomi.h"
#include "Load.h"
#include "Title.h"

Tutorial::Tutorial()
{

}

Tutorial::~Tutorial()
{

}

bool Tutorial::Start()
{

	//ステージ全体を暗くする。
	g_sceneLight->SetAmbient(Vector3(0.0001f, 0.0001f, 0.0001f));
	g_sceneLight->SetDirectionLight(0, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	//空の作成。
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetScale(1000.0f);

	//空の光の強さ。
	m_skyCube->SetLuminance(0.0001f);
	//空の光から影響する環境光の強さ
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.0001f);

	m_gameManagement = FindGO<GameManagement>("gameManagement");

	m_backGround = NewGO<BackGround>(0, "backGround");

	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_player = NewGO<Player>(0, "player");

	//m_enemy = NewGO<Enemy>(0, "enemy");
	//m_enemy->SetPosition(m_enemyPos);

	CreateUI();

	ButtonUI();

	Font();

	return true;
}

void Tutorial::Update()
{

	m_timer += g_gameTime->GetFrameDeltaTime();

	if (m_timer >= 13.0f) {

		State();

		if (g_pad[0]->IsPress(enButtonB)) {

			m_clearCount = 4;

		}
	}
	

	//m_enemy->SetPosition(m_enemyPos);
}

void Tutorial::CreateUI()
{
	//クロスヘアーを表示。
	m_crossHair = NewGO<CrossHair>(0);
	//月読の加護のUI。
	m_uiTukuyomi = NewGO<UItukuyomi>(0, "uitukuyomi");
	//スキルUI。
	m_uiSkill = NewGO<UIskill>(0, "uiskill");
	//しめ縄UI。
	m_uiSimenawa = NewGO<UISimenawa>(0, "uisimenawa");
	//呪ゲージ。
	m_uiCurseBar = NewGO<UIcurseBar>(0, "uicursebar");
	//回復。
	m_uiHeal = NewGO <UIheal>(0, "uiheal");
	
}

void Tutorial::Font()
{
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"チュートリアル:%d", int(m_clearCount));

	//表示するテキストを設定。
	m_fontClearCount.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_fontClearCount.SetPosition(Vector3(-900.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontClearCount.SetScale(1.5f);
	//フォントの色を設定。
	m_fontClearCount.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//表示するテキストを設定。
	m_fontClearCount1.SetText(L"/4");
	//フォントの位置を設定。
	m_fontClearCount1.SetPosition(Vector3(-370.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontClearCount1.SetScale(1.5f);
	//フォントの色を設定。
	m_fontClearCount1.SetColor({ 1.0f,1.0f,1.0f,1.0f });
}

void Tutorial::ButtonUI()
{

	//「チュートリアルをスキップする」の文字の読み込み。
	m_skip.SetText(L":チュートリアルを終了する");
	m_skip.SetPosition(Vector3(-800.0f, 380.0f, 0.0f));
	m_skip.SetScale(1.0f);
	m_skip.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//Bボタン
	m_bButton.Init("Assets/sprite/B.DDS", 1920, 1080);
	m_bButton.SetPosition({ -850.0f,350.0f,0.0f });
	m_bButton.SetScale({ 0.5f,0.5f,0.5f });
	m_bButton.Update();

	//通常攻撃
	m_fontNomalAttack.SetText(L":通常攻撃");
	m_fontNomalAttack.SetPosition(Vector3(-730.0f, -160.0f, 0.0f));
	m_fontNomalAttack.SetScale(1.0f);
	m_fontNomalAttack.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	//Xボタン
	m_xButton.Init("Assets/sprite/X.DDS", 1920, 1080);
	m_xButton.SetPosition({ 710.0f,-520.0f,0.0f });
	m_xButton.SetScale({ 0.3f,0.3f,0.3f });
	m_xButton.Update();

	//Yボタン
	m_yButton.Init("Assets/sprite/Y.DDS", 1920, 1080);
	m_yButton.SetPosition({ 420.0f,-520.0f,0.0f });
	m_yButton.SetScale({ 0.3f,0.3f,0.3f });
	m_yButton.Update();

	//LTボタン
	m_ltButton.Init("Assets/sprite/LT.DDS", 1920, 1080);
	m_ltButton.SetPosition({ 570.0f,-520.0f,0.0f });
	m_ltButton.SetScale({ 0.3f,0.3f,0.3f });
	m_ltButton.Update();

	//RTボタン
	m_rtButton.Init("Assets/sprite/RT.DDS", 1920, 1080);
	m_rtButton.SetPosition({ -800.0f,-200.0f,0.0f });
	m_rtButton.SetScale({ 0.5f,0.5f,0.5f });
	m_rtButton.Update();
}

void Tutorial::State()
{
	switch (m_clearCount)
	{
	case 0:
		NormalAttack();
		break;
	case 1:
		Skill();
		break;
	case 2:
		Simenawa();
		break;
	case 3:
		Protection();
		break;
	case 4:
		End();
		break;
	}
}

//通常攻撃
void Tutorial::NormalAttack()
{
	if (m_isSprite == false) {
		m_spriteAttack = NewGO<SpriteAttack>(0, "spriteAttack");
		m_isSprite = true;
		if (m_isClear == true) {
			if (m_isClearSprite == true) {
				
			}
		}
		
	}
}

//スキル
void Tutorial::Skill()
{

}

//しめ縄
void Tutorial::Simenawa()
{

}

//ツクヨミの加護
void Tutorial::Protection()
{

}

//チュートリアルの終了処理
void Tutorial::End()
{
	if (m_isEnd = false) {

		m_isEnd = true;

		m_tutorialEnd.SetText(L"チュートリアルを終了します");
		m_tutorialEnd.SetPosition(Vector3(0.0f, 100.0f, 0.0f));
		m_tutorialEnd.SetScale(1.5f);
		m_tutorialEnd.SetColor({ 1.0f,0.0f,0.0f,1.0f });

		m_endTimer += g_gameTime->GetFrameDeltaTime();

		if (m_endTimer >= 5.0f) {

			DeleteGO(m_gameManagement);
			m_gameManagement = NewGO<GameManagement>(0, "gameManagement");
			m_title = NewGO<Title>(0, "Title");
			DeleteGO(this);
		}
	}
	
}

void Tutorial::Render(RenderContext& rc)
{
	m_fontClearCount.Draw(rc);
	m_fontClearCount1.Draw(rc);
	m_tutorialEnd.Draw(rc);
	m_skip.Draw(rc);
	m_bButton.Draw(rc);
	m_fontNomalAttack.Draw(rc);
	m_xButton.Draw(rc);
	m_yButton.Draw(rc);
	m_ltButton.Draw(rc);
	m_rtButton.Draw(rc);
}