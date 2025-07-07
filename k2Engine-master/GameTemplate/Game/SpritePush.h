#pragma once
class SpritePush :public IGameObject
{
	//メンバ関数。
public:
	SpritePush();
	~SpritePush();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	//メンバ変数。
	SpriteRender		m_spriteRender;				//スプライトレンダー。
	Vector3				m_position;					//座標。
	const Vector3		m_scale = Vector3::One;		//大きさ。
};

