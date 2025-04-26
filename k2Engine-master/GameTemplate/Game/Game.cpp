#include "stdafx.h"
#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "CrossHair.h"
#include "Stone.h"
#include "UIStone.h"
#include "Lantern.h"
#include "LanternAttack.h"
#include "MiniMap.h"
#include "LittleEnemy.h"
#include "UItukuyomi.h"
#include "UIskill.h"
#include "UISimenawa.h"
#include "UIcurseBar.h"
#include "UIheal.h"
#include "RingBell.h"
#include "GameClear.h"
#include "GameOver.h"


bool Game::Start()
{

	//繧ｹ繝・・繧ｸ蜈ｨ菴薙ｒ證励￥縺吶ｋ縲・
	g_sceneLight->SetAmbient(Vector3(0.0001f, 0.0001f, 0.0001f));

	g_sceneLight->SetDirectionLight(0, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));

	//蛻ｶ髯先凾髢薙・險ｭ螳壹・
	m_timeLimit =120.0f;

	//閭梧勹縺ｮ菴懈・縲・
	m_backGround = NewGO<BackGround>(0);

	//繝吶Ν縺ｮ菴懈・縲・
	m_ringBell = NewGO<RingBell>(0, "ringbell");

	//繝励Ξ繧､繝､繝ｼ縺ｮ菴懈・縲・
	m_player = NewGO<Player>(0, "player");

	//繧ｲ繝ｼ繝繧ｫ繝｡繝ｩ縺ｮ菴懈・縲・
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//繧ｯ繝ｭ繧ｹ繝倥い繝ｼ繧定｡ｨ遉ｺ縲・
	m_crossHair = NewGO<CrossHair>(0);

	//繝・ヰ繝・け逕ｨ縲・
	//m_timeLimit = 3.0f;

	//・ｽ・ｽﾌ背・ｽi・ｽ・ｬ
	//SkyCube* skyCube = NewGO<SkyCube>(0);
	//skyCube->SetType(enSkyCubeType_NightToon);
	//skyCube->SetScale(1000.0f);
	
	//轣ｫ謇鍋浹縺ｮ菴懈・縲・
	CreateStone();

	//轣ｯ邀縺ｮ菴懈・縲・
	CreateLantern();

	//謾ｻ謦・畑轣ｯ邀縺ｮ菴懈・縲・
	CreateAttackLantern();

	//轣ｫ謇鍋浹縺ｮ繧ｫ繧ｦ繝ｳ繝医ｒ陦ｨ遉ｺ縲・
	m_uiStone = NewGO<UIStone>(0, "uiStone");

	//UI縺ｮ菴懈・
	CreateUI();

	//Enemy縺ｮ菴懈・
	CreateEnemy();
	
	return true;
}

Game::Game()
{

}

Game::~Game()
{
	//迚幃ｬｼ
	for (auto* enemy : m_enemyList) {
		DeleteGO(enemy);
	}

	//繝溘ル迚幃ｬｼ
	for (auto* littleEnemy : m_littleEnemyList) {
		DeleteGO(littleEnemy);
	}

	DeleteGO(m_player); //繝励Ξ繧､繝､繝ｼ
	DeleteGO(m_gameCamera); //繧ｲ繝ｼ繝繧ｫ繝｡繝ｩ
	DeleteGO(m_backGround); //繧ｹ繝・・繧ｸ
	DeleteGO(m_crossHair); //繧ｯ繝ｭ繧ｹ繝倥い繝ｼ
	DeleteGO(m_ringBell); //繝吶Ν

	//轣ｫ謇鍋浹縲・
	DeleteGO(m_stone1);
	DeleteGO(m_stone2);
	DeleteGO(m_stone3);
	DeleteGO(m_stone4);
	DeleteGO(m_stone5);
	DeleteGO(m_stone6);
	DeleteGO(m_stone7);

	//轣ｯ邀縲・
	DeleteGO(m_lantern1);
	DeleteGO(m_lantern2);
	DeleteGO(m_lantern3);
	DeleteGO(m_lantern4);

	//謾ｻ謦・畑轣ｯ邀縲・
	DeleteGO(m_lanternAttack1);
	DeleteGO(m_lanternAttack2);
	DeleteGO(m_lanternAttack3);

	//UI髢｢騾｣縲・
	DeleteGO(m_littleEnemy);
	DeleteGO(m_uiTukuyomi);
	DeleteGO(m_uiSkill);
	DeleteGO(m_uiSimenawa);
	DeleteGO(m_uiCurseBar);
	DeleteGO(m_uiHeal);
	DeleteGO(m_uiStone);
	DeleteGO(m_miniMap);

	
}

