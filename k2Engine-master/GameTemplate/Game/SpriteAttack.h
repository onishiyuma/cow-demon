#pragma once

class Tutorial;

class SpriteAttack:public IGameObject
{
public:
	//メンバ関数。
	SpriteAttack();
	~SpriteAttack();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	SpriteRender		m_spriteRender;					//スプライトレンダー。
	Vector3				m_position = Vector3::Zero;		//座標。
	const Vector3		m_scale = {0.7f,0.7f,0.7f};		//大きさ。
};

