#pragma once

class LanternAttack;

class LanternAttackLight:public IGameObject
{
public:
	//メンバ関数
	LanternAttackLight();
	~LanternAttackLight();
	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_firstPosition;//初期座標
	Vector3 m_position;//座標
	Vector3 m_direction;//ライトの向き
	LanternAttack* m_lanternAttack;//攻撃灯籠
	PointLight m_pointLight;//ポイントライト

};

