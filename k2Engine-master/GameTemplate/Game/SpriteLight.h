#pragma once
class SpriteLight :public IGameObject
{
public:
	//メンバ関数。
	SpriteLight();
	~SpriteLight();
	bool Start();
	//移動処理。
	void Move();
	void Update();
	void Render(RenderContext& rc);
private:
	//メンバ変数。
	SpriteRender	m_spriteRender;		//スプライトレンダー。
	Vector3			m_position;			//座標。
};

