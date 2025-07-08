#include "stdafx.h"
#include "PlayerLight.h"
#include "Player.h"

namespace
{
	const float SPOT_LIGHT_RANGE = 800.0f;
	const float SPOT_LIGHT_ANGLE_DEG = 75.0f;
	const float RANGE_AFFECT_POWER = 10.0f;
	const float ANGLE_AFFECT_POWER = 0.1f;
	const Vector3 LIGHT_OFFSET(0.0f, 10.0f, 0.0f);
}

PlayerLight::PlayerLight()
{

}

PlayerLight::~PlayerLight()
{

}

bool PlayerLight::Start()
{
	//インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");

	// スポットライトを初期化。
	m_spotLight.Init();
	//ライトの影響距離を設定。
	m_spotLight.SetRange(SPOT_LIGHT_RANGE);
	//ライトの影響角度を設定。
	m_spotLight.SetAngle(Math::DegToRad(SPOT_LIGHT_ANGLE_DEG));
	//ライトの距離減衰率を設定。
	m_spotLight.SetRangeAffectPowParam(RANGE_AFFECT_POWER);
	//ライトの角度減衰率を設定。
	m_spotLight.SetAngleAffectPowParam(ANGLE_AFFECT_POWER);
	//ライトの色を設定。
	m_spotLight.SetColor(Vector3::One);
	//ライトの方向を設定。
	m_spotLight.SetDirection(m_forward);
	//ライトの座標を設定。
	m_spotLight.SetPosition(m_player->m_position);

	return true;
}

void PlayerLight::Update()
{
	//ライトの座標を設定。
	m_spotLight.SetPosition(m_player->m_position + LIGHT_OFFSET);
	//前方向を取ってくる。
	m_forward = g_camera3D->GetForward();
	//正規化。
	m_forward.Normalize();
	//方向を前にする。
	m_spotLight.SetDirection(m_forward);
	//ライトを更新。
	m_spotLight.Update();
}

void PlayerLight::Render(RenderContext& rc)
{

}
