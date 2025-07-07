#pragma once

class Tutorial;

class SpriteTukuyomi:public IGameObject
{
public:
	//メンバ関数。
	SpriteTukuyomi();
	~SpriteTukuyomi();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	SpriteRender		m_spriteRender;					//スプライトレンダー。
	Vector3				m_position = Vector3::Zero;		//座標。
	const Vector3		m_scale=Vector3::One;			//大きさ。
};

