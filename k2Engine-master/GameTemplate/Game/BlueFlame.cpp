#include "stdafx.h"
#include "BlueFlame.h"
#include "Lantern.h"

namespace
{
	Vector3 EFECT_SCALE = { 30.0f,30.0f,30.0f };
}

bool BlueFlame::Start()
{
	m_lantern = FindGO<Lantern>("lantern1");
	m_lantern = FindGO<Lantern>("lantern2");
	m_lantern = FindGO<Lantern>("lantern3");
	m_lantern = FindGO<Lantern>("lantern4");

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/blueFlame/Tourou_Brue.efk");

	CreateEffect();
	
	//m_effectEmitter->Update();

	return true;
}

BlueFlame::BlueFlame()
{

}

BlueFlame::~BlueFlame()
{
	m_effectEmitter->Stop();
	DeleteGO(m_effectEmitter);
}



void BlueFlame::Update()
{
	m_effectEmitter->SetPosition(m_firstPosition);
	m_effectEmitter->Play();
}

void BlueFlame::CreateEffect()
{
	//エフェクトのインスタンスを生成。
	m_effectEmitter = NewGO<EffectEmitter>(2);
	m_effectEmitter->Init(2);
	//エフェクトの大きさ。
	m_effectEmitter->SetScale(EFECT_SCALE);
	//エフェクトの初期座標。
	m_effectEmitter->SetPosition(m_firstPosition);
	m_effectEmitter->Play();
}

void BlueFlame::Render(RenderContext& rc)
{

}
