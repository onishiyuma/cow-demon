#include "stdafx.h"
#include "LanternArrow.h"
#include "Game.h"

LanternArrow::LanternArrow()
{

}

LanternArrow::~LanternArrow()
{

}

bool LanternArrow::Start()
{
	//インスタンスアドレスを検索。
	auto game = FindGO<Game>("Game");

	//画像を読み込む
	m_modelRender.Init("Assets/modelData/offeringBox/arrow.tkm");

	//回転を設定。
	m_rotation.SetRotationDegY(90);

	//座標を代入。
	m_movePosition = m_position;

	return true;
}

void LanternArrow::Update()
{
	//モデルを更新。
	m_modelRender.Update();

	m_modelRender.SetPosition(m_movePosition);
	m_modelRender.SetScale(m_scale);

	Move();
}

void LanternArrow::Move()
{

	m_timer += g_gameTime->GetFrameDeltaTime();
	
	switch (m_moveState)
	{
	case enMoveState_UP:
		m_movePosition.y += 20.0f / m_timer;
		if (m_movePosition.y >= m_position.y + 20.0f) {
			m_moveState = enMoveState_Down;		
		}
		break;
	case enMoveState_Down:
		m_movePosition.y -= 20.0f / m_timer;
		if (m_movePosition.y <= m_position.y - 20.0f) {
			m_moveState = enMoveState_UP;
		}
		break;
	default:
		break;
	}
	

	m_modelRender.SetPosition(m_movePosition);
}

void LanternArrow::Rotation()
{

}

void LanternArrow::Render(RenderContext&rc)
{
	m_modelRender.Draw(rc);
}	