#include "stdafx.h"
#include "TukuyomiBlessing.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "Enemy.h"


bool TukuyomiBlessing::Start()
{
	//エフェクトをロードする。
	EffectEngine::GetInstance()->ResistEffect(0,u"Assets/effect/bullet.efkefc");
	m_player = FindGO<Player>("player");

	m_position = m_player->GetPosition();

	CreateEffect();
	CreateCollision();

	return true;
}

TukuyomiBlessing::TukuyomiBlessing()
{

}

TukuyomiBlessing::~TukuyomiBlessing()
{
	DeleteGO(m_effectEmitter);
	DeleteGO(m_collisionObject);
}

void TukuyomiBlessing::Update()
{
	//追従させる。
	Move();
	//エフェクトを削除。
	DeleteTime();
}

//攻撃できる範囲。
void TukuyomiBlessing::Distance()
{
	//for(auto&)
}

//継続時間。
void TukuyomiBlessing::DeleteTime()
{
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();

	if (m_deleteTimer >= m_duration)
	{
		DeleteGO(this);
		m_effectEmitter->Stop();
	}
}

//追従処理。
void TukuyomiBlessing::Move()
{
	Vector3 centerPosition = m_player->GetPosition();
	m_collisionObject->SetPosition(centerPosition);
	m_effectEmitter->SetPosition(centerPosition);
}

//コリジョンの作成。
void TukuyomiBlessing::CreateCollision()
{
	//コリジョンを作成
	m_collisionObject = NewGO <CollisionObject>(0);
	//球状のコリジョンを作成する。
	m_collisionObject->CreateBox(m_position, Quaternion::Identity, { 500.0f,1.0f,500.0f });
	//名前を付ける。
	m_collisionObject->SetName("Tukuyomi");
	//オブジェクトが自動で削除されないようにする。
	m_collisionObject->SetIsEnableAutoDelete(false);
}

//エフェクトの作成。
void TukuyomiBlessing::CreateEffect()
{
	m_effectEmitter=NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//大きさを設定。
	m_effectEmitter->SetScale({ 500.0f,2.0f,500.0f });
	//エフェクトの座標をセットする。
	m_effectEmitter->SetPosition(m_position);
	//エフェクトを再生。
	m_effectEmitter->Play();
}


void TukuyomiBlessing::Render(RenderContext& rc)
{

}