#pragma once
class FontMP:public IGameObject
{
public:
	//メンバ関数
	FontMP();
	~FontMP();
	bool Start();
	void Update();
	void Render(RenderContext&rc);

	//メンバ変数
	Vector3 m_position; //位置
	Vector3 m_scale;    //スケール
	Vector3 m_color; //色
	FontRender m_fontRenderer; //フォントレンダラー

	float m_timer; //タイマー
};

