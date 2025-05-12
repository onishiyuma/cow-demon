#pragma once

class LanternAttack;

class RedFlame:public IGameObject
{
public:
	//メンバ関数
	RedFlame();
	~RedFlame();
	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_firstPosition;
	Vector3 m_position;
	LanternAttack* m_lanternAttack;

};

