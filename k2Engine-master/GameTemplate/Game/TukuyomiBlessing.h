#pragma once

class Player;

#include "graphics/effect/EffectEmitter.h"

class TukuyomiBlessing:public IGameObject
{
public:
	TukuyomiBlessing();
	~TukuyomiBlessing();
	bool Start();
	void Render(RenderContext& rc);
	void Update();
	//エフェクト作成用関数。
	void CreateEffect();
	//敵の位置で判定を取る関数。
	void Distanxce();
	//継続時間。
	void Duration();

	//座標をセットする。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//座標を取得する。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//メンバ変数
	Player* m_player;//プレイヤー。
	EffectEmitter* m_effectEmitter;//エフェクト。
	Vector3 m_position;//座標。
	float m_tukuyomiBlessingTimer;//月読の加護の継続時間。
};