#include "stdafx.h"
#include "Amulet.h"
#include "Player.h"
#include "collision/CollisionObject.h"
#include "GameCamera.h"


bool Amulet::Start()
{
	//繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ繧｢繝峨Ξ繧ｹ繧呈､懃ｴ｢縲・
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_player = FindGO<Player>("player");

	//繧ｨ繝輔ぉ繧ｯ繝医ｒ繝ｭ繝ｼ繝峨☆繧九・
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/hit.efk");

	//繧ｫ繝｡繝ｩ陦悟・繧貞燕譁ｹ蜷代↓莉｣蜈･縲・
	Matrix cameraMatrix = g_camera3D->GetCameraRotation();
	m_direction = Vector3(cameraMatrix.m[2][0], cameraMatrix.m[2][1], cameraMatrix.m[2][2]);
	m_direction.Normalize();

	//遘ｻ蜍暮溷ｺｦ繧定ｨ育ｮ励・
	m_moveSpeed = m_direction * m_amuletSpeed;

	//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧剃ｽ懈・縲・
	CreateCollision();

	//繧ｨ繝輔ぉ繧ｯ繝医ｒ菴懈・縲・
	CreateEffect();

	return true;
}

Amulet::Amulet()
{

}

Amulet::~Amulet()
{
	DeleteGO(m_collisionObj);
	DeleteGO(m_effectEmitter);
}

void Amulet::Update()	
{
	//蠎ｧ讓吶ｒ遘ｻ蜍輔＆縺帙ｋ縲・
	m_position += m_moveSpeed * g_gameTime->GetFrameDeltaTime() * 4.0f;

	if (m_effectEmitter->GetEffect() != nullptr)
	{
		//繧ｨ繝輔ぉ繧ｯ繝医↓蠎ｧ讓吶ｒ險ｭ螳壹・
		m_effectEmitter->SetPosition(m_position);
	}
	//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧ｪ繝悶ず繧ｧ繧ｯ繝医↓蠎ｧ讓吶ｒ險ｭ螳壹☆繧九・
	m_collisionObj->SetPosition(m_position);

	//繧ｿ繧､繝槭・繧貞刈邂励・
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();
	//繧ｿ繧､繝槭・縺御ｸ螳壹・遘呈焚邨碁℃縺励※縺・◆繧峨・
	if (m_deleteTimer >= 0.38f)
	{
		//閾ｪ霄ｫ繧貞炎髯､縲・
		DeleteGO(this);
		//繧ｨ繝輔ぉ繧ｯ繝医・蜀咲函繧貞●豁｢縲・
		m_effectEmitter->Stop();
	}
}

void Amulet::CreateCollision()
{
	//繧ｫ繝｡繝ｩ縺ｮ迴ｾ蝨ｨ菴咲ｽｮ繧貞叙蠕励ゑｼ郁ｦ也せ菴咲ｽｮ・・
	Vector3 cameraPosition = g_camera3D->GetPosition();

	//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧ｪ繝悶ず繧ｧ繧ｯ繝医・菴懈・縲・
	m_collisionObj = NewGO<CollisionObject>(0);

	//邂ｱ迥ｶ縺ｮ繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧剃ｽ懈・縲・
	m_collisionObj->CreateBox(m_position, Quaternion::Identity, { 100.0f,100.0f,100.0f });

	//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ縺ｮ蜷榊燕縲・
	m_collisionObj->SetName("purification");

	//繧ｪ繝悶ず繧ｧ繧ｯ繝医′蜍晄焔縺ｫ蜑企勁縺輔ｌ縺ｪ縺・ｈ縺・↓縲・
	m_collisionObj->SetIsEnableAutoDelete(false);
}

void Amulet::CreateEffect()
{
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(0);
	//繧ｨ繝輔ぉ繧ｯ繝医・螟ｧ縺阪＆繧定ｨｭ螳壹☆繧九・
	m_effectEmitter->SetScale({ 55.0f,55.0f,55.0f });
	//繧ｨ繝輔ぉ繧ｯ繝医・蠎ｧ讓吶ｒ繧ｻ繝・ヨ縺吶ｋ縲・
	m_effectEmitter->SetPosition(m_position);
	m_effectEmitter->Play();
}
