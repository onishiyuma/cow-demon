#include "stdafx.h"
#include "BossEnemy.h"
#include "Player.h"
#include "EnemyUI.h"
#include "Poison.h"
#include "RingBell.h"
#include "EnemyBase.h"
#include "Game.h"
#include "GameOver.h"
#include "GameCamera.h"
#include "LanternAttack.h"
#include "sound/SoundEngine.h"
#include <time.h>
#include<stdlib.h>

namespace
{
	//チャージ増加量。
	const int CHARGE_INCREASE_AMOUNT = 10;
}

BossEnemy::BossEnemy()
{
}

BossEnemy::~BossEnemy()
{
	/*if (m_effectEmitter) {
		m_effectEmitter->Stop();
		DeleteGO(m_effectEmitter);
		m_effectEmitter = nullptr;
	}*/
}

bool BossEnemy::Start()
{
	//待機。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/Boss/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	//走り。
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/Boss/Move.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	//近接攻撃
	m_animationClips[enAnimationClip_Attack].Load("Assets/animData/Boss/Attack.tka");
	m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	//毒ブレス。
	m_animationClips[enAnimationClip_Poison].Load("Assets/animData/Boss/Poison.tka");
	m_animationClips[enAnimationClip_Poison].SetLoopFlag(false);
	//ダメージ。
	m_animationClips[enAnimationClip_Damage].Load("Assets/animData/Boss/Damage.tka");
	m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	//ダウン。
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/Boss/Down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);
	//モデルを初期化。
	m_modelRender.Init("Assets/modelData/Boss/Boss.tkm", m_animationClips, enAnimationClip_Num);

	//座標を更新する。
	m_modelRender.SetPosition(m_position);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	//キャラコンの初期化。
	m_charaCon.Init(
		120.0f,
		120.0f,
		m_position,
		enCollisionAttr_Enemy
	);

	//ボーンのIDを取得する。
	m_BossFangBoneID = m_modelRender.FindBoneID(L"BossFang");
	//大きさを設定。
	Vector3 scale(100.0f, 100.0f, 1.00f);
	SetScale(scale);
	//HPを設定する。
	
	//アニメーションイベント用の関数を設定する。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OneAnimationEvent(clipName, eventName);
		});

	//エフェクトを読み込む
	EffectEngine::GetInstance()->ResistEffect(20,u"Assets/effect/EnemyEffects/Usioni_Boss_Down/Boss_Down.efk");

	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_ringBell = FindGO<RingBell>("ringbell");
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack");

	//乱数を初期化する。
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

void BossEnemy::Update()
{
	//Game.cppで終了時のフラグがtrueになったら自分を削除するフラグをtrueにする
	//m_isDeadFlagはEnemyUIを切断するためのフラグ
	//m_isDeadはEnemyManagerに自身を削除してもらうためのフラグ 

 if (m_game->m_isEndGame == true)
	{
		m_isDeadFlag = true;
		m_isDead = true;
	}
   //m_isDeadがtrueの場合は何もさせないためのコード
 if (m_isDead == true)return;
	//本殿追跡処理
	IsHonden();
	//追跡処理。
	Chase();
	//回転処理。
	Rotation();
	//当たり判定。
	Collision();
    //攻撃
	Attack();
	//アニメーションの再生。
	PlayAnimation();
	//ステート管理。
	ManageState();

	//モデルの更新。
	m_modelRender.Update();

	

}

void BossEnemy::Rotation()
{
	//移動処理が小さい場合はスキップする。
	if (fabsf(m_moveSpeed.x) < 0.001f&&fabsf(m_moveSpeed.z)<0.001f)
	{
		return;
	}
	//移動方向ベクトルから回転角度を算出。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//回転をセット。
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//プレイヤーの前ベクトルを計算する。
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void BossEnemy::Chase()
{
	//追跡ステートでないなら追跡しない。
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}
	//キャラコンで移動させる。
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	
	//地面についているか。
	if (m_charaCon.IsOnGround())
	{
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}
	//重力を追加。
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//モデルの表示位置設定。
	Vector3 modelPositon = m_position;
	modelPositon.y += 2.5f;
	m_modelRender.SetPosition(modelPositon);
}

