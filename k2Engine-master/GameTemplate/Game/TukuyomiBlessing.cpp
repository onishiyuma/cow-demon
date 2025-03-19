#include "stdafx.h"
#include "TukuyomiBlessing.h"
#include "Player.h"
//#include "Enemy.h"


bool TukuyomiBlessing::Start()
{
	//エフェクトをロードする。
	//EffectEngine::GetInstance()->ResistEffect(0,u"Assets/effect/num");

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


	//CreateEffect();
}

//攻撃できる範囲。
void TukuyomiBlessing::Distanxce()
{
	//for(auto&)
}

//継続時間。
void TukuyomiBlessing::Duration()
{

}

//エフェクトの作成。
void TukuyomiBlessing::CreateEffect()
{
	m_effectEmitter=NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(0);
	m_effectEmitter->SetScale({ 55.0f,1.0f,55.0f });
	//エフェクトの座標をセットする。
	m_effectEmitter->SetPosition(m_position);
	m_effectEmitter->Play();
}


void TukuyomiBlessing::Render(RenderContext& rc)
{

}