void Game::Update()
{
	wchar_t wcsbuf[256];

	int minute = (int)m_timer / 60;

	int sec = (int)m_timer % 60;
	swprintf_s(wcsbuf, 256, L"AM%01d:%02d", minute, sec);


	//陦ｨ遉ｺ縺吶ｋ繝・く繧ｹ繝医ｒ陦ｨ遉ｺ
	m_timerFontRender.SetText(wcsbuf);
	//繝輔か繝ｳ繝医・菴咲ｽｮ繧定ｨｭ螳・
	m_timerFontRender.SetPosition(Vector3(0.0f, 500.0f, 0.0f));
	//繝輔か繝ｳ繝医・濶ｲ繧定ｨｭ螳・
	m_timerFontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });
	//繝輔か繝ｳ繝医・螟ｧ縺阪＆繧定ｨｭ螳・
	m_timerFontRender.SetScale(1.5f);

	m_timer += g_gameTime->GetFrameDeltaTime();

	GameManager();
}

Vector3 Game::Random()
{
	Vector3 m_position;
	//繝ｩ繝ｳ繝繝縺ｫ繝昴ず繧ｷ繝ｧ繝ｳ繧貞ｽ薙※縺ｯ繧√ｋ
	m_position.x = rand() % 800 - 400;
	m_position.y = 0.0f;
	m_position.z = rand() % 1000 + 500;
	return m_position;
}


//繧ｲ繝ｼ繝繧ｯ繝ｪ繧｢縲√ご繝ｼ繝繧ｪ繝ｼ繝舌・縺ｮ蛻､螳壼・逅・・
void Game::GameManager()
{
	//繧ｿ繧､繝槭・繧呈ｸ帙ｉ縺吝・逅・・
	m_timeLimit -= g_gameTime->GetFrameDeltaTime();

	//謨ｵ縺九ｉ譛ｬ谿ｿ繧貞ｮ医ｊ蛻・▲縺溘ｉ繧ｲ繝ｼ繝繧ｯ繝ｪ繧｢縲・
	if (m_timeLimit <= 0)
	{
		NewGO<GameClear>(0);
		DeleteGO(this);
	}


	//蜻ｪ縺・・謚ｵ謚怜､縺後↑縺上↑縺｣縺溘ｉ縲・
	if (m_player->m_playerHP <= 0)
	{
		NewGO<GameOver>(0);
		DeleteGO(this);
	}
}

//轣ｫ謇鍋浹菴懈・逕ｨ髢｢謨ｰ縲・
void Game::CreateStone()
{
	// 轣ｫ謇鍋浹繧定｡ｨ遉ｺ縲・
	m_stone1 = NewGO<Stone>(0, "stone1");
	m_stone1->m_position = { 1000.0f,0.0f,-500.0f };
	m_stone1->m_firstPosition = m_stone1->m_position;
	//m_stone1 = FindGO<Stone>("stone");

	m_stone2 = NewGO<Stone>(0, "stone2");
	m_stone2->m_position = { 200.0f,0.0f,-2000.0f };
	m_stone2->m_firstPosition = m_stone2->m_position;
	//m_stone2 = FindGO<Stone>("stone");

	m_stone3 = NewGO<Stone>(0, "stone3");
	m_stone3->m_position = { -1200.0f,0.0f,500.0f };
	m_stone3->m_firstPosition = m_stone3->m_position;

	m_stone4 = NewGO<Stone>(0, "stone4");
	m_stone4->m_position = { 2000.0f,0.0f,-2000.0f };
	m_stone4->m_firstPosition = m_stone4->m_position;

	m_stone5 = NewGO<Stone>(0, "stone5");
	m_stone5->m_position = { -2300.0f,0.0f,-2200.0f };
	m_stone5->m_firstPosition = m_stone5->m_position;

	m_stone6 = NewGO<Stone>(0, "stone6");
	m_stone6->m_position = { 0.0f,0.0f,500.0f };
	m_stone6->m_firstPosition = m_stone6->m_position;

	m_stone7 = NewGO<Stone>(0, "stone7");
	m_stone7->m_position = { 0.0f,0.0f,-500.0f };
	m_stone7->m_firstPosition = m_stone7->m_position;
}

