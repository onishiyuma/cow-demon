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
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/stage/Tree.tkm");
	m_modelRender.SetPosition(m_position);
	return true;
}

void Tree::Update()
{

}

void Tree::Render(RenderContext&rc)
{
	m_modelRender.Draw(rc);
}