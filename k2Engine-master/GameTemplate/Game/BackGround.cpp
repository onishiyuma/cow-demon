#include "stdafx.h"
#include "BackGround.h"
#include "collision/CollisionObject.h"

bool BackGround::Start()
{
	//モデルの初期化を行う。
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");

	//モデルのワールド行列を更新する。
	m_modelRender.Update();
	//静的物理オブジェクトの作成。
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//当たり判定を有効化する。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

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
	//コリジョンオブジェクトを削除する。
	DeleteGO(m_collisionObject);
}

void BackGround::Update()
{

}

//コリジョンを作成。
void BackGround::CreateCollision()
{
	//コリジョンオブジェクトのインスタンスを作成。
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