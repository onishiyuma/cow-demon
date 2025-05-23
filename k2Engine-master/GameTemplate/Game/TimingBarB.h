#pragma once
class TimingBarB :public IGameObject
{
	//メンバ関数。
public:
	TimingBarB();
	~TimingBarB();

	bool Start();

	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	SpriteRender	m_spriteRender;		//スプライトレンダー。
	Vector3			m_position;			//座標。

};

