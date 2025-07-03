#include "stdafx.h"
#include "Purification.h"
#include "Player.h"
#include "GameCamera.h"
#include "collision/CollisionObject.h"

namespace
{
	//箱状コリジョンの大きさ。
	const Vector3 BOX_SIZE{ 100.0f, 100.0f, 100.0f };
	//エフェクトの大きさ。
	const Vector3 EFFECT_SCALE{ 55.0f, 55.0f, 55.0f };
}

bool Purification::Start()
{
	//インスタンスアドレスを検索。
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_player = FindGO<Player>("player");

	//エフェクトをロードする。
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/PlayerEffects/NormalAttack/NormalAttack.efk");

	//カメラの前方向を取得。
	Matrix cameraMatrix = g_camera3D->GetCameraRotation();
	m_direction = Vector3(cameraMatrix.m[2][0], cameraMatrix.m[2][1], cameraMatrix.m[2][2]);
	m_direction.Normalize();

	//移動速度を計算。
	m_moveSpeed = m_direction * m_purificationSpeed;

	//コリジョンの作成。
	CreateCollision();

	//エフェクトの作成。
	CreateEffect();

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
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime() * 4.0f;
	if (m_effectEmitter->GetEffect() != nullptr)
	{
		//エフェクトに座標を設定。
		m_effectEmitter->SetPosition(m_position);
	}
	//コリジョンオブジェクトに座標を設定する。
	m_collisionObj->SetPosition(m_position);

	//タイマーを加算する。
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	//タイマーが一定の秒数経過していたら。
	if (m_deleteTimer >= 0.28f)
	{
		// エフェクトを停止する。
		if (m_effectEmitter != nullptr)
		{
			m_effectEmitter->Stop();
		}

		//自身を削除。
		DeleteGO(this);
	}
}

//コリジョンオブジェクトの作成。
void Purification::CreateCollision()
{
	//カメラの現在位置を取得。
	Vector3 cameraPosition = g_camera3D->GetPosition();
	//コリジョンオブジェクトの作成。
	m_collisionObj = NewGO<CollisionObject>(0);
	//箱状のコリジョンを作成。
	m_collisionObj->CreateBox(m_position, Quaternion::Identity, BOX_SIZE);
	//コリジョンの名前。
	m_collisionObj->SetName("purification");
	//オブジェクトが勝手に削除されないように。
	m_collisionObj->SetIsEnableAutoDelete(false);
}

void Purification::CreateEffect()
{
	//エフェクトのインスタンスを作成。
	m_effectEmitter = NewGO<EffectEmitter>(0);
	//読み込み。
	m_effectEmitter->Init(1);
	//大きさをセットする。
	m_effectEmitter->SetScale(EFFECT_SCALE);
	//m_rotation.SetRotationDegY(90.0f);
	//m_effectEmitter->SetRotation(m_rotation);
	//エフェクトの座標をセットする。
	m_effectEmitter->SetPosition(m_position);
	//エフェクトを再生。
	m_effectEmitter->Play();
}