void BossEnemy::IsHonden()
{
	//追跡ステートでないなら、追跡処理はしない。
	if (m_enemyState != enEnemyState_Honden)
	{
		return;
	}
	
	//キャラコンを使って移動。
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	//地面についていたらY方向の速度をリセット。
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}
    //重力を追加。
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//座標をセット。
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void BossEnemy::Attack()
{
	//攻撃処理要ステートが出ないなら処理はしない。
	if (m_enemyState != enEnemyState_Attack)
	{
		return;
	}

	//攻撃中であれば。
	if (m_isUnderAttack == true)
	{
		//攻撃用のコリジョンを作成する。
		MakeAttackCollision();
	}
}

void BossEnemy::MakeAttackCollision()
{
	//攻撃判定用のコリジョンオブジェクトを作成する。
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	collisionPosition += m_forward * 15.0f;
	collisionObject->CreateSphere(collisionPosition,
		Quaternion::Identity,
		120.0f
	);
	collisionObject->SetName("Boss_enemy_attack");
}

void BossEnemy::Collision()
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
						//HPが0になったら。
						m_enemyState = enEnemyState_Down;
					}
					else 
					{
						//被ダメージステートに遷移する。
						m_enemyState = enEnemyState_Damage;
					}

					//スキルを使うためのチャージ加算。
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
					else 
					{
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
		//プレイヤーのスキル用のコリジョンを取得する
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("amulet");
		//for文で配列を回す
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突する
			if (collision->IsHit(m_charaCon))
			{
				//スキルのダメージ。
				m_player->m_skillATK = m_player->m_playerATK * m_player->m_skillMagnification;
				
				//敵のHPを減らす。
				m_enemyHP -= m_player->m_skillATK;

				//HPが0になったら
				if (m_enemyHP <= 0)
				{
					//ダウンステートに遷移する
					m_enemyState = enEnemyState_Down;
				}
				else 
				{
					//被ダメージステートに遷移する
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

				//HPが0になったら
				if (m_enemyHP <= 0)
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
				break;
			}
		}

		//停止中の処理。
		if (m_isStopped)
		{
			//動きを止める。
			m_moveSpeed = m_stopMove;
			//アニメーションも止める。
			m_enemyState = enEnemyState_Idle;
			m_stopTimer -= g_gameTime->GetFrameDeltaTime();

			if (m_stopTimer <= 0.0f)
			{
				m_isStopped = false;
			}
		}
	}

	//----------------------------------------
	//攻撃用灯籠の判定管理。
	//----------------------------------------
	//{
	//	float attackTimer = 0.0f;
	//	attackTimer += g_gameTime->GetFrameDeltaTime();

	//	Vector3 diff1 = m_game->m_lanternAttack1->m_position - m_position;
	//	Vector3 diff2 = m_game->m_lanternAttack2->m_position - m_position;
	//	Vector3 diff3 = m_game->m_lanternAttack3->m_position - m_position;

	//	//灯籠に火がともっている
	//	if (diff1.Length() >= 400.0f or diff2.Length() >= 400.0f or diff3.Length() >= 400.0f) {
	//		if (m_game->m_lanternAttack1->m_isLight == true or m_game->m_lanternAttack1->m_isLight == true or m_game->m_lanternAttack1->m_isLight == true) {
	//			if (attackTimer >= 1.0f) {

	//				m_enemyHP -= 5.0f;

	//				//HPが0になったら。
	//				if (m_enemyHP < 0)
	//				{
	//					//ダウンステートに遷移する。
	//					m_enemyState = enEnemyState_Down;
	//				}

	//				else
	//				{
	//					//被ダメージステートに遷移する。
	//					m_enemyState = enEnemyState_Damage;
	//				}
	//				attackTimer = 0.0f;
	//				return;
	//			}
	//		}
	//	}


	//}

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
			m_game->m_isEndGame = true;
			//ゲームオーバーのフラグを立てる。
			m_gameCamera->m_isGameOver = true;
			////消滅時EnemyUIのポインタを切断するためのフラグ
			//m_isDeadFlag = true;
			////自身を削除。
			//m_isDead = true;
			break;
		}
	}
}

