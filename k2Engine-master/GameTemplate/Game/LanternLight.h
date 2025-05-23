#pragma once

class Lantern;//灯籠クラス。

class LanternLight:public IGameObject
{
public:
	//メンバ関数。
	LanternLight();
	~LanternLight();
	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

	//メンバ変数。
public:
	Vector3			m_firstPosition;		//初期座標。
	Vector3			m_position;				//座標。
private:
	Vector3			m_direction;			//ライトの向き。
	Lantern*		m_lantern;				//灯籠。
	PointLight		m_pointLight;			//ポイントライト。
};

