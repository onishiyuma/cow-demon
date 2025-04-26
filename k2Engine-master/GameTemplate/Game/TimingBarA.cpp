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
	m_spriteRender.Init("Assets/sprite/patternA.DDS", 1000.0f, 800.0f); //画像を読み込む
	m_spriteRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f)); //座標の設定
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); //大きさの設定
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