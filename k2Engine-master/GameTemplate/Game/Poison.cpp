#include "stdafx.h"
#include "Poison.h"
#include "LittleEnemy.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "graphics/effect/EffectEmitter.h"


Poison::Poison()
{

}

Poison::~Poison()
{
	DeleteGO(m_effectEmitter);
	DeleteGO(m_collisionObj);
}

bool Poison::Start()
{
	//各種インスタンスアドレスを検索。
	m_littleenemy = FindGO<LittleEnemy>("littleEnemy");
	m_player = FindGO<Player>("player");

	//エフェクトを設定。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/Effect/Poison.efk");
	//移動速度を設定する。
	m_moveSpeed = Vector3::AxisZ;
	m_rotation.Apply(m_moveSpeed);
	m_position += m_moveSpeed * 50.0f;
	m_moveSpeed *= 1200.0f;
	//回転を設定する
	m_rotation.AddRotationDegY(360.0f);


	//コリジョンオブジェクトを生成する。
	m_collisionObj = NewGO<CollisionObject>(0);
	//球状のコリジョンを作成する。
	m_collisionObj->CreateSphere(m_position, Quaternion::Identity, 10.0f * m_scale.z);
	if (m_enEnemy == enPoison_LittleEnemy)
	{
		//名前をLittleEnemy_Poisonにする。
		m_collisionObj->SetName("LittleEnemy_Poison");
	}

	//コリジョンオブジェクトが自動で削除されないようにする。
	m_collisionObj->SetIsEnableAutoDelete(false);

	return true;
}
void Poison::CreatEffect()
{
	//エフェクトのインスタンスを生成する。
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//エフェクトの大きさ。
	Vector3 scale(1.0f, 1.0f, 1.0f);
	m_effectEmitter->SetScale(scale);
	//エフェクトの座標をセットする。
	m_effectEmitter->SetPosition(m_position);
	m_effectEmitter->Play();
}

void Poison::Update()
{
	//座標を移動させる。
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime();

	//コリジョンオブジェクトに座標を設定する。
	m_collisionObj->SetPosition(m_position);
	m_collisionObj->SetRotation(m_rotation);

	//タイマーを加算。
	m_timer += g_gameTime->GetFrameDeltaTime();
	//タイマーが0.7f以上だったら
	if (m_timer >= 2.0f)
	{
		DeleteGO(this);
	}
}