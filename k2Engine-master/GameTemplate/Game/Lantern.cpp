#include "stdafx.h"
#include "Lantern.h"
#include "Player.h"
#include "Stone.h"
#include "SpriteLight.h"
#include "SpriteNoStone.h"
#include "TimingBarA.h"
#include "TimingBarB.h"
#include "TimingBarC.h"
#include "SpritePush.h"
#include "LanternLight.h"
#include "Game.h"

namespace
{
	//モデルの大きさを設定。
	const Vector3 MODELRENDER_SCALE = Vector3(0.6f, 0.6f, 0.6f);
}

bool Lantern::Start() 
{
	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/lanternJapan/lantern.tkm");
	//インスタンスアドレスを検索。
	auto game = FindGO<Game>("game");
	//モデルの位置を設定。
	m_modelRender.SetScale(MODELRENDER_SCALE);
	

	//各種インスタンスアドレスを検索。
	m_player = FindGO <Player>("player");
	m_stone = FindGO<Stone>("stone");
	m_spriteLight = FindGO<SpriteLight>("spriteLight");
	m_spriteNoStone = FindGO<SpriteNoStone>("spriteNoStone");
	m_spritePush = FindGO<SpritePush>("spritePush");

	return true;
}

Lantern::Lantern() 
{

}

Lantern::~Lantern() 
{

}

void Lantern::Update() 
{
	//モデルレンダーの更新。
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);

	//プレイヤーとの距離ベクトルを計算。
	Vector3 diff = m_position - m_player->m_position;

	//すでに灯っている場合は何もしない。
	if (m_isLight)
	{
		//灯籠に4つ火が灯っていたなら攻撃できる。
		if (m_player->m_lanternCount == 4)
		{
			m_player->m_enemyIsCanAttack = true;
		}
		return;
	}

	//一定以上離れている場合は何もしない。
	if (diff.Length() > m_lightUpDistance)
	{
		ResetLanternState();
		return;
	}

	//「A:火を灯す」表示が出ていなければ出す。
	if (!m_isLightUI)
	{
		m_isLightUI = true;
		m_spriteLight = NewGO<SpriteLight>(0, "spriteLight");
	}

	//点灯処理。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_player->m_stoneCount > 0)
		{
			//火を灯す処理。
			m_player->m_lanternCount++;
			m_player->m_stoneCount--;

			//UIを削除する。
			DeleteGO(m_spriteLight);
			//音を設定して再生する。
			g_soundEngine->ResistWaveFileBank(63, "Assets/sound/lighting.wav");
			m_light = NewGO<SoundSource>(63);
			m_light->Init(63);
			m_light->Play(false);
			//フラグを立てる
			m_isLight = true;
		}
		else if (!m_isNoStoneUI)
		{
			// 火打石がない場合のUI
			m_isNoStoneUI = true;
			m_spriteNoStone = NewGO<SpriteNoStone>(0, "spriteNoStone");
		}
	}
}



void Lantern::ResetLanternState()
{
	//各種フラグをfalseにする。
	m_isLightUI = false;
	m_isNoStoneUI = false;
	m_isLanternAction = false;
	m_buttonAState = 0;

	//画像を削除する。
	if (m_spriteLight != nullptr)
	{
		DeleteGO(m_spriteLight);
		m_spriteLight = nullptr;
	}
	if (m_spriteNoStone != nullptr)
	{
		DeleteGO(m_spriteNoStone);
		m_spriteNoStone = nullptr;
	}
	if (m_spritePush != nullptr)
	{
		DeleteGO(m_spritePush);
		m_spritePush = nullptr;
	}
}

void Lantern::Render(RenderContext& rc) 
{
	m_modelRender.Draw(rc);
}
