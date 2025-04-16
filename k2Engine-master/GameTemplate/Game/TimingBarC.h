#pragma once
class TimingBarC :public IGameObject
{
public:
	TimingBarC();
	~TimingBarC();

	bool Start();

	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	Vector3 m_position;

};

