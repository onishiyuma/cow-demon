#pragma once


class CrossHair:public IGameObject
{
public:
	CrossHair();
	~CrossHair();
	void Update();
	void Render(RenderContext& rc);
	bool Start();

	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//メンバ変数。
	CrossHair* m_crosshair;//クロスヘアー。
	SpriteRender m_spriteRender;//スプライトレンダー。
	Vector3 m_position=Vector3::Zero;//座標。
};

