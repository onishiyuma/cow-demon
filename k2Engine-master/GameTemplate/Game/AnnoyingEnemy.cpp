#include "stdafx.h"
#include "AnnoyingEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "Poison.h"
#include "EnemyBase.h"
#include "Game.h"


//#include "collision/CollisionObject.h"
#include<time.h>
#include<stdlib.h>

AnnoyingEnemy::AnnoyingEnemy()
{

}

bool AnnoyingEnemy::Start()
{
	//待機。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/AnnoyingEnemy/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//歩き。
	m_animationClips[enAnimationClip_walk].Load("Assets/animData/AnnoyingEnemy/walk.tka");
	m_animationClips[enAnimationClip_walk].SetLoopFlag(true);
	//走り。
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/AnnoyingEnemy/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//毒ブレス。
	m_animationClips[enAnimationClip_Poison].Load("Assets/animData/AnnoyingEnemy/poison.tka");
	m_animationClips[enAnimationClip_Poison].SetLoopFlag(true);
	//ダメージ。
	m_animationClips[enAnimationClip_Damage].Load("Assets/animData/AnnoyingEnemy/receivedamage.tka");
	m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	//ダウン
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/AnnoyingEnemy/down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/LittleEnemy/enemy.tkm", m_animationClips, enAnimationClip_Num);

	//座標を更新する。
	m_modelRender.SetPosition(m_position);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	//大きさを設定する。
	//m_modelRender.SetScale(m_scale);
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position
	);
	Vector3 scale(100.0f, 100.0f, 1.00f);
	SetScale(scale);
	//アニメーションイベント用の関数を設定する。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OneAnimationEvent(clipName, eventName);
		});

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/Effect/Poison.efk");

	m_player = FindGO<Player>("player");

	//乱数を初期化する。
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

void AnnoyingEnemy::Update()
{
	//退散処理。
	//Leave();
	//追跡処理。
	Chase();
	//回転処理。
	Rotation();
	//当たり判定。
	Collision();
	//アニメーションの再生。
	PlayAnimation();
	//ステート管理。
	ManageState();

	//モデルの更新。
	m_modelRender.Update();
}

void AnnoyingEnemy::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f && fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//プレイヤーの前ベクトルを計算する。
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void AnnoyingEnemy::Chase()
{
	//追跡ステートでないなら追跡しない。
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}
	/*m_moveSpeed.y-=980.0f*g_gameTime->GetFrameDeltaTime();*/
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround())
	{
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPositon = m_position;
	modelPositon.y += 2.5f;
	m_modelRender.SetPosition(modelPositon);
}

void AnnoyingEnemy::Collision()
{
	//被ダメージ、あるいはダウンステートの時は当たり判定処理はしない
	if (m_enemyState == enEnemyState_Damage ||
		m_enemyState == enEnemyState_Down)
	{
		return;
	}

	{
		//プレイヤー攻撃用のコリジョンを取得する
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("purification");
		//コリジョンの配列をfor文で回す
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突したら
			if (collision->IsHit(m_charaCon))
			{
				//HPを減らす
				m_enemyHP -= 5;
				//HPが0になったら
				m_enemyState = enEnemyState_Down;
			}
			else {
				//被ダメージステートに遷移する
				m_enemyState = enEnemyState_Damage;
			}
			return;
		}
	}

	{
		//プレイヤーのスキル用のコリジョンを取得する
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("amulet");
		//for文で配列を回す
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突する
			if (collision->IsHit(m_charaCon))
			{
				m_enemyHP -= 10;
				//HPが0になったら
				if (m_enemyHP < 0)
				{
					//ダウンステートに遷移する
					m_enemyState = enEnemyState_Down;
				}

				else {
					//被ダメージステートに遷移する
					m_enemyState = enEnemyState_Damage;
				}
				return;
			}
		}
	}

	{
		//しめ縄のスキル用コリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("Shimenawa");
		//for文で配列を回す
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突する
			if (collision->IsHit(m_charaCon))
			{

				m_enemyState = enEnemyState_Idle;
				return;
			}
		}
	}
}

const bool AnnoyingEnemy::SearchPlayer()const
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//対象に近くなったら
	if (diff.LengthSq() <= 700.0f * 700.0f)
	{
		//エネミーからプレイヤーに向かうベクトルを正規化する
		diff.Normalize();
		//内積(cos0)を調べる
		float cos = m_forward.Dot(diff);
		//内積(cos0)から角度を求める
		float angle = acosf(cos);
		//角度を(0)が120度より小さければ
		if (angle <= (Math::PI / 360.0f) * 360.0f)
		{
			//プレイヤーを見つけられた
			return true;
		}

	}
	return false;
}

