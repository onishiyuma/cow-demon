#pragma once

class Tutorial;

class SpriteSkil:public IGameObject
{
public:
	//メンバ関数。
	SpriteSkil();
	~SpriteSkil();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数。
	SpriteRender		m_spriteRender;					//スプライトレンダー。
	const Vector3		m_position = Vector3::Zero;		//座標。
	const Vector3		m_scale = Vector3::One;			//大きさ。
};

