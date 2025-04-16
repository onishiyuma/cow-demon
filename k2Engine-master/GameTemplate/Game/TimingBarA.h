#pragma once
class TimingBarA:public IGameObject
{
public:
	TimingBarA();
	~TimingBarA();

	bool Start();

	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	Vector3 m_position;

};

