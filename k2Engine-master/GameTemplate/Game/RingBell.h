#pragma once


class RingBell:public IGameObject
{
public:
	RingBell();
	~RingBell();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//ƒƒ“ƒo•Ï”B
	Vector3 m_position;
};