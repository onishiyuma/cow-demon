#pragma once

class LanternAttack;

class RedFlame:public IGameObject
{
public:
	//メンバ関数。
	RedFlame();
	~RedFlame();
	bool Start();
	//更新処理。
	void Update();
	//エフェクト作成用関数
	void CreateEffect();
	//描画処理。
	void Render(RenderContext& rc);

	//メンバ変数。
	LanternAttack*      m_lanternAttack;//攻撃用灯籠。
	Vector3	            m_firstPosition;//初期座標。
	Vector3	            m_position;//座標。
	EffectEmitter*      m_effectEmitter;//エフェクトエミッター。
};

