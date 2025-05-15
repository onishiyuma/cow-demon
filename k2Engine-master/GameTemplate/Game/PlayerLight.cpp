#include "stdafx.h"
#include "PlayerLight.h"
#include "Player.h"

PlayerLight::PlayerLight()
{

}

PlayerLight::~PlayerLight()
{

}

bool PlayerLight::Start()
{
	m_player = FindGO<Player>("player");

	// スポットライトを初期化。
	m_spotLight.Init();
	//ライトの影響距離を設定。
	m_spotLight.SetRange(800.0f);
	//ライトの影響角度を設定。
	m_spotLight.SetAngle(Math::DegToRad(75.0f));
	//ライトの距離減衰率を設定。
	m_spotLight.SetRangeAffectPowParam(10.0f);
	//ライトの角度減衰率を設定。
	m_spotLight.SetAngleAffectPowParam(0.1f);
	//ライトの色を設定。
	m_spotLight.SetColor(1.0f, 1.0f, 1.0f);
	//ライトの方向を設定。
	m_spotLight.SetDirection(m_direction);
	//ライトの座標を設定。
	m_spotLight.SetPosition(m_player->m_position);

	return true;
}

void PlayerLight::Update()
{
	//ライトの座標を設定。
	m_spotLight.SetPosition(m_player->m_position + Vector3(0.0f, 10.0f, 0.0f));
	//ライトの方向を設定。
	//m_spotLight.SetDirection(0.0f,1.0f,1.0f);
	m_direction = g_camera3D->GetForward();
	m_direction.Normalize();
	m_spotLight.SetDirection(m_direction);
	//ライトを更新。3q
	m_spotLight.Update();
}

void PlayerLight::Render(RenderContext& rc)
{

}
