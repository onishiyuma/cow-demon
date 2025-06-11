#include "stdafx.h"
#include "AnnoyingEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "Poison.h"
#include "EnemyBase.h"
#include "Game.h"
#include "GameCamera.h"
#include "RingBell.h"

#include <time.h>
#include <stdlib.h>

namespace
{
	//スキルのチャージの増加量。
	int CHARGE_INCREASE_AMOUNT = 10;
}

AnnoyingEnemy::AnnoyingEnemy()
{

}


AnnoyingEnemy::~AnnoyingEnemy()
{
	if (m_effectEmitter)
	{
		m_effectEmitter->Stop();
		DeleteGO(m_effectEmitter);
		m_effectEmitter = nullptr;
	}
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

	m_modelRender.Init("Assets/modelData/fox/fox.tkm");

	//座標を更新する。
	m_modelRender.SetPosition(m_position);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	//大きさを設定する。
	m_modelRender.SetScale(m_scale);
	m_charaCon.Init(
		60.0f,
		60.0f,
		m_position
	);

	//ボーンのIDを取得する。
	m_ExplosionBoneId = m_modelRender.FindBoneID(L"Explosion");
	Vector3 scale(100.0f, 100.0f, 1.00f);
	SetScale(scale);

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(7, u"Assets/effect/EnemyEffects/Fox_Down/Fox_Down.efk");
	EffectEngine::GetInstance()->ResistEffect(10, u"Assets/effect/EnemyEffects/Fox_Explosion/Fox_Explosion.efk");

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_ringBell = FindGO<RingBell>("ringbell");

	//乱数を初期化する。
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	m_enemyHP = 5;

	return true;
}

void AnnoyingEnemy::Update()
{
	//モデルの更新。
	m_modelRender.Update();
	////爆発処理
	//Explode();
	//本殿追跡処理
	IsHonden();
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

	
}

/*void Enemy::MakeAttackCollision()
{
	//攻撃判定用のコリジョンオブジェクトを作成する。
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	collisionPosition += m_forward * 15.0f;
	collisionObject->CreateSphere(collisionPosition,
		Quaternion::Identity,
		70.0f
	);
	collisionObject->SetName("annoyingenemy_attack");
}*/

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

//void AnnoyingEnemy::Explode()
//{
//
//	// 爆発ステートでなければreturn
//	if (m_enemyState != enEnemyState_Explode)
//		return;
//
//	// 爆発処理を一度だけ行う
//	if (m_hasExploded == true)
//	{
//		// 爆発用のコリジョン生成
//		MakeExplosion();
//		
//	}
//}

void AnnoyingEnemy::MakeExplosion()
{
	//爆発コリジョンを生成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	collisionObject->CreateSphere(collisionPosition,Quaternion::Identity,300.0f);
	collisionObject->SetName("explosion");
	//エフェクトの発生位置
	Vector3 m_effectPosition = m_position;
    m_effectPosition.y += 10.0f;
	//爆発エフェクトを生成する
	//エフェクトの生成
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(10);
	m_effectEmitter->SetPosition(m_effectPosition);
	m_effectEmitter->SetScale(Vector3(75.0f, 75.0f, 75.0f));
	m_effectEmitter->Play();
	
}

void AnnoyingEnemy::DeathEffect()
{
	//エフェクトの発生位置
	Vector3 m_effectPosition = m_position;
	

	//エフェクトの生成
	m_effectEmitter = NewGO <EffectEmitter>(0);
	m_effectEmitter->Init(7);
	m_effectEmitter->SetPosition(m_effectPosition);
	m_effectEmitter->SetScale(Vector3(30.0f, 30.0f, 30.0f));
	m_effectEmitter->Play();

}

void AnnoyingEnemy::IsHonden()
{
	//追跡ステートでないなら、追跡処理はしない
	if (m_enemyState != enEnemyState_Main)
	{
		return;
	}
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//地面についた
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;

	m_modelRender.SetPosition(modelPosition);
}

