#include "stdafx.h"
#include "Shimenawa.h"
#include "Player.h"
#include "collision/collisionObject.h"

namespace
{
	//箱状コリジョンの大きさを設定。
	Vector3 BOX_SIZE = { 700.0f, 1.0f, 700.0f }; 
}

bool Shimenawa::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/rope/rope.tkm");

	//プレイヤーのインスタンスを検索する。
	m_player = FindGO<Player>("player");

	//座標を取得。
	m_position = m_player->GetPosition();

	//コリジョンを作成。
	CreateCollision();

	//設置。
	Put();

	return true;
}

Shimenawa::Shimenawa()
{

}

Shimenawa::~Shimenawa()
{
	DeleteGO(m_collisionObject);
}

void Shimenawa::Update()
{
	//継続時間。
	DurationTime();
}

//設置する関数
void Shimenawa::Put()
{
	m_collisionObject->SetPosition(m_position);
	m_collisionObject->Update();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
}

//コリジョンを作成。
void Shimenawa::CreateCollision()
{
	m_collisionObject = NewGO<CollisionObject>(0);
	//箱状のコリジョンを作成。
	m_collisionObject->CreateBox(m_position, Quaternion::Identity, BOX_SIZE);
	//名前を付ける。
	m_collisionObject->SetName("Shimenawa");;
	//オブジェクトが削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);
}

void Shimenawa::DurationTime()
{
	//継続時間が切れたら削除する。
	m_durationTimer+= g_gameTime->GetFrameDeltaTime();
	if (m_durationTimer >= m_duration)
	{
		DeleteGO(this);
	}
}

void Shimenawa::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}