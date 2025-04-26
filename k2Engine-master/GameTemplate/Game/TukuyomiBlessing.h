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
	//コリジョン作成用関数
	void CreateCollision();
	//エフェクト作成用関数。
	void CreateEffect();
	//継続時間。
	void DeleteTime();
	void Move();

	//座標をセットする。
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	//現在の座標を取得し続ける。
	void RealTimeSetPosition(Vector3& position)
	{
		m_position = position;
	}

	//座標を取得する。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//メンバ変数
	CollisionObject* m_collisionObject;//コリジョンオブジェクト
	Player* m_player;//プレイヤー。
	EffectEmitter* m_effectEmitter;//エフェクト。
	Vector3 m_position;//座標。
	float m_deleteTimer=0.0f;//削除までの時間。
	float m_tukuyomiBlessingTimer;//月読の加護の継続時間。
	const float m_duration=10.0f;//継続時間。
};