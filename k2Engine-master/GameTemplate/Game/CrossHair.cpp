#include "stdafx.h"
#include "CrossHair.h"

namespace
{
	//rayの大きさを設定。
	const float RAY_LENGTH = 2600.0f;
}

namespace
{
	struct EnemyRayResultCallback : public MyRayResultCallback
	{
		btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{	
			//最も近いヒット位置を記録。
			if (rayResult.m_hitFraction < hitFraction) {
				// こちらの方が近い。
				hitPos.Lerp(rayResult.m_hitFraction, rayStart, rayEnd);
			}
			//敵とヒットしたか確認。
			if (rayResult.m_collisionObject->getUserIndex() == EnCollisionAttr::enCollisionAttr_Enemy)
			{
				isHit = true;
			}
			return rayResult.m_hitFraction;
		}
	};
}

bool CrossHair::Start()
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/CrossHair.DDS", 120.0f, 120.0f);
	//座標をセット。
	m_spriteRender.SetPosition(m_position);
	return true;
}

CrossHair::CrossHair()
{

}

CrossHair::~CrossHair()
{
	DeleteGO(this);
}

void CrossHair::Update()
{
	//レイを当てて判定を取る処理。
	HitRayCast();
}

void CrossHair::HitRayCast()
{
	//カメラの位置と向きを取得。
	const Vector3 cameraPos = g_camera3D->GetPosition();
	Vector3 cameraForward = g_camera3D->GetTarget() - cameraPos;
	//正規化。
	cameraForward.Normalize();
	cameraForward.Scale(RAY_LENGTH);
	Vector3 rayTestEnd = cameraPos + cameraForward;
	Vector3 hitPoint;
	if (rayTestEnd.Length() >= 0.01)
	{
		EnemyRayResultCallback cb;
		bool isHIt = PhysicsWorld::GetInstance()->RayTest(cameraPos, rayTestEnd, hitPoint, cb);
		if (isHIt)
		{
			//赤色に。
			m_spriteRender.SetMulColor(g_vec4Red);
		}
		else
		{
			//白色に。
			m_spriteRender.SetMulColor(g_vec4White);
		}
	}
}

void CrossHair::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}