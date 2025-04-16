#include "stdafx.h"
#include "BackGround.h"
#include "collision/CollisionObject.h"

bool BackGround::Start()
{
	m_modelRender.Init("Assets/modelData/stage/StageNotree.tkm");

	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	
	//コリジョン作成用関数を呼び出す。
	CreateCollision();
	//コリジョンに座標をセット。
	m_collisionObject->SetPosition(m_position);
	m_collisionObject->Update();

	return true;
}

BackGround::BackGround()
{

}

BackGround::~BackGround() 
{
	DeleteGO(m_collisionObject);
}

void BackGround::Update()
{

}

//コリジョンを作成。
void BackGround::CreateCollision()
{
	m_collisionObject = NewGO<CollisionObject>(0);

	//箱状のコリジョンを作成。
	m_collisionObject->CreateBox(m_position, Quaternion::Identity, { m_collisionScale });

	//コリジョンに名前をつける。
	m_collisionObject->SetName("gameover_collision");

	//オブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}