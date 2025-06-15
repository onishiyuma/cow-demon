#pragma once


class CrossHair:public IGameObject
{
public:
	CrossHair();
	~CrossHair();
	void Update();
	void Render(RenderContext& rc);
	bool Start();
	//レイが当たる処理。
	void HitRayCast();

	//座標を取得。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//色を取得。
	const Vector4& GetColor() const
	{
		return m_spriteRender.GetMulColor();
	}

	//色を設定。
	const void SetColor(const Vector4& color)
	{
		m_spriteRender.SetMulColor(color);
	}

private:
	//メンバ変数。
	CrossHair*		m_crosshair;				//クロスヘアー。
	SpriteRender	m_spriteRender;				//スプライトレンダー。
	Vector3			m_position=Vector3::Zero;	//座標。
};

