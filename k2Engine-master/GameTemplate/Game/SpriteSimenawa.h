#pragma once

class Tutorial;

class SpriteSimenawa:public IGameObject
{
public:
	//メンバ関数。
	SpriteSimenawa();
	~SpriteSimenawa();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	//メンバ変数。
	SpriteRender	m_spriteRender;					//スプライトレンダー。
	const Vector3	m_position = Vector3::Zero;		//座標。
	const Vector3	m_scale=Vector3::One;			//大きさ。
};

