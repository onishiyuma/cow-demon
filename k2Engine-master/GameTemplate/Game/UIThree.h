#pragma once

class UIThree : public IGameObject
{
public:
	//メンバ関数
	UIThree();
	~UIThree();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
	float m_timer = 0.0f;
	bool m_isMove = false;
	Vector3 m_scaleStart = { 1.0f, 1.0f, 1.0f };
	Vector3 m_scaleEnd = { 5.0f, 5.0f, 5.0f };
	Vector3 m_firstPosition = { 0.0f, 200.0f, 0.0f };
	Vector3 m_position;
	Vector4 m_color = { 1.0f, 1.0f, 1.0f, 0.8f };

	SpriteRender m_spriteRender;
};

