#pragma once
class TimingBarB :public IGameObject
{
public:
	TimingBarB();
	~TimingBarB();

	bool Start();

	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	Vector3 m_position;

};

