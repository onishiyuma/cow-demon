#include "stdafx.h"
#include "Stone.h"
#include "Player.h"
#include "SpriteCollection.h"
#include "sound/SoundEngine.h"
#include "Game.h"


bool Stone::Start() 
{
	//各種インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");
	m_spriteCollection = FindGO<SpriteCollection>("spriteCollection");
	auto game = FindGO<Game>("game");

	//火打石のモデルを読み込む。
	ModelInitData initData;
	initData.m_tkmFilePath = "Assets/modelData/stone/stone.tkm";
	initData.m_expandConstantBuffer = &game->m_luminance;
	initData.m_expandConstantBufferSize = sizeof(game->m_luminance);
	//火打石用のシェーダーを読み込む。
	initData.m_fxFilePath = "Assets/shader/stone.fx";
	m_modelRender.InitForwardRendering(initData);
	m_modelRender.SetScale(0.5f, 0.5f, 0.5f);

	return true;
}

Stone::Stone() 
{

}

Stone::~Stone() 
{
	DeleteGO(m_spriteCollection);
}

void Stone::Update() 
{
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);

	//プレイヤーから火打石に向かうベクトルを計算。
	Vector3 diff = m_player->m_position - m_position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 120.0f)
	{

		if (!m_isNearCollection )
		{

			m_spriteCollection = NewGO<SpriteCollection>(0, "spriteCollection");

			m_isNearCollection = true;
		}
		//Aボタンを押したら
		if (g_pad[0]->IsTrigger(enButtonA))
		{

			//火打石のアイテムカウントを1増やす。
			m_player->m_stoneCount += 1;

			//自身を削除する。
			DeleteGO(this);	
		}
	}
	else 
	{

		m_isNearCollection = false;

		if (m_spriteCollection != nullptr)
		{
			DeleteGO(m_spriteCollection);
			m_spriteCollection = nullptr;
		}	
	}	
}

void Stone::Render(RenderContext& rc) 
{
	m_modelRender.Draw(rc);
}