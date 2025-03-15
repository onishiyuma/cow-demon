#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround() 
{
	//モデルの表示
	m_modelRender.Init("Assets/modelData/stage/stage.tkm");
	//モデルの更新
	m_modelRender.Update();
	//当たり判定
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround() 
{

}

void BackGround::Render(RenderContext& rc) 
{
	m_modelRender.Draw(rc);
}
