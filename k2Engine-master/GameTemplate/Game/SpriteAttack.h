#pragma once

class Tutorial;

class SpriteAttack:public IGameObject
{
public:
	//メンバ関数
	SpriteAttack();
	~SpriteAttack();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale;
	SpriteRender m_spriteRender;

	Tutorial* m_tutorial;
};

