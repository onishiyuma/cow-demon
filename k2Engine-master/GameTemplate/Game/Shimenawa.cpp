#include "stdafx.h"
#include "Shimenawa.h"

bool Shimenawa::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");

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
	//アクティブか。
	if (!m_isActive)
	{
		return;
	}
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();

	//削除条件。
	if (m_elapsedTime >=7)
	{
		Destroy();
	}
}

//しめ縄の削除処理
void Shimenawa::Destroy()
{
	m_isActive = false;
	currentShimenawa = nullptr;
}

Shimenawa::Shimenawa(Vector3 pos, float dur)
{
	m_position = pos;
	m_duration = dur;
	m_elapsedTime = 0.0f;
	m_isActive = true;
}


void Shimenawa::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}