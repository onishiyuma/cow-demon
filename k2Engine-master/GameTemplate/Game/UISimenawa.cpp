#include "stdafx.h"
#include "UISimenawa.h"
#include "Player.h"
#include "Game.h"

namespace
{
	//しめ縄
	Vector3 ROPE_FREME_POSITION = Vector3(435.0f, -425.0f, 0.0f);
	//しめ縄ゲージ
	Vector3 ROPE_GAUGE_POSITION = Vector3(435.0f, -486.0f, 0.0f);
	//緑
	Vector4 GREEN = Vector4(0.0f,1.0f,0.0f,1.0f);
	//薄い緑
	Vector4 LIGHT_GREEN = Vector4(0.0f, 1.0f, 0.0f, 0.2f);
}

UISimenawa::UISimenawa()
{

}

UISimenawa::~UISimenawa()
{

}

bool UISimenawa::Start()
{
	//インスタンスアドレスを検索。
	m_player=FindGO<Player>("player");

	//ロープゲージ
	m_ropeGage.Init("Assets/UI/White.DDS", 120, 14);
	m_ropeGage.SetPosition(ROPE_GAUGE_POSITION);
	m_ropeGage.SetPivot(Vector2{ 0.5f, 0.0f });

	//ロープの画像
	m_ropeSprite.Init("Assets/UI/aitemskil1.DDS", 130, 130);
	m_ropeSprite.SetPosition(ROPE_FREME_POSITION);
	
	return true;
}

void UISimenawa::Update()
{

	m_ropeTimer = m_player->m_shimenawaGetTime;
	float wari = (float)m_ropeTimer / 2.6;
	Vector3 scal = { 1.0f,1.51f,1.0f };
	scal.y *= wari;

	if (m_ropeTimer <= m_player->m_collectTime)
	{
		m_ropeGage.SetScale(scal);
		m_ropeGage.SetMulColor(LIGHT_GREEN);
	}
	else
	{
		m_ropeGage.SetMulColor(GREEN);
	}

	m_ropeSprite.Update();
	m_ropeGage.Update();
}

void UISimenawa::Render(RenderContext& rc)
{
	if (m_ropeTimer > 0) 
	{
		m_ropeGage.Draw(rc);
	}

	m_ropeSprite.Draw(rc);
}