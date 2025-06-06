#include "stdafx.h"
#include "RingBell.h"
#include "collision/CollisionObject.h"
#include "Player.h"

namespace
{
	Vector3 MODEL_SCALE{ 0.7f, 0.7f, 0.7f };
}


bool RingBell::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/offeringBox/offeringBox.tkm");
	//画像を読み込む
	m_arrowModel.Init("Assets/modelData/offeringBox/arrow.tkm");
	//座標を設定する。
	m_modelRender.SetPosition(m_position);
	//大きさを設定する。
	m_modelRender.SetScale(MODEL_SCALE);
	//画像の座標を設定する。
	m_arrowModel.SetPosition(m_arrwPosition);
	m_rotation.SetRotationDegY(90);
	m_arrowModel.SetRotation(m_rotation);
	//現在の座標に初期座標を代入。
	m_currentPosition = m_arrwPosition;
	//インスタンスアドレスを検索。
	m_player=FindGO<Player>("player");
	//コリジョン作成用関数を呼び出す。
	CreateCollision();
	//コリジョンの座標を設定する。
	m_collisionObject->SetPosition(m_position);
	//更新。
	m_collisionObject->Update();
	return true;
}

RingBell::RingBell()
{

}

RingBell::~RingBell()
{

}

void RingBell::Update()
{
	MoveArrow();
	m_modelRender.Update();
	m_arrowModel.Update();

}

//コリジョンを作成。
void RingBell::CreateCollision()
{
	//コリジョンのインスタンスを作成。
	m_collisionObject= NewGO<CollisionObject>(0);

	//箱状のコリジョンを作成する。
	m_collisionObject->CreateBox(m_position, Quaternion::Identity, {m_collisionScale});

	//コリジョンに名前をつける。
	m_collisionObject->SetName("ringbell");
	//オブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);
}

void RingBell::MoveArrow()
{
	switch (m_moveState)
	{
	case enMoveState_UP:
		m_currentPosition.y += 65*g_gameTime->GetFrameDeltaTime();
		if (m_currentPosition.y >= m_arrwPosition.y+50)
		{
			m_currentPosition.y = m_arrwPosition.y + 10;
			m_moveState = enMoveState_Down;
		}
		break;
	case enMoveState_Down:
		m_currentPosition.y -= 5*g_gameTime->GetFrameDeltaTime();
		if (m_currentPosition.y <= m_arrwPosition.y + 100)
		{
			m_currentPosition.y = m_arrwPosition.y - 10;
			m_moveState = enMoveState_UP;
		}
		break;
	default:
		break;
	}


	m_arrowModel.SetPosition(m_currentPosition);
}

void RingBell::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	if (!m_player->m_isDisplay)
	{
		return;
	}
	m_arrowModel.Draw(rc);
}
