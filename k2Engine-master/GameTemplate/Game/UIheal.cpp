#include "stdafx.h"
#include "UIheal.h"
#include "Game.h"
#include "Player.h"

namespace
{
	//回復回数1。
	Vector3 SOUL_POSITION1(-600.0f, -450.0f, 0.0f);
	//回復回数2。
	Vector3 SOUL_POSITION2(-725.0f, -450.0f, 0.0f);
	//回復回数3。
	Vector3 SOUL_POSITION3(-850.0f, -450.0f, 0.0f);
}


UIheal::UIheal()
{
	
}

UIheal::~UIheal()
{

}

bool UIheal::Start()
{
	//インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");

	//回復回数1
	m_soulSprite1.Init("Assets/UI/gage.DDS", 150, 150);
	m_soulSprite1.SetPosition(SOUL_POSITION1);
	//回復回数2
	m_soulSprite2.Init("Assets/UI/gage.DDS", 150, 150);
	m_soulSprite2.SetPosition(SOUL_POSITION2);
	//回復回数3
	m_soulSprite3.Init("Assets/UI/gage.DDS", 150, 150);
	m_soulSprite3.SetPosition(SOUL_POSITION3);

	//回復回数を初期化。
	m_useHeal = 3;

	return true;
}

void UIheal::Update()
{
	m_soulSprite1.Update();
	m_soulSprite2.Update();
	m_soulSprite3.Update();
}

void UIheal::Render(RenderContext& rc)
{
	//回復回数を表示。
	if (m_useHeal >= 3)
	{
		m_soulSprite1.Draw(rc);
		m_soulSprite2.Draw(rc);
		m_soulSprite3.Draw(rc);
	}
	if (m_useHeal ==2)
	{
		m_soulSprite2.Draw(rc);
		m_soulSprite3.Draw(rc);
	}
	else if (m_useHeal == 1)
	{
		m_soulSprite3.Draw(rc);
	}
	else if (m_useHeal <= 0)
	{
		m_isDelete = true;
		DeleteGO(this);
	}
}