void AnnoyingEnemy::Collision()
{
	//被ダメージ、あるいはダウンステートの時は当たり判定処理はしない。
	if (m_enemyState == enEnemyState_Damage ||m_enemyState == enEnemyState_Down)
	{
		return;
	}

	//-----------------------------------------
	//プレイヤーの攻撃判定処理。
	//-----------------------------------------

	{
		//プレイヤー攻撃用のコリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("purification");
		//コリジョンの配列をfor文で回す。
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突したら。
			if (collision->IsHit(m_charaCon))
			{
				//会心の設定。
				int ram = rand() % 100;
				if (ram < m_player->m_criticalRate)
				{
					m_enemyHP -= m_player->m_criticalATK;

					if (m_enemyHP <= 0)
					{
						m_enemyState = enEnemyState_Down;
					}
					else 
					{
						//被ダメージステートに遷移する。
						m_enemyState = enEnemyState_Damage;
					}

					//スキルを使うため。
					m_player->m_skillCharge += CHARGE_INCREASE_AMOUNT;
				}
				//非会心。
				else
				{
					m_enemyHP -= m_player->m_normalATK;

					if (m_enemyHP <= 0)
					{
						//HPが0になったら。
						m_enemyState = enEnemyState_Down;
					}
					else {
						//被ダメージステートに遷移する。
						m_enemyState = enEnemyState_Damage;
					}
					return;
				}
			}
		}
	}

	//-----------------------------------------
	//プレイヤーのスキル処理。
	//-----------------------------------------	

	{
		//プレイヤーのスキル用のコリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("amulet");
		//for文で配列を回す
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突する。
			if (collision->IsHit(m_charaCon))
			{
				//スキルのダメージ。
				m_player->m_skillATK = m_player->m_playerATK * m_player->m_skillMagnification;
				//敵のHPを減らす。
				m_enemyHP -= m_player->m_skillATK;

				//HPが0になったら。
				if (m_enemyHP < 0)
				{
					//ダウンステートに遷移する。
					m_enemyState = enEnemyState_Down;
				}

				else {
					//被ダメージステートに遷移する。
					m_enemyState = enEnemyState_Damage;
				}
				return;
			}
		}
	}

	//-----------------------------------------
	//月読の加護の判定処理。
	//-----------------------------------------

	{
		//プレイヤーの月読の加護用のコリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("Tukuyomi");
		//for文で配列を回す。
		for (auto collision : collisions)
		{
			//コリジョンとキャラが衝突する。
			if (collision->IsHit(m_charaCon))
			{
				//月読の加護のダメージ。
				m_player->m_tukuyomiATK = m_player->m_playerATK * m_player->m_TukuyomiMagnification;
				//敵のHPを減らす。
				m_enemyHP -= m_player->m_tukuyomiATK;

				//HPが0になったら。
				if (m_enemyHP < 0)
				{
					//ダウンステートに遷移する。
					m_enemyState = enEnemyState_Down;
				}

				else
				{
					//被ダメージステートに遷移する。
					m_enemyState = enEnemyState_Damage;
				}
				return;
			}
		}
	}

	//-----------------------------------------
	//しめ縄の判定処理。
	//-----------------------------------------

	{
		//プレイヤーのしめ縄用のコリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("Shimenawa");
		//for文で配列を回す。
		for (auto collision : collisions)
		{
			//コリジョンとキャラが衝突する。
			if (collision->IsHit(m_charaCon))
			{
				//停止させる準備。
				if (!m_isStopped)
				{
					m_isStopped = true;
					//動きを止める。
					m_moveSpeed = m_stopMove;
					//アニメーションも止める。
					m_enemyState = enEnemyState_Idle;
					//時間をリセット。
					m_stopTimer = 5.0f;
				}
			}
			//停止中の処理。
			else if (m_isStopped)
			{
				m_stopTimer -= g_gameTime->GetFrameDeltaTime();

				if (m_stopTimer <= 0.0f)
				{
					m_isStopped = false;
				}
			}
		}
	}

	//-----------------------------------------
	//本殿に接触したらゲームオーバーする処理。
	//-----------------------------------------

	//本殿に触れたらゲームオーバー。
	const auto& collisions = g_collisionObjectManager->FindMatchForwardNameCollisionObjects("gameover_collision");
	//コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//コリジョンとキャラが衝突したら。
		if (collision->IsHit(m_charaCon))
		{
			m_gameCamera->m_isGameOver = true;
			//消滅時EnemyUIのポインタを切断するためのフラグ
			m_isDeadFlag = true;
			DeleteGO(this);
			break;
		}
	}

}

const bool AnnoyingEnemy::SearchPlayer()const
{
	//プレイヤーとの方向ベクトルを取得。
	Vector3 diff = m_player->GetPosition() - m_position;

	//対象に近くなったら。
	if (diff.LengthSq() <= 700.0f * 700.0f)
	{
		//エネミーからプレイヤーに向かうベクトルを正規化する。
		diff.Normalize();
		//内積(cos0)を調べる。
		float cos = m_forward.Dot(diff);
		//内積(cos0)から角度を求める。
		float angle = acosf(cos);
		//角度を(0)が120度より小さければ。
		if (angle <= (Math::PI / 360.0f) * 360.0f)
		{
			//プレイヤーを見つけられた。
			return true;
		}

	}
	return false;
}

