#include "stdafx.h"
#include "Stone.h"
#include "Player.h"
#include "SpriteCollection.h"
#include "sound/SoundEngine.h"



bool Stone::Start() 
{

	m_player = FindGO<Player>("player");

	m_spriteCollection = FindGO<SpriteCollection>("spriteCollection");

	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/stone/stone.test.tkm");
	m_modelRender.SetScale(0.5f, 0.5f, 0.5f);
	
	//m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//コリジョン作成用関数を呼び出す。
	//CreateCollision();
	//コリジョンに座標をセット。
	//m_collisionObject->SetPosition(m_position);
	//m_collisionObject->Update();
	

	return true;
}

Stone::Stone() 
{

}

Stone::~Stone() 
{
	DeleteGO(m_spriteCollection);
	//DeleteGO(m_collisionObject);
	//DeleteGO(this);
}

void Stone::Update() 
{

	//m_modelRender.SetPosition(m_player->GetPosition());
	m_modelRender.Update();

	Move();
	
	//プレイヤーから火打石に向かうベクトルを計算。
	Vector3 diff = m_player->m_position - m_position;
	//ベクトルの長さが120.0fより小さかったら
	if (diff.Length() <= 50.0f) {

		if (m_collectionFlag ==false) {

			m_spriteCollection = NewGO<SpriteCollection>(0, "spriteCollection");

			m_collectionFlag = true;

			
			
		}
		//Aボタンを押したら
		if (g_pad[0]->IsTrigger(enButtonA)) {

			//火打石のアイテムカウントを1増やす。
			m_player->m_stoneCount += 1;

			//自身を削除する。
			DeleteGO(this);
			
		}
		
	}
	else {

		m_collectionFlag = false;

		DeleteGO(m_spriteCollection);
	}
	
	
}

void Stone::Move() 
{
	m_modelRender.SetPosition(m_position);
}

////コリジョンを作成。
//void Stone::CreateCollision()
//{
//	m_collisionObject = NewGO<CollisionObject>(0);
//
//	//箱状のコリジョンを作成。
//	m_collisionObject->CreateBox(m_position, Quaternion::Identity, { m_collisionScale });
//
//	//コリジョンに名前をつける。
//	m_collisionObject->SetName("gameover_collision");
//
//	//オブジェクトが自動で削除されないようにする。
//	m_collisionObject->SetIsEnableAutoDelete(false);
//}


void Stone::Render(RenderContext& rc) 
{
	m_modelRender.Draw(rc);
}