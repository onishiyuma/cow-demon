#pragma once
class TimingBarA:public IGameObject
{
	//メンバ関数。
public:
	TimingBarA();
	~TimingBarA();

	bool Start();

	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	SpriteRender		m_spriteRender;		//スプライトレンダー。
	Vector3				m_position;			//座標。

};

