#pragma once

#include"graphics/effect/EffectEmitter.h"

class Lantern;

class BlueFlame:public IGameObject
{
public:
	//メンバ関数
	BlueFlame();
	~BlueFlame();
	bool Start();
	//更新処理
	void Update();
	//エフェクト作成用関数
	void CreateEffect();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_firstPosition;//初期座標
	Vector3 m_position;//座標
	EffectEmitter* m_effectEmitter = nullptr;//エフェクト
	Lantern* m_lantern;//灯籠

};

