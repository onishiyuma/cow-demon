#include "stdafx.h"
#include "TimingBarA.h"

TimingBarA::TimingBarA()
{

}

TimingBarA::~TimingBarA()
{

}

bool TimingBarA::Start()
{
	m_spriteRender.Init("Assets/sprite/patternA.DDS", 1000.0f, 800.0f); //‰æ‘œ‚ğ“Ç‚İ‚Ş
	m_spriteRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f)); //À•W‚Ìİ’è
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); //‘å‚«‚³‚Ìİ’è
	m_spriteRender.Update();

	return true;
}

void TimingBarA::Update()
{
	m_spriteRender.SetPosition(m_position);
}

void TimingBarA::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}