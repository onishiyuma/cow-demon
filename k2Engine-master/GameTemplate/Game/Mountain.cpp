#include "stdafx.h"
#include "Mountain.h"

Mountain::Mountain()
{

}

Mountain::~Mountain()
{

}

bool Mountain::Start() 
{
	m_modelRender.Init("Assets/modelData/stage/Mountain.tkm");
	m_position = m_firstPosition;

	return true;
}

void Mountain::Update() 
{
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);
}

void Mountain::Render(RenderContext&rc) 
{
	m_modelRender.Draw(rc);
}