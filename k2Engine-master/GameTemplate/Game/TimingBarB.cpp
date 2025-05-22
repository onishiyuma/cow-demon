#include "stdafx.h"
#include "TimingBarB.h"

TimingBarB::TimingBarB()
{

}

TimingBarB::~TimingBarB()
{

}

bool TimingBarB::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/patternB.DDS", 1000.0f, 800.0f); 
	//座標の設定。
	m_spriteRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f)); 
	//大きさの設定。
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); 
	m_spriteRender.Update();

	return true;
}

void TimingBarB::Update()
{
	m_spriteRender.SetPosition(m_position);
}

void TimingBarB::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}