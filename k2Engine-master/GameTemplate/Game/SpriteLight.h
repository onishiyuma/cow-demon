#pragma once
class SpriteLight :public IGameObject
{
public:
	//メンバ関数
	SpriteLight();
	~SpriteLight();

	bool Start();
	void Move();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
	SpriteRender m_spriteRender;
	Vector3 m_position;
};

