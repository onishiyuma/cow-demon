#include "stdafx.h"
#include "UIheal.h"
#include "Game.h"
#include "Player.h"

namespace
{
	//‰ñ•œ‰ñ”1
	Vector3 SOUL_POSITION = Vector3(-600.0f, -450.0f, 0.0f);
	//‰ñ•œ‰ñ”2
	Vector3 SOUL_POSITION2 = Vector3(-725.0f, -450.0f, 0.0f);
	//‰ñ•œ‰ñ”3
	Vector3 SOUL_POSITION3 = Vector3(-850.0f, -450.0f, 0.0f);
}


UIheal::UIheal()
{
	
}

UIheal::~UIheal()
{

}

bool UIheal::Start()
{
m_player = FindGO<Player>("player");
	//‰ñ•œ‰ñ”1
	m_soulSprite1.Init("Assets/UI/gage.DDS", 150, 150);
	m_soulSprite1.SetPosition(SOUL_POSITION);
	//‰ñ•œ‰ñ”2
	m_soulSprite2.Init("Assets/UI/gage.DDS", 150, 150);
	m_soulSprite2.SetPosition(SOUL_POSITION2);
	//‰ñ•œ‰ñ”3
	m_soulSprite3.Init("Assets/UI/gage.DDS", 150, 150);
	m_soulSprite3.SetPosition(SOUL_POSITION3);

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
		m_deleteFlag = true;
		DeleteGO(this);
	}
}