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
	m_volumePointLight.Init(m_pointLight);
	//ポイントライトの色を設定。
	m_pointLight.SetColor(Vector3(5.0f, 50.0f, 50.0f) * 0.0003f);

	//ポイントライトの範囲を設定。
	m_pointLight.SetRange(150.0f);
	//ポイントライトの影響力を設定。
	m_pointLight.SetAffectPowParam(2.0f);

	return true;
}

void LanternLight::Update()
{
	//ポイントライトの座標を設定。
	m_pointLight.SetPosition(m_firstPosition);
	//ポイントライトの更新。
	m_pointLight.Update();
	m_volumePointLight.Update();
}

void LanternLight::Render(RenderContext& rc)
{

}