const bool AnnoyingEnemy::SearchHonden()const
{
	Vector3 diff = m_ringBell->GetPosition() - m_position;
	//対象に向かう
	if (diff.LengthSq() <= 10000 * 10000)
	{
		//エネミーから本殿に向かうベクトルを正規化する
		diff.Normalize();
		//内積(cos0)を調べる
		float cos = m_forward.Dot(diff);
		//内積から角度を求める
		float angle = acosf(cos);
		if (angle <= (Math::PI / 360.0f) * 360.0f)
		{
			return true;
		}
		return false;

	}
}

void AnnoyingEnemy::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら。
	if (m_idleTimer >= 0.9f)
	{
		//他のステートに遷移する。
		ProcessCommonStateTransition();
	}
}

void AnnoyingEnemy::ProcessChaseStateTransition()
{
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら。
	if (m_chaseTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
}

void AnnoyingEnemy::ProcessHondenStateTransition()
{
	m_mainTimer += g_gameTime->GetFrameDeltaTime();
	//本殿に向かう時間がある程度経過したら。
	if (m_mainTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
}

void AnnoyingEnemy::ProcessExplodeStateTransition()
{
	//ダウンステートなら、何もしない。
	if (m_enemyState ==!enEnemyState_Down)
	{
		return;
	}

	if (!m_hasExploded)
	{
		MakeExplosion();
		m_hasExploded = true;
		m_isDeadFlag = true;
		m_enemyHP = 0; 
	}
    
	m_explodeTimer += g_gameTime->GetFrameDeltaTime();
	if (m_explodeTimer > 3.0f) //演出後に消える
	{
		m_game->m_totalCount--;
		DeleteGO(this);
	}
}

void AnnoyingEnemy::ProcessDamageStateTransition()
{
	//攻撃されたら距離関係なしに退散させる。
	m_enemyState = enEnemyState_Chase;
	Vector3 diff = m_player->GetPosition() - m_position;
	diff.Normalize();
	//移動速度を設定する。
	m_moveSpeed = diff * 10.0f;
}

void AnnoyingEnemy::ProcessDownStateTransition()
{
	/*if (m_enemyState != enEnemyState_Explode)
	{
		return;
	}*/

	m_deathEffectTimer += g_gameTime->GetFrameDeltaTime();

	if (!m_isDeadFlag)
	{
		DeathEffect();
		m_isDeadFlag = true;
	}

	if (m_deathEffectTimer >= 1.0f)
	{
		//Gameのインスタンスアドレスを検索
		m_game->m_totalCount--;
		DeleteGO(this);
	}
}

void AnnoyingEnemy::ProcessCommonStateTransition()
{
	//各タイマーを初期化。
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	m_explodeTimer = 0.0f;


	if (SearchHonden() == true)
	{
		//プレイヤーを見つけたら。
		if (SearchPlayer() == true)
		{
			Vector3 diff = m_player->GetPosition() - m_position;
			//ベクトルを正規化する。
			diff.Normalize();
			//移動速度計算する。
			m_moveSpeed = diff * 300.0f;
			//攻撃できをる距離なら。
			if (IsCanAttack() == true)
			{
				int ram = rand() % 100;
				if (ram > 20)
				{
					m_enemyState = enEnemyState_Explode;
					/*m_hasExploded == true;*/
					return;

				}
				else
				{
					m_enemyState = enEnemyState_Chase;
				}
			}
			else
			{
				m_enemyState = enEnemyState_Chase;
			}
		}
		else
		{
			Vector3 diff = m_ringBell->GetPosition() - m_position;
			diff.Normalize();
			m_moveSpeed = diff * 300.0f;
			m_enemyState = enEnemyState_Main;
			return;
		}
	}
}

void AnnoyingEnemy::ManageState()
{
	switch (m_enemyState)
	{
		//何もしない。
	case enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
		//追跡処理。
	case enEnemyState_Chase:
		ProcessChaseStateTransition();
		break;
	case enEnemyState_Main:
		ProcessHondenStateTransition();
		break;
		//自爆処理
	case enEnemyState_Explode:
		ProcessExplodeStateTransition();
		break;
		//ダメージを受けった時の処理。
	case enEnemyState_Damage:
		ProcessDamageStateTransition();
		break;
		//ダウン処理。
	case enEnemyState_Down:
		ProcessDownStateTransition();
		break;
		//何もしない。
	default:
		break;
	}
}

void AnnoyingEnemy::PlayAnimation()
{

}

//アニメーションイベントを受け取った際に呼び出される関数。
void AnnoyingEnemy::OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	
}

const bool AnnoyingEnemy::IsCanAttack()const
{
	Vector3 diff = m_player->GetPosition() - m_position;

	//エネミーとプレイヤーの距離が近かったら
	if (diff.LengthSq() <= 150.0f * 150.0f)
	{
		
		return true;
	}
	return false;
}

void AnnoyingEnemy::Render(RenderContext& rc)
{
	if (m_hasExploded == false){
		m_modelRender.Draw(rc);
	}
}