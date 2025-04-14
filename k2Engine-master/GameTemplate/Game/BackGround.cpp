#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
}
bool BackGround::Start()
{
	m_modelRender.Init("Assets/modelData/stage/StageNotree.tkm");

	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	return true;
}

BackGround::~BackGround() 
{

}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}