#include "stdafx.h"
#include "Operation.h"
#include "Title.h"

Operation::Operation()
{

}

Operation::~Operation()
{

}

bool Operation::Start()
{
	//画像を読み込む。
	m_operationController.Init("Assets/sprite/S.DDS", 1920.0f, 1080.0f);
	m_operationController.SetPosition(m_position);
	//画像を読み込む。
	m_operationPlayer.Init("Assets/sprite/sousa.DDS", 1920.0f, 1080.0f);
	m_operationPlayer.SetPosition(m_position);

	return true;
}

void Operation::Update()
{
	//更新処理。
	m_operationController.Update();
	m_operationPlayer.Update();

	//Aボタンが押されたら。
	if(m_count == 0 && g_pad[0]->IsTrigger(enButtonA))
	{
		m_count = 1;
	}
	else if (m_count == 1) {
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_count++;
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