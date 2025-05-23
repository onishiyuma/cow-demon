#include "stdafx.h"
#include "Amulet.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "GameCamera.h"


bool Amulet::Start()
{
	//カメラとプレイヤーのインスタンスを取得する。
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_player = FindGO<Player>("player");

	//エフェクトの登録。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/hit.efk");

	//カメラの前方向のベクトルを取得して、移動方向にする。
	Matrix cameraMatrix = g_camera3D->GetCameraRotation();
	m_direction = Vector3(cameraMatrix.m[2][0], cameraMatrix.m[2][1], cameraMatrix.m[2][2]);
	m_direction.Normalize();

	//移動速度の設定。
	m_moveSpeed = m_direction * m_amuletSpeed;

	//コリジョンの作成。
	CreateCollision();

	//エフェクトの作成。
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
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime() * 4.0f;

	if (m_effectEmitter->GetEffect() != nullptr)
	{
		m_effectEmitter->SetPosition(m_position);
	}

	m_collisionObj->SetPosition(m_position);

	//自動削除タイマー。
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	//時間経過で削除する。
	if (m_deleteTimer >= 0.38f)
	{
		DeleteGO(this);
		//エフェクトの停止。
		m_effectEmitter->Stop();
	}
}

void Amulet::CreateCollision()
{
	//カメラ位置の取得。
	Vector3 cameraPosition = g_camera3D->GetPosition();
	//コリジョンオブジェクトの作成。
	m_collisionObj = NewGO<CollisionObject>(0);
	//ボックス上のコリジョンを作成。
	m_collisionObj->CreateBox(m_position, Quaternion::Identity, { 100.0f,100.0f,100.0f });
	//名前をつける。
	m_collisionObj->SetName("purification");
	//自動削除されないようにする。
	m_collisionObj->SetIsEnableAutoDelete(false);
}

void Amulet::CreateEffect()
{
	//エフェクトエミッターのインスタンスを作成。
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//エフェクトのサイズを設定する。
	m_effectEmitter->SetScale({ 55.0f,55.0f,55.0f });
	//初期座標を設定する。
	m_effectEmitter->SetPosition(m_position);
	//エフェクトを再生。
	m_effectEmitter->Play();
}
