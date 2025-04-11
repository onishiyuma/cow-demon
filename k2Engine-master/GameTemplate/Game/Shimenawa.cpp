#include "stdafx.h"
#include "Shimenawa.h"
#include "Player.h"

bool Shimenawa::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	//m_position.Set(0.0f, 50.0f, 0.0f);

	//プレイヤーのインスタンスを検索する。
	m_player = FindGO<Player>("player");

	return true;
}

Shimenawa::Shimenawa()
{

}

Shimenawa::~Shimenawa()
{
	DeleteGO(this);
}

void Shimenawa::Update()
{
		m_elapsedTime += g_gameTime->GetFrameDeltaTime();

		if (m_elapsedTime >= m_placeDuration)
		{
			Destroy();
		}
}

void Shimenawa::Place(Vector3 playerPosition)
{
	m_position = playerPosition;
	//m_position = m_player->GetPosition();
	m_elapsedTime = 0.0f;
}

//しめ縄の削除処理
void Shimenawa::Destroy()
{
	if (m_player)
	{
		m_player->ResetShimenawa();
	}

	m_isPlaced = false;
	m_elapsedTime = 0.0f;

	DeleteGO(this);

}

void Shimenawa::Render(RenderContext& rc)
{
	m_position=m_player->GetPosition();
	m_modelRender.SetPosition(m_position);
	m_modelRender.Draw(rc);
}