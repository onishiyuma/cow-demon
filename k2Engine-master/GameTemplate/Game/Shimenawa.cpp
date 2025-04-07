#include "stdafx.h"
#include "Shimenawa.h"
#include "Player.h"

bool Shimenawa::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");

	//プレイヤーのインスタンスを検索する。
	m_player = FindGO<Player>("player");

	return true;
}

Shimenawa::Shimenawa()
{

}

Shimenawa::~Shimenawa()
{

}

void Shimenawa::Update()
{
	m_timer = g_gameTime->GetFrameDeltaTime();

	//取得処理。
	if (!m_isCollected)
	{
		m_collectTimer += m_timer;
		if (m_collectTimer >= m_collectTime)
		{
			m_isCollected = true;
		}
	}

	//設置後の時間管理。
	if (m_isPlaced)
	{
		m_elapsedTime += m_timer;
		if (m_elapsedTime >= m_placeDuration)
		{
			Destroy();
		}
	}
}

void Shimenawa::Place(Vector3 playerPosition)
{
	if (m_isCollected && !m_isPlaced)
	{
		m_isPlaced = true;
		m_isCollected = false;
		m_position = m_player->m_position;
		m_elapsedTime = 0.0f;//取得時間をリセット。
	}
}

//しめ縄の削除処理
void Shimenawa::Destroy()
{
	m_isPlaced = false;
	m_elapsedTime = 0.0f;

}

void Shimenawa::Render(RenderContext& rc)
{
	if (!m_isPlaced)return;
	{
		m_modelRender.Draw(rc);
	}
}


