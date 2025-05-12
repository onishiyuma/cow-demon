#include "stdafx.h"
#include "UItukuyomi.h"
#include "Game.h"
#include "Player.h"

namespace 
{
	//ツクヨミ
	Vector3 RUNA_FREME_POSITION = Vector3(815.0f, -425.0f, 0.0f);
}

UItukuyomi::UItukuyomi()
{

}

UItukuyomi::~UItukuyomi()
{

}

bool UItukuyomi::Start()
{
	m_player = FindGO<Player>("player");
	//ツクヨミゲージ0
	m_runaSprite.Init("Assets/UI/Tukuyomi 1.DDS", 230, 230);
	m_runaSprite.SetPosition(RUNA_FREME_POSITION);
	m_runaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

	//ツクヨミMAX
	m_runaSprite2.Init("Assets/UI/TukuyomiMax 1.DDS", 230, 230);
	m_runaSprite2.SetPosition(RUNA_FREME_POSITION);
	m_runaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f));

	return true;
}

void UItukuyomi::Update()
{
	m_fadeTime = m_player->m_tukuyomiBlessingCoolDown;
	m_runaMax = m_player->m_tukuyomiMax;

	Vector3 scal = { 1.0f,1.0f,1.0f };

	m_runaSprite2.SetScale(scal);



	m_runaSprite.Update();
	m_runaSprite2.Update();
}

void UItukuyomi::Render(RenderContext& rc)
{
	if (m_fadeTime >=m_runaMax)
	{
		m_runaSprite.Draw(rc);
	}
	else
	{
		m_runaSprite2.Draw(rc);
	}
}