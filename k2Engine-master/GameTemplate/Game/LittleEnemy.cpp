#include "stdafx.h"
#include "LittleEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "Poison.h"
#include "Game.h"

//#include"collision/CollisionObject.h"
#include<time.h>
#include<stdlib.h>


LittleEnemy::LittleEnemy()
{

}

LittleEnemy::~LittleEnemy()
{

}

bool LittleEnemy::Start()
{   //蠕・ｩ・
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/littleEnemy/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//豁ｩ陦・
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/littleEnemy/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	//襍ｰ陦・
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/littleEnemy/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	////迢ｬ繝悶Ξ繧ｹ
	m_animationClips[enAnimationClip_Poison].Load("Assets/animData/littleEnemy/poison.tka");
	m_animationClips[enAnimationClip_Poison].SetLoopFlag(true);
	//繝繝｡繝ｼ繧ｸ
	m_animationClips[enAnimationClip_Damage].Load("Assets/animData/littleEnemy/receivedamage.tka");
	m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	//繝繧ｦ繝ｳ
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/littleEnemy/down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/LittleEnemy/enemy.tkm", m_animationClips, enAnimationClip_Num);

	//蠎ｧ讓吶ｒ譖ｴ譁ｰ縺吶ｋ
	m_modelRender.SetPosition(m_position);
	//蝗櫁ｻ｢繧定ｨｭ螳壹☆繧・
	m_modelRender.SetRotation(m_rotation);
	////螟ｧ縺阪＆繧定ｨｭ螳壹☆繧・
	//m_modelRender.SetScale(m_scale);
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position
	);

	Vector3  scale(100.0f, 100.0f, 100.0f);
	SetScale(scale);
	//繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧､繝吶Φ繝育畑縺ｮ髢｢謨ｰ繧定ｨｭ螳壹☆繧・
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OneAnimationEvent(clipName, eventName);
		});

	////繧ｨ繝輔ぉ繧ｯ繝医ｒ隱ｭ縺ｿ霎ｼ繧
	//EffectEngine::GetInstance()->ResistEffect(1, u"Assets/Effect/Poison.efk");

	m_player = FindGO<Player>("player");
	//荵ｱ謨ｰ繧貞・譛溷喧縺吶ｋ
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
	return true;
}

void LittleEnemy::Update()
{
	////騾謨｣蜃ｦ逅・
	//Leave();
	//霑ｽ霍｡蜃ｦ逅・
	Chase();
	//蝗櫁ｻ｢蜃ｦ逅・
	Rotation();
	//蠖薙◆繧雁愛螳・
	Collision();
	//繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蜀咲函
	PlayAnimation();
	//繧ｹ繝・・繝育ｮ｡逅・
	ManageState();
	//繝｢繝・Ν縺ｮ譖ｴ譁ｰ
	m_modelRender.Update();
}

