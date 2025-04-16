#pragma once
class SpriteLight :public IGameObject
{
public:
	//ƒƒ“ƒoŠÖ”
	SpriteLight();
	~SpriteLight();

	bool Start();
	void Move();
	void Update();
	void Render(RenderContext& rc);

	//ƒƒ“ƒo•Ï”
	SpriteRender m_spriteRender;
	Vector3 m_position;
};

