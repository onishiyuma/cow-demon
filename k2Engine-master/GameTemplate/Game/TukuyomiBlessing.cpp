#include "stdafx.h"
#include "TukuyomiBlessing.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "Enemy.h"

#include "sound/SoundEngine.h"
#include "sound/soundSource.h"


bool TukuyomiBlessing::Start()
{
	//エフェクトをロードする。
	EffectEngine::GetInstance()->ResistEffect(12,u"Assets/effect/PlayerEffects/TUkuyomi/Tukuyomi.efkefc");
	//音を読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/tukuyomichan.wav");
	//インスタンスアドレスを検索する。
	m_player = FindGO<Player>("player");
	//プレイヤーの座標を取得する。
	m_position = m_player->GetPosition();

	//音を再生。
	SoundSource* se = NewGO<SoundSource>(0);
	se->Init(0);
	se->Play(false);
	se->SetVolume(0.7);

	//エフェクトの作成。
	CreateEffect();
	//コリジョンの作成。
	CreateCollision();

	return true;
}

TukuyomiBlessing::TukuyomiBlessing()
{

}

TukuyomiBlessing::~TukuyomiBlessing()
{

}

void TukuyomiBlessing::Update()
{
	//追従処理。
	Move();
	//エフェクトを削除。
	DeleteTime();
}

//継続時間。
void TukuyomiBlessing::DeleteTime()
{
	//エフェクトを再生。
	m_effectEmitter->Play();
	//エフェクトの削除時間を設定。
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	if (m_deleteTimer >= m_duration)
	{ 
		m_effectEmitter->Stop();
		DeleteGO(this);
	}
}

//追従処理。
void TukuyomiBlessing::Move()
{
	//プレイヤーの座標を取得する。
	Vector3 centerPosition = m_player->GetPosition();
	//コリジョンの座標を設定。
	m_collisionObject->SetPosition(centerPosition);
	//エフェクトの座標を設定。
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
	//エフェクトのインスタンスを作成。
	m_effectEmitter=NewGO<EffectEmitter>(0);
	//エフェクトを初期化。
	m_effectEmitter->Init(12);
	//大きさを設定。
	m_effectEmitter->SetScale({ 95.0f,10.0f,95.0f });
	//エフェクトの座標をセットする。
	m_effectEmitter->SetPosition(m_position);
	//エフェクトを再生。
	//m_effectEmitter->Play();
}


void TukuyomiBlessing::Render(RenderContext& rc)
{

}