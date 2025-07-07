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
	SpriteRender		m_spriteRender;								//スプライト。
	const Vector3		m_position{ 300.0f, -150.0f, 0.0f };		//座標。
	const Vector3		m_scale = Vector3::One;						//大きさ。
};