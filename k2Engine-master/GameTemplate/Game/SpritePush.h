#pragma once
class SpritePush :public IGameObject
{
public:
	SpritePush();
	~SpritePush();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_spriteRender;
	Vector3 m_position;
};

