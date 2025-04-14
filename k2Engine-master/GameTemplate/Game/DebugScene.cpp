#include "stdafx.h"
#include "DebugScene.h"

bool DebugScene::Start()
{
	m_modelRender.Init("Assets/modelData/stone/stone.tkm");
	// m_modelRender.SetScale(1.0f, 1.0f, 1.0f);
	return true;

}
void DebugScene::Update()
{
	m_modelRender.Update();
}
void DebugScene::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);

}