const bool BossEnemy::SearchPlayer()const
{
	//プレイヤーと自身の位置のベクトル。
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

const bool BossEnemy::SearchHonden()const
{
	//本殿と自身の位置のベクトル。
	Vector3 diff = m_ringBell->GetPosition() - m_position;
	//対象に近くなったら。
	if (diff.LengthSq() <= 10000.0f * 10000.0f)
	{
		//エネミーから本殿に向かうベクトルを正規化する。
		diff.Normalize();
		//内積(cos0)を調べる。
		float cos = m_forward.Dot(diff);
		//内積(cos0)から角度を求める。
		float angle = acosf(cos);
		//角度を(0)が120度より小さければ。
		if (angle <= (Math::PI / 360.0f) * 360.0f)
		{
			return true;
		}
	}
	return false;
}

void BossEnemy::MakePoison()
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
	poison->SetEnEnemy(Poison::enPoison_BossEnemy);
}

void BossEnemy::DeathEffect()
{
	if (m_effectEmitter) {
		m_effectEmitter->Stop();
		DeleteGO(m_effectEmitter);
		m_effectEmitter = nullptr;
	}

	//エフェクトの発生位置
	Vector3 m_effectPosition = m_position;
	m_effectPosition.y += 50.0f;

	//エフェクトの生成
    m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(20);//番号はRegistの登録番号
	m_effectEmitter->SetPosition(m_effectPosition);
	m_effectEmitter->SetScale(Vector3(30.0f, 30.0f, 30.0f));//大きさは調整
	m_effectEmitter->Play();//エフェクトの再生
}

void BossEnemy::ProcessIdleStateTransition()
{
	//待機時間を加算。
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら。
	if (m_idleTimer >= 0.8f)
	{
		//他のステートに遷移する。
		ProcessCommonStateTransition();
		return;
	}
}

void BossEnemy::ProcessChaseStateTransition()
{
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら。
	if (m_chaseTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
}

void BossEnemy::ProcessHondenStateTransition()
{
	
	m_hondenTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時移行がある程度経過したら
	if (m_hondenTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
	}
}

void BossEnemy::ProcessAttackStateTransition()
{
	// 攻撃可能範囲外なら即座に遷移
	if (!IsCanAttack()) {
		ProcessCommonStateTransition();
		return;
	}

	//アニメーション再生が終わっていたら。
	if (m_modelRender.IsPlayingAnimation() == false) {
		ProcessCommonStateTransition();
		return;
	}
}

void BossEnemy::ProcessPoisonAttackStateTransition()
{
	
	//遠距離攻撃アニメーションの再生が終わったら。
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		ProcessCommonStateTransition();
		return;
	}
	//追跡時間がある程度経過したら。
	if (m_poisonAttackCoolDown >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
	m_poisonAttackCoolDown += g_gameTime->GetFrameDeltaTime();

}

void BossEnemy::ProcessDamageStateTransition()
{
	//被ダメージアニメーションの再生が終わったら。
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//攻撃されたら距離関係なしに退散させる。
		m_enemyState = enEnemyState_Chase;
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		//移動速度を設定する.。
		m_moveSpeed = diff * 10.0f;
	}
}

void BossEnemy::ProcessDownStateTransition()
{
	
	if (!m_isDeadFlag) {
		DeathEffect();
		g_soundEngine->ResistWaveFileBank(94, "Assets/sound/dai.wav");
		m_die = NewGO<SoundSource>(94);
		m_die->Init(94);
		m_die->Play(false);
		m_isDeadFlag = true;
	}
	m_deathTimer += g_gameTime->GetFrameDeltaTime();
	if (m_deathTimer >= 1.0f)
	{
		if (m_effectEmitter)
		{
			m_effectEmitter->Stop();
			DeleteGO(m_effectEmitter);
			m_effectEmitter = nullptr;
		}
		m_isDead = true;
	}
}

