#include "stdafx.h"
#include "CrossHair.h"

namespace
{
	struct EnemyRayResultCallback : public MyRayResultCallback
	{
		btScalar	addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
		{	
			if (rayResult.m_hitFraction < hitFraction) {
				// こちらの方が近い。
				hitPos.Lerp(rayResult.m_hitFraction, rayStart, rayEnd);
			}
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
	const Vector3 cameraPos = g_camera3D->GetPosition();
	Vector3 rayTestEnd = cameraPos - g_camera3D->GetTarget();
	rayTestEnd.Normalize();
	Vector3 hitPoint;
	rayTestEnd.Scale(1000.0f);
	if (rayTestEnd.Length() >= 0.01)
	{
		EnemyRayResultCallback cb;
		bool isHIt = PhysicsWorld::GetInstance()->RayTest(cameraPos, rayTestEnd, hitPoint, cb);
		if (isHIt)
		{
			m_spriteRender.SetMulColor(g_vec4Red);
		}
		else
		{
			m_spriteRender.SetMulColor(g_vec4White);
		}
	}
}

void CrossHair::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}