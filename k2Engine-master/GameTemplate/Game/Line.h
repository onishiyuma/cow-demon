#pragma once

class Lantern;

class Line :public IGameObject
{
public:
	Line();
	~Line();

	bool Start();
	void Move();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	Vector3 m_firstPosition;
	Vector3 m_position;
	Lantern* m_lantern1;
	Lantern* m_lantern2; 
	Lantern* m_lantern3;
	Lantern* m_lantern4;

	int m_moveState = 0;
	bool m_moving = false;
};