//轣ｯ邀菴懈・逕ｨ髢｢謨ｰ縲・
void Game::CreateLantern()
{
	//轣ｯ邀縺ｮ繝｢繝・Ν繧定｡ｨ遉ｺ
	m_lantern1 = NewGO<Lantern>(0, "lantern1");
	m_lantern1->m_position = { 500.0f,-50.0f,500.0f };
	m_lantern1->m_firstPosition = m_lantern1->m_position;
	//m_lantern1 = FindGO<Lantern>("lantern1");

	m_lantern2 = NewGO<Lantern>(0, "lantern2");
	m_lantern2->m_position = { 500.0f,-50.0f,-500.0f };
	m_lantern2->m_firstPosition = m_lantern2->m_position;
	//m_lantern2 = FindGO<Lantern>("lantern2");

	m_lantern3 = NewGO<Lantern>(0, "lantern3");
	m_lantern3->m_position = { -500.0f,-50.0f,500.0f };
	m_lantern3->m_firstPosition = m_lantern3->m_position;
	//m_lantern3= FindGO<Lantern>("lantern3");

	m_lantern4 = NewGO<Lantern>(0, "lantern4");
	m_lantern4->m_position = { -500.0f,-50.0f,-500.0f };
	m_lantern4->m_firstPosition = m_lantern4->m_position;
	//m_lantern4 = FindGO<Lantern>("lantern4");
}

//謾ｻ謦・・邀縺ｮ菴懈・逕ｨ髢｢謨ｰ
void Game::CreateAttackLantern()
{
	//謾ｻ謦・畑轣ｯ邀縺ｮ繝｢繝・Ν繧定｡ｨ遉ｺ
	m_lanternAttack1 = NewGO<LanternAttack>(0, "lanternAttack1");
	m_lanternAttack1->m_position = { 700.0f,-50.0f,2000.0f };
	m_lanternAttack1->m_firstPosition = m_lanternAttack1->m_position;
	//m_lantern1 = FindGO<Lantern>("lantern1");

	m_lanternAttack2 = NewGO<LanternAttack>(0, "lanternAttack2");
	m_lanternAttack2->m_position = { -700.0f,-50.0f,2000.0f };
	m_lanternAttack2->m_firstPosition = m_lanternAttack2->m_position;
	//m_lantern2 = FindGO<Lantern>("lantern2");

	m_lanternAttack3 = NewGO<LanternAttack>(0, "lanternAttack3");
	m_lanternAttack3->m_position = { 100.0f,-50.0f,1600.0f };
	m_lanternAttack3->m_firstPosition = m_lanternAttack3->m_position;
	//m_lantern3= FindGO<Lantern>("lantern3");
}

void Game::CreateEnemy()
{

	for (int i = 0; i < 5; i++)
	{

		int ram = rand() % 100;
		if (ram > 30)
		{
			Enemy* enemy = NewGO<Enemy>(1, "enmy");
			enemy->SetPosition(Random());
			m_enemyList.push_back(enemy);//謨ｵ繝ｪ繧ｹ繝医↓霑ｽ蜉
		}
		else
		{
			LittleEnemy* littleEnemy = NewGO<LittleEnemy>(1, "littleEnemy");
			littleEnemy->SetPosition(Random());
			m_littleEnemyList.push_back(littleEnemy);//繝ｪ繝医Ν謨ｵ繝ｪ繧ｹ繝医↓霑ｽ蜉
		}
	}
}

//UI菴懈・逕ｨ髢｢謨ｰ縲・
void Game::CreateUI()
{
	//譛郁ｪｭ縺ｮ蜉隴ｷ縺ｮUI
	m_uiTukuyomi = NewGO<UItukuyomi>(0, "uitukuyomi");
	//繧ｹ繧ｭ繝ｫUI
	m_uiSkill = NewGO<UIskill>(0, "uiskill");
	//縺励ａ邵ФI
	m_uiSimenawa = NewGO<UISimenawa>(0, "uisimenawa");
	//繝溘ル繝槭ャ繝・
	//m_miniMap = NewGO<MiniMap>(0, "minimap");
	//蜻ｪ繧ｲ繝ｼ繧ｸ
	m_uiCurseBar = NewGO<UIcurseBar>(0, "uicursebar");
	//蝗槫ｾｩ
	m_uiHeal = NewGO <UIheal>(0, "uiheal");
}


void Game::Render(RenderContext& rc)
{
	m_timerFontRender.Draw(rc);
}