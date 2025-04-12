#include "stdafx.h"
#include "UItukuyomi.h"
#include "Game.h"
#include "Player.h"

namespace 
{
	//ツクヨミ
	Vector3 RUNA_FREME_POSITION = Vector3(815.0f, -425.0f, 0.0f);
	//透明
	Vector4 TOUMEI = Vector4(1.0f, 1.0f, 1.0f, 0.0f);
	//80%透明
	Vector4 TOUMEI_80 = Vector4(1.0f, 1.0f, 1.0f, 0.8f);
	//40%透明
	Vector4 TOUMEI_40 = Vector4(1.0f, 1.0f, 1.0f, 0.4f);
	//20％透明
	Vector4 TOUMEI_20 = Vector4(1.0f, 1.0f, 1.0f, 0.2f);
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
	m_RunaSprite.Init("Assets/UI/Tukuyomi 1.DDS", 230, 230);
	//ツクヨミMAX
	m_RunaSprite2.Init("Assets/UI/TukuyomiMax 1.DDS", 230, 230);

	return true;
}

void UItukuyomi::Update()
{
	m_RunaTimer += g_gameTime->GetFrameDeltaTime();
	 float wari = (float)m_RunaTimer;
	 Vector3 scal = { 1.0f,1.0f,1.0f };
	 scal.x,scal.y += wari;


	if (m_RunaTimer >= 40) {
		m_RunaSprite2.SetPosition(RUNA_FREME_POSITION);
		m_RunaSprite2.Update();
	}

	if (m_RunaTimer >= 30, m_RunaTimer < 39)
	{
		m_RunaSprite2.SetPosition(RUNA_FREME_POSITION);
		m_RunaSprite2.SetMulColor(TOUMEI_80);
		m_RunaSprite2.Update();
	}

	if (m_RunaTimer >= 20, m_RunaTimer < 29)
	{
		m_RunaSprite2.SetPosition(RUNA_FREME_POSITION);
		m_RunaSprite2.SetMulColor(TOUMEI_40);
		m_RunaSprite2.Update();
	}

	if (m_RunaTimer >= 10, m_RunaTimer < 19)
	{
		m_RunaSprite2.SetPosition(RUNA_FREME_POSITION);
		m_RunaSprite2.SetMulColor(TOUMEI_20);
		m_RunaSprite2.Update();
	}

	if (m_RunaTimer <= 9)
	{
		m_RunaSprite.SetPosition(RUNA_FREME_POSITION);
		m_RunaSprite.Update();
	}


}

void UItukuyomi::Render(RenderContext& rc)
{
	if (m_RunaTimer >= 10) {
		m_RunaSprite2.Draw(rc);
	}

	else {
		
		m_RunaSprite.Draw(rc);
	}
}