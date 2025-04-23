#include "stdafx.h"
#include "EnemyBase.h"
#include "Game.h"
#include "Player.h"

bool EnemyBase::Start()
{
	//ゲームを探す
	m_game = FindGO<Game>("game");
	//プレイヤーを探す
	m_player = FindGO<Player>("player");
	//ゲーム全般の設定


	return true;
}

void EnemyBase::Update()
{

}

void EnemyBase::BaseAction()
{
	////追跡処理
	//Chase();
	////本殿追跡処理
	///*Goal();*/
	////回転処理
	//Rotation();
	////当たり判定
	//Collision();
	////攻撃処理
	//Attack();
	////遠距離攻撃処理
	//MakePoison();
	////ステートの遷移処理
	//ManageState();
	////アニメーションの再生
	//PlayAnimation();

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();
}


void EnemyBase::Chase()
{

}

//void EnemyBase::Collision()
//{
//
//}

//
//void EnemyBase::MakePoison()
//{
//
//}

//void EnemyBase::ProcessCommonStateTransition()
//{
//
//}
//
//void EnemyBase::ProcessIdleStateTransition()
//{
//
//}
//
//void EnemyBase::ProcessRunStateTransition()
//{
//
//}
//
//void EnemyBase::ProcessAttackStateTransition()
//{
//
//}
//
//void EnemyBase::ProcessChaseStateTransition()
//{
//
//}
//
//void EnemyBase::ProcessDamageStateTransition()
//{
//
//}
//
//void EnemyBase::ProcessDownStateTransition()
//{
//
//}
//
//void EnemyBase::ManageState()
//{
//
//}
//
//void EnemyBase::PlayAnimation()
//{
//
//}

//Vector3 EnemyBase::RandPos()
//{
//	Vector3 m_position;
//
//	m_position.x = rand() % 800 - 400;
//	m_position.y = 0.0f;
//	m_position.z = rand() % 500;
//
//	return m_position;
//}

void EnemyBase::Render(RenderContext& rc)
{

}