void LittleEnemy::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);

	//蝗櫁ｻ｢繧定ｨｭ螳壹☆繧・
	m_modelRender.SetRotation(m_rotation);

	//繝励Ξ繧､繝､繝ｼ縺ｮ蜑阪・繧ｯ繝医Ν繧定ｨ育ｮ励☆繧・
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void LittleEnemy::Chase()
{
	//霑ｽ霍｡繧ｹ繝・・繝医〒縺ｪ縺・↑繧峨∬ｿｽ霍｡蜃ｦ逅・・縺励↑縺・
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}
	/*m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();*/
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//蝨ｰ髱｢縺ｫ縺､縺・◆
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void LittleEnemy::Collision()
{
	//陲ｫ繝繝｡繝ｼ繧ｸ縲√≠繧九＞縺ｯ繝繧ｦ繝ｳ繧ｹ繝・・繝医・譎ゅ・
	//蠖薙◆繧雁愛螳壼・逅・・縺励↑縺・/
	if (m_enemyState == enEnemyState_Damage ||
		m_enemyState == enEnemyState_Down)
	{
		return;
	}

	{
		//繝励Ξ繧､繝､繝ｼ謾ｻ謦・畑縺ｮ繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧貞叙蠕励☆繧・
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("purification");
		//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ縺ｮ驟榊・繧断or譁・〒蝗槭☆
		for (auto collision : collisions)
		{
			//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ縺ｨ繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺瑚｡晉ｪ√＠縺溘ｉ
			if (collision->IsHit(m_charaCon))
			{
				//HP繧呈ｸ帙ｉ縺・
				m_enemyHP -= 5;
				//HP縺・縺ｫ縺ｪ縺｣縺溘ｉ
				m_enemyState = enEnemyState_Down;
			}
			else {
				//陲ｫ繝繝｡繝ｼ繧ｸ繧ｹ繝・・繝医↓驕ｷ遘ｻ縺吶ｋ
				m_enemyState = enEnemyState_Damage;
			}
			return;
		}
	}

	{
		//繝励Ξ繧､繝､繝ｼ縺ｮ繧ｹ繧ｭ繝ｫ逕ｨ縺ｮ繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧貞叙蠕励☆繧・
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("amulet");
		//for譁・〒驟榊・繧貞屓縺・
		for (auto collision : collisions)
		{
			//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ縺ｨ繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺瑚｡晉ｪ√☆繧・
			if (collision->IsHit(m_charaCon))
			{
				m_enemyHP -= 10;
				//HP縺・縺ｫ縺ｪ縺｣縺溘ｉ
				if (m_enemyHP < 0)
				{
					//繝繧ｦ繝ｳ繧ｹ繝・・繝医↓驕ｷ遘ｻ縺吶ｋ
					m_enemyState = enEnemyState_Down;
				}

				else {
					//陲ｫ繝繝｡繝ｼ繧ｸ繧ｹ繝・・繝医↓驕ｷ遘ｻ縺吶ｋ
					m_enemyState = enEnemyState_Damage;
				}
				return;
			}
		}
	}

	{
		//しめ縄のスキル用コリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("Shimenawa");
		//for譁・〒驟榊・繧貞屓縺・
		for (auto collision : collisions)
		{
			//繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ縺ｨ繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺瑚｡晉ｪ√☆繧・
			if (collision->IsHit(m_charaCon))
			{

				m_enemyState = enEnemyState_Idle;
				return;
			}
		}
	}

}

const bool LittleEnemy::SearchPlayer()const
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//蟇ｾ雎｡縺ｫ霑代￥縺ｪ縺｣縺溘ｉ
	if (diff.LengthSq() <= 700.0f * 700.0f)
	{
		//繧ｨ繝阪Α繝ｼ縺九ｉ繝励Ξ繧､繝､繝ｼ縺ｫ蜷代°縺・・繧ｯ繝医Ν繧呈ｭ｣隕丞喧縺吶ｋ
		diff.Normalize();
		//蜀・ｩ・cos0)繧定ｪｿ縺ｹ繧・
		float cos = m_forward.Dot(diff);
		//蜀・ｩ・cos0)縺九ｉ隗貞ｺｦ繧呈ｱゅａ繧・
		float angle = acosf(cos);
		//隗貞ｺｦ繧・0)縺・20蠎ｦ繧医ｊ蟆上＆縺代ｌ縺ｰ
		if (angle <= (Math::PI / 360.0f) * 360.0f)
		{
			//繝励Ξ繧､繝､繝ｼ繧定ｦ九▽縺代ｉ繧後◆
			return true;
		}

	}
	return false;
}

