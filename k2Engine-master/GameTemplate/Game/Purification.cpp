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

	//エフェクトをロードする。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/black.efkefc");

	CreateCollision();
	CreateEffect();

	//カメラの前方向を取得。
	Matrix cameraMatrix = g_camera3D->GetCameraRotation();
	m_direction = Vector3(cameraMatrix.m[2][0], cameraMatrix.m[2][1], cameraMatrix.m[2][2]);
	m_direction.Normalize();

	//移動速度を計算。
	m_moveSpeed = m_direction * m_purificationSpeed;

	return true;
}

Purification::Purification()
{

}

Purification::~Purification()
{
	DeleteGO(m_collisionObj);
	DeleteGO(m_effectEmitter);
}

void Purification::Update()
{
	//座標を移動させる。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime() * 4.0f;
	if (m_effectEmitter->GetEffect() != nullptr)
	{
		m_effectEmitter->SetPosition(m_position);
	}

	m_collisionObj->SetPosition(m_position);

	//タイマーを加算する。
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	//タイマーが一定の秒数経過していたら。
	if (m_deleteTimer >= 0.48f)
	{
		//自身を削除。
		DeleteGO(this);
		//エフェクトを停止する。
		m_effectEmitter->Stop();
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
	m_collisionObj->CreateBox(m_position, Quaternion::Identity, { 100.0f,100.0f,100.0f});

	//コリジョンの名前。
	m_collisionObj->SetName("purification");

	//オブジェクトが勝手に削除されないように。
	m_collisionObj->SetIsEnableAutoDelete(false);
}

void Purification::CreateEffect()
{
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(0);
	m_effectEmitter->SetScale({ 55.0f,55.0f,55.0f });
	//エフェクトの座標をセットする。
	m_effectEmitter->SetPosition(m_position);
	m_effectEmitter->Play();
}
