#include "stdafx.h"
#include "RedFlame.h"
#include "LanternAttack.h"

namespace
{
	Vector3 EFECT_SCALE = { 30.0f,30.0f,30.0f };
}

RedFlame::RedFlame()
{

}

RedFlame::~RedFlame()
{

}

bool RedFlame::Start()
{
	m_lanternAttack = FindGO<LanternAttack>("LanternAttack1");
	m_lanternAttack = FindGO<LanternAttack>("LanternAttack2");
	m_lanternAttack = FindGO<LanternAttack>("LanternAttack3");
	m_lanternAttack = FindGO<LanternAttack>("LanternAttack4");

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/redFlame/Tourou_Red.efk");

	CreateEffect();
	return true;
}

void RedFlame::Update()
{
	m_effectEmitter->SetPosition(m_firstPosition);
	m_effectEmitter->Play();
}

void RedFlame::CreateEffect()
{
	//エフェクトのインスタンスを生成。
	m_effectEmitter = NewGO<EffectEmitter>(3);
	m_effectEmitter->Init(3);
	//エフェクトの大きさ。
	m_effectEmitter->SetScale(EFECT_SCALE);
	//エフェクトの初期座標。
	m_effectEmitter->SetPosition(m_firstPosition);
	m_effectEmitter->Play();
}

void RedFlame::Render(RenderContext& rc)
{

}