//void LittleEnemy::Leave()
//{
//	//騾謨｣繧ｹ繝・・繝亥・縺ｪ縺・↑繧・騾謨｣蜃ｦ逅・・縺励↑縺・
//	if (m_enemyState != enEnemyState_Leave)
//	{
//		return;
//	}
//
//	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
//	if (m_charaCon.IsOnGround())
//	{
//		m_moveSpeed.y = 0.0f;
//	}
//	Vector3 modelPosition = m_position;
//	m_modelRender.SetPosition(modelPosition);
//}
//
void LittleEnemy::PoisonAttack()
{
	//謾ｻ謦・せ繝・・繝医〒縺ｪ縺・↑繧牙・逅・・縺励↑縺・
	//謾ｻ謦・・逅・ｦ√せ繝・・繝医′蜃ｺ縺ｪ縺・↑繧牙・逅・・縺励↑縺・
	if (m_enemyState != enEnemyState_Poison)
	{
		return;
	}

	//謾ｻ謦・ｸｭ縺ｧ縺ゅｌ縺ｰ
	if (m_isUnderAttack == true)
	{
		//謾ｻ謦・畑縺ｮ繧ｳ繝ｪ繧ｸ繝ｧ繝ｳ繧剃ｽ懈・縺吶ｋ
		MakePoison();
	}
}

void LittleEnemy::MakePoison()
{
	//豈偵ヶ繝ｬ繧ｹ縺ｮ繧ｪ繝悶ず繧ｧ繧ｯ繝医ｒ菴懈・縺吶ｋ
	Poison* poison = NewGO<Poison>(0);
	Vector3 PoisonPosition = m_position;
	//蠎ｧ讓吶ｒ蟆代＠荳翫↓險ｭ螳壹☆繧・
	PoisonPosition.y += 50.0f;
	//蠎ｧ讓吶ｒ險ｭ螳壹☆繧・
	poison->SetPosition(PoisonPosition);
	//蝗櫁ｻ｢繧定ｨｭ螳壹☆繧・
	poison->SetRotation(m_rotation);
	//蟆・焔繧定ｨｭ螳壹☆繧・
	poison->SetEnEnemy(Poison::enPoison_LittleEnemy);
}

void LittleEnemy::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//蠕・ｩ滓凾髢薙′縺ゅｋ遞句ｺｦ邨碁℃縺励◆繧・
	if (m_idleTimer >= 0.9f)
	{
		//莉悶・繧ｹ繝・・繝医↓驕ｷ遘ｻ縺吶ｋ
		ProcessCommonStateTransition();
	}
}
void LittleEnemy::ProcessChaseStateTransition()
{
	////謾ｻ謦・′縺ｧ縺阪ｋ霍晞屬縺ｪ繧・
	if (IsCanAttack() == true)
	{
		//莉悶・繧ｹ繝・・繝医↓驕ｷ遘ｻ縺吶ｋ
		ProcessCommonStateTransition();
		return;
	}
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//霑ｽ霍｡譎る俣縺後≠繧狗ｨ句ｺｦ邨碁℃縺励◆繧・
	if (m_chaseTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
}

//void LittleEnemy::ProcessLeaveStateTransition()
//{
//	//霍晞屬縺瑚ｿ代＞縺ｪ繧・
//	if (IsLeave() == true)
//	{
//		//莉悶・繧ｹ繝・・繝医↓驕ｷ遘ｻ縺吶ｋ
//		ProcessCommonStateTransition();
//		return;
//	}
//	m_leaveTimer += g_gameTime->GetFrameDeltaTime();
//		//騾謨｣譎る俣縺後≠繧狗ｨ句ｺｦ邨碁℃縺励◆繧・
//	if (m_leaveTimer >= 0.8f)
//	{
//		//莉悶・繧ｹ繝・・繝医↓驕ｷ遘ｻ縺吶ｋ
//		ProcessCommonStateTransition();
//	}
//}

void LittleEnemy::ProcessPoisonAttackStateTransition()
{

	//驕霍晞屬謾ｻ謦・い繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蜀咲函縺檎ｵゅｏ縺｣縺溘ｉ
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		ProcessCommonStateTransition();
		return;
	}
	//霑ｽ霍｡譎る俣縺後≠繧狗ｨ句ｺｦ邨碁℃縺励◆繧・
	if (m_poisonAttackCoolDown >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
	m_poisonAttackCoolDown += g_gameTime->GetFrameDeltaTime();

}

void LittleEnemy::ProcessDamageStateTransition()
{
	//陲ｫ繝繝｡繝ｼ繧ｸ繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ蜀咲函縺檎ｵゅｏ縺｣縺溘ｉ
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//謾ｻ謦・＆繧後◆繧芽ｷ晞屬髢｢菫ゅ↑縺励↓騾謨｣縺輔○繧・
		m_enemyState = enEnemyState_Chase;
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		//遘ｻ蜍暮溷ｺｦ繧定ｨｭ螳壹☆繧・
		m_moveSpeed = diff * 10.0f;
	}
}