void BossEnemy::ProcessCommonStateTransition()
{
	if (m_game->m_isEndGame) {
		return;
	}

	//各タイマーを初期化。
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	m_poisonAttackCoolDown = 0.0f;
	m_hondenTimer = 0.0f;


	if (SearchHonden() == true)
	{
		//プレイヤーを見つけたら。
		if (SearchPlayer() == true)
		{
			Vector3 diff = m_player->GetPosition() - m_position;
			//ベクトルを正規化する。
			diff.Normalize();
			//移動速度計算する。
			m_moveSpeed = diff * 100.0f;
			//攻撃できをる距離なら。
			if (IsCanAttack() == true)
			{
				int ram = rand() % 100;
				if (ram > 10)
				{

					m_enemyState = enEnemyState_Attack;
					m_isUnderAttack = false;
					return;
				}
				else
				{
					m_enemyState = enEnemyState_Chase;
					return;
				}
			}

			//攻撃できない距離なら
			else
			{
				int ram = rand() % 100;
				if (ram > 40)
				{
					//追跡ステートに遷移する
					m_enemyState = enEnemyState_Chase;
					return;
				}

				else
				{
					//遠距離攻撃ステートに遷移する。
					m_enemyState = enEnemyState_Poison;
					/*MakePoison();*/
					return;
				}
			}
		}
		else
		{
			Vector3 diff = m_ringBell->GetPosition() - m_position;
			diff.Normalize();
			m_moveSpeed = diff * 50.0f;

			m_enemyState = enEnemyState_Honden;
			return;
		}
	}
}

void BossEnemy::ManageState()
{
	switch (m_enemyState)
	{
		//待機中の処理。
	case enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
		//追跡処理。
	case enEnemyState_Chase:
		ProcessChaseStateTransition();
		break;
		//本殿追跡処理。
	case enEnemyState_Honden:
		ProcessHondenStateTransition();
		break;
		//攻撃処理。
	case enEnemyState_Attack:
		ProcessAttackStateTransition();
		break;
		//毒攻撃処理。
	case enEnemyState_Poison:
		ProcessPoisonAttackStateTransition();
		break;
		//ダメージを受けた時の処理。
	case enEnemyState_Damage:
		ProcessDamageStateTransition();
		break;
		//ダウン処理。
	case enEnemyState_Down:
		ProcessDownStateTransition();
		break;
	default:
		break;
	}
}

void BossEnemy::PlayAnimation()
{//アニメーションの再生速度の設定。
	m_modelRender.SetAnimationSpeed(1.5f);
	switch (m_enemyState)
	{
		//待機ステート
	case enEnemyState_Idle:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
		//追跡ステート
	case enEnemyState_Chase:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
	case enEnemyState_Honden:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
	case enEnemyState_Attack:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Attack,0.1f);
		break;
		//遠距離攻撃ステート
	case enEnemyState_Poison:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Poison, 0.1f);
		break;
		//被ダメージステート
	case enEnemyState_Damage:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Damage, 0.1f);
		break;
		//ダウンステート
	case enEnemyState_Down:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Down, 0.1f);
		break;
	default:
		break;
	}
}

void BossEnemy::OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"Boss_Start") == 0) {
		//攻撃中判定をtrueにする。
		m_isUnderAttack = true;
	}
	else if (wcscmp(eventName, L"Boss_End") == 0) {
		m_isUnderAttack = false;
	}

	if (wcscmp(eventName, L"Boss_Poison") == 0) {
		MakePoison();
	}
}

const bool BossEnemy::IsCanAttack()const
{
	//プレイヤーとの距離ベクトルを取得。
	Vector3 diff = m_player->GetPosition() - m_position;
	//エネミーとプレイヤーの距離が近かったら
	if (diff.LengthSq() <= 200.0f * 200.0f)
	{
		//攻撃可
		return true;
	}
	//攻撃不可
	return false;
}

void BossEnemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}