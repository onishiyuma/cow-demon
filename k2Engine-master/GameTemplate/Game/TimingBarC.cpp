#include "stdafx.h"
#include "TimingBarC.h"

TimingBarC::TimingBarC()
{

}

TimingBarC::~TimingBarC()
{

}

bool TimingBarC::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/patternC.DDS", 1000.0f, 800.0f); 
	//座標の設定。
	m_spriteRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f)); 
	//大きさの設定。
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); 
	m_spriteRender.Update();

	return true;
}

void TimingBarC::Update()
{
	m_spriteRender.SetPosition(m_position);
}

void TimingBarC::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}