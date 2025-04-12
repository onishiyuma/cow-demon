#include "stdafx.h"
#include "UISimenawa.h"
#include "Player.h";
#include "Game.h";

namespace
{
	//しめ縄
	Vector3 ROPE_FREME_POSITION = Vector3(435.0f, -425.0f, 0.0f);
	//しめ縄ゲージ
	Vector3 ROPE_GAUGE_POSITION = Vector3(435.0f, -486.0f, 0.0f);
	//黒
	Vector4 BLACK = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

UISimenaw::UISimenaw()
{

}

UISimenaw::~UISimenaw()
{

}

bool UISimenaw::Start()
{
	//ロープゲージ
	m_RopeGage.Init("Assets/UI/Red.DDS", 120, 14);
	m_RopeGage.SetPosition(ROPE_GAUGE_POSITION);
	m_RopeGage.SetPivot(Vector2{ 0.5f, 0.0f });
	m_RopeGage.SetMulColor(BLACK);

	//ロープの画像
	m_RopeSprite.Init("Assets/UI/aitemskil1.DDS", 130, 130);
	m_RopeSprite.SetPosition(ROPE_FREME_POSITION);

	return true;
}

void UISimenaw::Update()
{
	m_RopeTimer += g_gameTime->GetFrameDeltaTime();
	float wari = (float)m_RopeTimer / 2.6;
	Vector3 scal = { 1.0f,1.0f,1.0f };
	scal.y += wari;

	if (m_RopeTimer <= 20) {
		m_RopeGage.SetScale(scal);
	}
	else {

	}
	m_RopeSprite.Update();
	m_RopeGage.Update();
}

void UISimenaw::Render(RenderContext& rc)
{
	if (m_RopeTimer > 0) {
		m_RopeGage.Draw(rc);
	}
	m_RopeSprite.Draw(rc);
}