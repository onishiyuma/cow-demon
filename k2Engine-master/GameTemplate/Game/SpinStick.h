#pragma once


class SpinStick :public IGameObject
{
public:
	//メンバ関数。
	SpinStick();
	~SpinStick();

	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	SpriteRender		m_spriteRender;			//スプライト。
	Vector3				m_firstPosition;		//初期座標。
	Vector3				m_position;				//座標。

};