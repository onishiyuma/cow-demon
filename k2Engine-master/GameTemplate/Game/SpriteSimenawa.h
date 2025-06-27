#pragma once

class Tutorial;

class SpriteSimenawa:public IGameObject
{
public:
	//メンバ関数
	SpriteSimenawa();
	~SpriteSimenawa();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale;
	SpriteRender m_spriteRender;
};

