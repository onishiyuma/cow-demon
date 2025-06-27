#include "stdafx.h"
#include "Operation.h"
#include "GameManagement.h"
#include "Title.h"

Operation::Operation()
{

}

Operation::~Operation()
{

}

bool Operation::Start()
{
	m_gameManagement = FindGO<GameManagement>("gameManagement");

	m_operationController.Init("Assets/sprite/S.DDS", 1920.0f, 1080.0f);
	m_operationController.SetPosition({ 0.0f,0.0f,0.0f });

	m_operationPlayer.Init("Assets/sprite/sousa.DDS", 1920.0f, 1080.0f);
	m_operationPlayer.SetPosition({ 0.0f,0.0f,0.0f });

	return true;
}

void Operation::Update()
{
	m_operationController.Update();
	m_operationController.SetPosition({ 0.0f,0.0f,0.0f });
	m_operationPlayer.Update();
	m_operationPlayer.SetPosition({ 0.0f,0.0f,0.0f });

	//Aボタンが押されたら
	if(m_count == 0 && g_pad[0]->IsTrigger(enButtonA))
	{
		m_count = 1;
	}
	else if (m_count == 1) {
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_count++;

			DeleteGO(m_gameManagement);
			m_gameManagement = NewGO<GameManagement>(0, "gameManagement");
			m_title = NewGO<Title>(0, "title");
			DeleteGO(this);
		}
	}
	

}

void Operation::Render(RenderContext& rc)
{
	if(m_count == 0)
	{
		m_operationController.Draw(rc);
	}
	else if(m_count == 1)
	{
		m_operationPlayer.Draw(rc);
	}
	
}