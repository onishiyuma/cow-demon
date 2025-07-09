#pragma once
class FontMP:public IGameObject
{
public:
	//メンバ関数。
	FontMP();
	~FontMP();
	bool Start();
	void Update();
	void Render(RenderContext&rc);

private:
	//メンバ変数。
	FontRender		m_fontRenderer;			//フォントレンダー。
	Vector3			m_position;				//位置。
	Vector3			m_color;				//色。
	float			m_scale=1.0f;			//スケール。
	float			m_timer;				//タイマー。
};

