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
	m_spriteRender.Init("Assets/sprite/patternB.DDS", 1000.0f, 800.0f); //‰æ‘œ‚ğ“Ç‚İ‚Ş
	m_spriteRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f)); //À•W‚Ìİ’è
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); //‘å‚«‚³‚Ìİ’è
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