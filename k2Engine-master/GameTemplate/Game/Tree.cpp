#include "stdafx.h"
#include "Tree.h"

Tree::Tree()
{

}

Tree::~Tree()
{

}

bool Tree::Start()
{
	m_modelRender.Init("Assets/modelData/stage/Tree.tkm");

	m_position = m_firstPosition;

	return true;
}

void Tree::Update()
{
	m_modelRender.Update();
	m_modelRender.SetPosition(m_position);
}

void Tree::Render(RenderContext&rc)
{
	m_modelRender.Draw(rc);
}