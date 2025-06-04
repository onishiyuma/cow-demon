#pragma once

class Ray;

class CrossHair:public IGameObject
{
public:
	CrossHair();
	~CrossHair();
	void Update();
	void Render(RenderContext& rc);
	bool Start();

private:
	//メンバ変数。
	Ray* m_raycast;
	CrossHair*		m_crosshair;				//クロスヘアー。
	SpriteRender	m_spriteRender;				//スプライトレンダー。
	Vector3			m_position=Vector3::Zero;	//座標。
};

