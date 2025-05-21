#include "stdafx.h"
#include "LanternLight.h"
#include "Lantern.h"

LanternLight::LanternLight()
{

}

LanternLight::~LanternLight()
{

}

bool LanternLight::Start()
{
	//各種インスタンスアドレスを検索する。
	m_lantern = FindGO<Lantern>("lantern1");
	m_lantern = FindGO<Lantern>("lantern2");
	m_lantern = FindGO<Lantern>("lantern3");
	m_lantern = FindGO<Lantern>("lantern4");

	//ポイントライトの初期化。
	m_pointLight.Init();
	//ポイントライトの色を設定。
	m_pointLight.SetColor(Vector3(0.35f, 0.5f, 0.5f));
	//ポイントライトの範囲を設定。
	m_pointLight.SetRange(500.0f);
	//ポイントライトの影響力を設定。
	m_pointLight.SetAffectPowParam(1.0f);

	return true;
}

void LanternLight::Update()
{
	//ポイントライトの座標を設定。
	m_pointLight.SetPosition(m_firstPosition);
	//ポイントライトの更新。
	m_pointLight.Update();
}

void LanternLight::Render(RenderContext& rc)
{

}