void LittleEnemy::ProcessDownStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		Game* game = FindGO<Game>("Game");
		DeleteGO(this);
	}
}

void LittleEnemy::ProcessCommonStateTransition()
{
	//蜷・ち繧､繝槭・繧貞・譛溷喧
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	m_poisonAttackCoolDown = 0.0f;


	Vector3 diff = m_player->GetPosition() - m_position;
	//繝励Ξ繧､繝､繝ｼ繧定ｦ九▽縺代◆繧・
	if (SearchPlayer() == true)
	{
		//繝吶け繝医Ν繧呈ｭ｣隕丞喧縺吶ｋ
		diff.Normalize();
		//遘ｻ蜍暮溷ｺｦ險育ｮ励☆繧・
		m_moveSpeed = diff * 100.0f;
		//謾ｻ謦・〒縺阪ｒ繧玖ｷ晞屬縺ｪ繧・
		if (IsCanAttack() == true)
		{
			int ram = rand() % 100;
			if (ram > 90)
			{
				m_enemyState = enEnemyState_Chase;

			}

			else
			{
				m_enemyState = enEnemyState_Poison;
				return;
			}
		}
		else
		{
			m_enemyState = enEnemyState_Chase;
		}

	}
	else
	{
		m_enemyState = enEnemyState_Idle;
		return;
	}
}




void LittleEnemy::ManageState()
{
	switch (m_enemyState)
	{
	case enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
	case enEnemyState_Chase:
		ProcessChaseStateTransition();
		break;
		/*case enEnemyState_Leave:
			ProcessLeaveStateTransition();
			break;*/
	case enEnemyState_Poison:
		ProcessPoisonAttackStateTransition();
		break;
	case enEnemyState_Damage:
		ProcessDamageStateTransition();
		break;
	case enEnemyState_Down:
		ProcessDownStateTransition();
		break;
	default:
		break;
	}
}

void LittleEnemy::PlayAnimation()
{
	m_modelRender.SetAnimationSpeed(1.0f);
	switch (m_enemyState)
	{
	case enEnemyState_Idle:
		//蠕・ｩ溘せ繝・・繝・
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
	case enEnemyState_Chase:
		//霑ｽ霍｡繧ｹ繝・・繝・
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
		//case enEnemyState_Leave:
		//	//騾謨｣繧ｹ繝・・繝・
		//	m_modelRender.SetAnimationSpeed(1.2f);
		//	m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		//	break;
	case enEnemyState_Poison:
		//驕霍晞屬謾ｻ謦・せ繝・・繝・
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Poison, 0.1f);
		break;
	case enEnemyState_Damage:
		//陲ｫ繝繝｡繝ｼ繧ｸ繧ｹ繝・・繝・
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Damage, 0.1f);
		break;
	case enEnemyState_Down:
		//繝繧ｦ繝ｳ繧ｹ繝・・繝・
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Down, 0.1f);
		break;
	default:
		break;
	}
}

void LittleEnemy::OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;

	if (wcscmp(eventName, L"magic_attack") == 0) {
		MakePoison();
	}
}

const bool LittleEnemy::IsCanAttack()const
{
	Vector3 diff = m_player->GetPosition() - m_position;
	//繧ｨ繝阪Α繝ｼ縺ｨ繝励Ξ繧､繝､繝ｼ縺ｮ霍晞屬縺瑚ｿ代°縺｣縺溘ｉ
	if (diff.LengthSq() <= 10000.0f * 1000.0f)
	{
		//謾ｻ謦・庄
		return true;
	}
	//謾ｻ謦・ｸ榊庄
	return false;
}

void LittleEnemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


