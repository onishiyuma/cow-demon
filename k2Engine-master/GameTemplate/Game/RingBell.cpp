#include "stdafx.h"
#include "RingBell.h"
#include "collision/CollisionObject.h"

bool RingBell::Start()
{
	m_modelRender.Init("Assets/modelData/offeringBox/offeringBox.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetScale(0.7f, 0.7f, 0.7f);

	//コリジョン作成用関数を呼び出す。
	CreateCollision();

	m_collisionObject->SetPosition(m_position);
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
	m_modelRender.Update();


}

//コリジョンを作成。
void RingBell::CreateCollision()
{
	m_collisionObject= NewGO<CollisionObject>(0);

	//箱状のコリジョンを作成する。
	m_collisionObject->CreateBox(m_position, Quaternion::Identity, {m_collisionScale});

	//コリジョンに名前をつける。
	m_collisionObject->SetName("ringbell");
	//オブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);
}

void RingBell::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
