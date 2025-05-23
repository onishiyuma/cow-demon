#pragma once
class SpriteNoStone:public IGameObject
{
public:
	//メンバ関数。
	SpriteNoStone();
	~SpriteNoStone();

	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
private:
	//メンバ変数。
	SpriteRender		m_spriteRender;		//スプライトレンダー。
	Vector3				m_position;			//座標。
};