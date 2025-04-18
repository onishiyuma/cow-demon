#include "stdafx.h"
#include "Amulet.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "GameCamera.h"


bool Amulet::Start()
{
	//インスタンスアドレスを検索。
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_player = FindGO<Player>("player");

	//エフェクトをロードする。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/hit.efk");

	//カメラ行列を前方向に代入。
	Matrix cameraMatrix = g_camera3D->GetCameraRotation();
	m_direction = Vector3(cameraMatrix.m[2][0], cameraMatrix.m[2][1], cameraMatrix.m[2][2]);
	m_direction.Normalize();

	//移動速度を計算。
	m_moveSpeed = m_direction * m_amuletSpeed;

	//コリジョンを作成。
	CreateCollision();

	//エフェクトを作成。
	CreateEffect();

	return true;
}

Amulet::Amulet()
{

}

Amulet::~Amulet()
{
	DeleteGO(m_collisionObj);
	DeleteGO(m_effectEmitter);
}

void Amulet::Update()	
{
	//座標を移動させる。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime() * 4.0f;

	if (m_effectEmitter->GetEffect() != nullptr)
	{
		//エフェクトに座標を設定。
		m_effectEmitter->SetPosition(m_position);
	}
	//コリジョンオブジェクトに座標を設定する。
	m_collisionObj->SetPosition(m_position);

	//タイマーを加算。
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	//タイマーが一定の秒数経過していたら。
	if (m_deleteTimer >= 0.38f)
	{
		//自身を削除。
		DeleteGO(this);
		//エフェクトの再生を停止。
		m_effectEmitter->Stop();
	}
}

void Amulet::CreateCollision()
{
	//カメラの現在位置を取得。（視点位置）
	Vector3 cameraPosition = g_camera3D->GetPosition();

	//コリジョンオブジェクトの作成。
	m_collisionObj = NewGO<CollisionObject>(0);

	//箱状のコリジョンを作成。
	m_collisionObj->CreateBox(m_position, Quaternion::Identity, { 100.0f,100.0f,100.0f });

	//コリジョンの名前。
	m_collisionObj->SetName("purification");

	//オブジェクトが勝手に削除されないように。
	m_collisionObj->SetIsEnableAutoDelete(false);
}

void Amulet::CreateEffect()
{
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//エフェクトの大きさを設定する。
	m_effectEmitter->SetScale({ 55.0f,55.0f,55.0f });
	//エフェクトの座標をセットする。
	m_effectEmitter->SetPosition(m_position);
	m_effectEmitter->Play();
}