/*void BossEnemy::Leave()
{
	//退散ステート出ないなら,退散処理はしない
	if (m_enemyState != enEnemyState_Leave)
	{
		return;
	}

	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void BossEnemy::PoisonAttack()
{
	//攻撃ステートでないなら処理はしない
	//攻撃処理要ステートが出ないなら処理はしない
	if (m_enemyState != enEnemyState_Poison)
	{
		return;
	}

	//攻撃中であれば
	if (m_isUnderAttack == true)n
	{
		//攻撃用のコリジョンを作成する
		MakePoison()
	}
}*/

void AnnoyingEnemy::MakePoison()
{
	//毒ブレスのオブジェクトを作成する。
	Poison* poison = NewGO<Poison>(0);
	Vector3 PoisonPosition = m_position;
	//座標を少し上に設定する。
	PoisonPosition.y += 50.0f;
	//座標を設定する。
	poison->SetPosition(PoisonPosition);
	//回転を設定する。
	poison->SetRotation(m_rotation);
	//射手を設定する。
	poison->SetEnEnemy(Poison::enPoison_LittleEnemy);
}

void AnnoyingEnemy::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら
	if (m_idleTimer >= 0.9f)
	{
		//他のステートに遷移する
		ProcessCommonStateTransition();
	}
}

void AnnoyingEnemy::ProcessChaseStateTransition()
{
	/*//攻撃ができる距離なら
if (IsCanAttack() == true)
{
	//他のステートに遷移する
	ProcessCommonStateTransition();
	return;
}*/

	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら
	if (m_chaseTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
}

/*void BossEnemy::ProcessLeaveStateTransition()
{
	//距離が近いなら
	if (IsLeave() == true)
	{
		//他のステートに遷移する
		ProcessCommonStateTransition();
		return;
	}
	m_leaveTimer += g_gameTime->GetFrameDeltaTime();
		//退散時間がある程度経過したら
	if (m_leaveTimer >= 0.8f)
	{
		//他のステートに遷移する
		ProcessCommonStateTransition();
	}
}*/

void AnnoyingEnemy::ProcessPoisonAttackStateTransition()
{
	//遠距離攻撃アニメーションの再生が終わったら
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		ProcessCommonStateTransition();
		return;
	}
	//追跡時間がある程度経過したら
	if (m_poisonAttackCoolDown >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
	m_poisonAttackCoolDown += g_gameTime->GetFrameDeltaTime();
}

void AnnoyingEnemy::ProcessDamageStateTransition()
{
	//被ダメージアニメーションの再生が終わったら
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//攻撃されたら距離関係なしに退散させる
		m_enemyState = enEnemyState_Chase;
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		//移動速度を設定する
		m_moveSpeed = diff * 10.0f;
	}
}

void AnnoyingEnemy::ProcessDownStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		Game* game = FindGO<Game>("game");
		DeleteGO(this);
	}
}

void AnnoyingEnemy::ProcessCommonStateTransition()
{
	//各タイマーを初期化
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	m_poisonAttackCoolDown = 0.0f;


	Vector3 diff = m_player->GetPosition() - m_position;
	//プレイヤーを見つけたら
	if (SearchPlayer() == true)
	{
		//ベクトルを正規化する
		diff.Normalize();
		//移動速度計算する
		m_moveSpeed = diff * 100.0f;
		//攻撃できをる距離なら
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

void AnnoyingEnemy::ManageState()
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

void AnnoyingEnemy::PlayAnimation()
{
	m_modelRender.SetAnimationSpeed(1.0f);
	switch (m_enemyState)
	{
	case enEnemyState_Idle:
		//待機ステート
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
	case enEnemyState_Chase:
		//追跡ステート
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
		/*case enEnemyState_Leave:
			//退散ステート
			m_modelRender.SetAnimationSpeed(1.2f);
			m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
			break;*/
	case enEnemyState_Poison:
		//遠距離攻撃ステート
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Poison, 0.1f);
		break;
	case enEnemyState_Damage:
		//被ダメージステート
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Damage, 0.1f);
		break;
	case enEnemyState_Down:
		//ダウンステート
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Down, 0.1f);
		break;
	default:
		break;
	}
}

void AnnoyingEnemy::OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;

	if (wcscmp(eventName, L"magic_attack") == 0) {
		MakePoison();
	}
}

const bool AnnoyingEnemy::IsCanAttack()const
{
	Vector3 diff = m_player->GetPosition() - m_position;
	//エネミーとプレイヤーの距離が近かったら
	if (diff.LengthSq() <= 10000.0f * 1000.0f)
	{
		//攻撃可
		return true;
	}
	//攻撃不可
	return false;
}

void AnnoyingEnemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}