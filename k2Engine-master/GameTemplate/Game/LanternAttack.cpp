#include "stdafx.h"
#include "LanternAttack.h"
#include "Player.h"
#include "Stone.h"
#include "SpriteLight.h"
#include "SpriteNoStone.h"

#include "SpritePush.h"

bool LanternAttack::Start() 
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/lanternJapan/lanternAttack.tkm");
	m_modelRender.SetScale(0.6f, 0.6f, 0.6f);

	//各種インスタンスアドレスを検索。
	m_player = FindGO <Player>("player");
	m_stone = FindGO<Stone>("stone");
	m_spriteLight = FindGO<SpriteLight>("spriteLight");
	m_spriteNoStone = FindGO<SpriteNoStone>("spriteNoStone");
	m_spritePush = FindGO<SpritePush>("spritePush");

	m_attack;

	return true;
}

LanternAttack::LanternAttack() 
{

}

LanternAttack::~LanternAttack() 
{
	DeleteGO(m_spriteLight);
	DeleteGO(m_spriteNoStone);
	DeleteGO(m_spritePush);
}

void LanternAttack::Update() 
{
	// モデルレンダーのアップデート
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);

	// プレイヤーとの距離ベクトル
	Vector3 diff = m_player->m_position - m_position;

	// すでに点灯済みなら終了
	if (m_isLight)
	{
		return;
	}

	// 灯籠から離れていたら状態リセット
	if (diff.Length() > 100.0f)
	{
		m_isLightUI = false;
		m_isNoStoneUI = false;
		m_isLanternAttackAction = false;
		m_buttonAState = 0;

		// UI削除
		DeleteGO(m_spriteLight);			m_spriteLight = nullptr;
		DeleteGO(m_spriteNoStone);			m_spriteNoStone = nullptr;
		DeleteGO(m_spritePush);				m_spritePush = nullptr;
		return;
	}

	// UI「A:火を灯す」が出ていなければ出す
	if (!m_isLightUI)
	{
		m_isLightUI = true;
		m_spriteLight = NewGO<SpriteLight>(0, "spriteLight");
	}

	// Aボタンを押した時の処理
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		// 火打石を持っていれば点灯
		if (m_player->m_stoneCount > 0)
		{
			DeleteGO(m_spriteLight); m_spriteLight = nullptr;

			/*// 音再生など
			g_soundEngine->ResistWaveFileBank(63, "Assets/sound/lighting.wav");
			m_light = NewGO<SoundSource>(63);
			m_light->Init(63);
			m_light->Play(false);*/

			m_isLight = true;
			m_player->m_stoneCount--;
			m_lanternCount++;
		}
		else
		{
			// 火打石がない場合、UI表示
			if (!m_isNoStoneUI)
			{
				m_isNoStoneUI = true;
				m_spriteNoStone = NewGO<SpriteNoStone>(0, "spriteNoStone");
			}
		}
	}
}

void LanternAttack::Render(RenderContext& rc) 
{
	m_modelRender.Draw(rc);
}
