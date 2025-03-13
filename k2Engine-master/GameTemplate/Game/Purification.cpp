#include "stdafx.h"
#include "Purification.h"
#include "Player.h"
#include "GameCamera.h"
#include "collision/CollisionObject.h"


bool Purification::Start()
{
	//インスタンスアドレスを検索。
	m_gameCamera = FindGO<GameCamera>("gamecamera");

	//カメラの前方向を取得。
	//m_direction = g_camera3D->GetForward();//カメラの前方向を取得する。

	Vector3 direction=g_camera3D->GetAxisZ


	//////移動速度を計算。//////
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 2000.0f;

	CreateCollision();

	return true;
}

Purification::Purification()
{

}

Purification::~Purification()
{
	DeleteGO(m_collisionObj);
}

void Purification::Update()
{
	//座標を移動させる。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime() * 1.5f;

	//コリジョンオブジェクトに座標を設定。
	m_collisionObj->SetPosition(m_position);

	//タイマーを加算。
	m_timer += g_gameTime->GetFrameDeltaTime();

	//タイマーが一定の秒数経過していたら。
	if (m_timer >= 0.48f)
	{
		//自身を削除。
		DeleteGO(this);
	}
}

//カメラのベクトル。
void Purification::CameraVector()
{

}

//コリジョンオブジェクトの作成。
void Purification::CreateCollision()
{
	//カメラの現在位置を取得。（視点位置）
	Vector3 cameraPosition = g_camera3D->GetPosition();

	//コリジョンオブジェクトの作成。
	m_collisionObj = NewGO<CollisionObject>(0);

	//箱状のコリジョンを作成。
	m_collisionObj->CreateBox(m_position, Quaternion::Identity, { 45.0f,45.0f,45.0f});

	//コリジョンの名前。
	m_collisionObj->SetName("purification");

	//オブジェクトが勝手に削除されないように。
	m_collisionObj->SetIsEnableAutoDelete(false);
}

//モデルレンダー。
void Purification::Render(RenderContext& rc)
{

}