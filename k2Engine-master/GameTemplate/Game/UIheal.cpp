#include "stdafx.h"
#include "UIheal.h"
#include "Game.h"
#include "Player.h"

namespace
{
	//‰ñ•œ‰ñ”1
	Vector3 SOUL_POSITION = Vector3(-850.0f, -450.0f, 0.0f);
	//‰ñ•œ‰ñ”2
	Vector3 SOUL_POSITION2 = Vector3(-725.0f, -450.0f, 0.0f);
	//‰ñ•œ‰ñ”2
	Vector3 SOUL_POSITION3 = Vector3(-600.0f, -450.0f, 0.0f);
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
	m_SoulSprite1.Init("Assets/UI/gage.DDS", 150, 150);
	m_SoulSprite1.SetPosition(SOUL_POSITION);
	//‰ñ•œ‰ñ”2
	m_SoulSprite2.Init("Assets/UI/gage.DDS", 150, 150);
	m_SoulSprite2.SetPosition(SOUL_POSITION2);
	//‰ñ•œ‰ñ”3
	m_SoulSprite3.Init("Assets/UI/gage.DDS", 150, 150);
	m_SoulSprite3.SetPosition(SOUL_POSITION3);

	return true;
}

void UIheal::Update()
{
	m_SoulSprite3.Update();
	m_SoulSprite2.Update();
	m_SoulSprite1.Update();


}

void UIheal::Render(RenderContext& rc)
{
	m_SoulSprite1.Draw(rc);
	m_SoulSprite2.Draw(rc);
	m_SoulSprite3.Draw(rc);
}