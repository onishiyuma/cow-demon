#include "stdafx.h"
#include "Purification.h"
#include "Player.h"
#include "GameCamera.h"
#include "collision/CollisionObject.h"


bool Purification::Start()
{
	//インスタンスアドレスを検索。
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_player = FindGO<Player>("player");

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
	//カメラの前方向を取得。
	Matrix cameraMatrix = g_camera3D->GetCameraRotation();
	m_direction = Vector3(cameraMatrix.m[2][0], cameraMatrix.m[2][1], cameraMatrix.m[2][2]);
	m_direction.Normalize();

	//キャラクターの回転を考慮する。
	Quaternion rotation = m_player->GetRotation();
	Vector3 foward = Vector3(0, 0, 1);//z方向
	//m_player->GetRotation().Apply(foward);
	rotation.Apply(foward);
	foward.Normalize();

	//////移動速度を計算。//////
	m_moveSpeed = m_direction;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed;
	m_moveSpeed *= m_purificationSpeed;


	//座標を移動させる。
	m_position+= m_moveSpeed * g_gameTime->GetFrameDeltaTime() * 4.0f;

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

//コリジョンオブジェクトの作成。
void Purification::CreateCollision()
{
	//カメラの現在位置を取得。（視点位置）
	Vector3 cameraPosition = g_camera3D->GetPosition();

	//コリジョンオブジェクトの作成。
	m_collisionObj = NewGO<CollisionObject>(0);

	//箱状のコリジョンを作成。
	m_collisionObj->CreateBox(m_position, Quaternion::Identity, { 65.0f,65.0f,65.0f});

	//コリジョンの名前。
	m_collisionObj->SetName("purification");

	//オブジェクトが勝手に削除されないように。
	m_collisionObj->SetIsEnableAutoDelete(false);
}

//モデルレンダー。
void Purification::Render(RenderContext& rc)
{

}