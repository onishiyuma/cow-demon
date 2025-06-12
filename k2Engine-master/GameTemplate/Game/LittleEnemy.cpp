#include "stdafx.h"
#include "LittleEnemy.h"
#include "Player.h"
#include "Enemy.h"
#include "Poison.h"
#include "Game.h"
#include "GameOver.h"
#include "GameCamera.h"
#include "RingBell.h"
#include "LanternAttack.h"
//#include"collision/CollisionObject.h"
#include<time.h>
#include<stdlib.h>

namespace
{
	//チャージ増加量。
	int CHARGE_INCREASE_AMOUNT = 10;
}

LittleEnemy::LittleEnemy()
{

}

LittleEnemy::~LittleEnemy()
{
	if (m_effectEmitter) {
		m_effectEmitter->Stop();
		DeleteGO(m_effectEmitter);
		m_effectEmitter = nullptr;
	}
}

bool LittleEnemy::Start()
{  
	//アニメーションの読み込みとループ設定。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/littleEnemy/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);

	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/littleEnemy/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);

	m_animationClips[enAnimationClip_Run].Load("Assets/animData/littleEnemy/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	m_animationClips[enAnimationClip_Poison].Load("Assets/animData/littleEnemy/poison.tka");
	m_animationClips[enAnimationClip_Poison].SetLoopFlag(true);

	m_animationClips[enAnimationClip_Damage].Load("Assets/animData/littleEnemy/receivedamage.tka");
	m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/littleEnemy/down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);

	//モデルの初期化。
	m_modelRender.Init("Assets/modelData/LittleEnemy/enemy.tkm", m_animationClips, enAnimationClip_Num);
	EffectEngine::GetInstance()->ResistEffect(8, u"Assets/effect/EnemyEffects/Usioni_Little_Down/Little_Down.efk");
	//座標を設定。
	m_modelRender.SetPosition(m_position);
	//回転を設定。
	m_modelRender.SetRotation(m_rotation);

	//キャラコンを初期化。
	m_charaCon.Init(
		50.0f,
		50.0f,
		m_position,
		enCollisionAttr_Enemy
	);

	//大きさを設定。
	Vector3  scale(100.0f, 100.0f, 100.0f);
	SetScale(scale);
	//HPを設定。
	
	//アニメーションイベントの登録。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OneAnimationEvent(clipName, eventName);
		});

	//各種インスタンスアドレスを検索。
	m_game = FindGO<Game>("Game");
	m_player = FindGO<Player>("player");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_ringBell = FindGO<RingBell>("ringbell");
	m_lanternAttack = FindGO<LanternAttack>("lanternAttack");
	//乱数を初期化。
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	m_enemyHP = 10;

	return true;
}

void LittleEnemy::Update()
{
	//追跡処理。
	Chase();
	//本殿追跡処理
	IsHonden();
	//回転処理。
	Rotation();
	//コリジョン
	Collision();
	//アニメーション更新。
	PlayAnimation();
	//状態管理。
	ManageState();
	//モデルレンダーの更新。
	m_modelRender.Update();
}

void LittleEnemy::Rotation()
{
	//移動速度がなければ何もしない。
	if (fabsf(m_moveSpeed.x) < 0.001f&& fabsf(m_moveSpeed.z) < 0.001f) 
	{
		return;
	}

	//進行方向に回転をかける。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);

	//回転を設定。
	m_modelRender.SetRotation(m_rotation);

	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void LittleEnemy::Chase()
{
	//追跡ステートでなければ何もしない。
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}

	//重力を追加。
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//キャラコンを使って移動。
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	if (m_charaCon.IsOnGround()) {
		//y方向には移動させない。
		m_moveSpeed.y = 0.0f;
	}
	//重力を追加。
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//モデルの表示位置を更新。
	Vector3 modelPosition = m_position;
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void LittleEnemy::IsHonden()
{
	//追跡ステートでないなら、追跡処理はしない
	if (m_enemyState != enEnemyState_Honden)
	{
		return;
	}
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//地面についた
		m_moveSpeed.y = 0.0f;
	}
    m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	
	Vector3 modelPosition = m_position;
	modelPosition.y += 2.5f;
	m_modelRender.SetPosition(modelPosition);
}

void LittleEnemy::Collision()
{
	//ダメーいを受けている場合は何もしない。
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
					else {
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
		//for文で配列を回す。
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
	//		if (m_lanternAttack->m_isLight == true) {
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
			m_gameCamera->m_isGameOver = true;
			//消滅時EnemyUIのポインタを切断するためのフラグ
			m_isDeadFlag = true;
			DeleteGO(this);
			break;
		}
	}
}

const bool LittleEnemy::SearchPlayer()const
{
	//プレイヤーとのベクトルを求める。
	Vector3 diff = m_player->GetPosition() - m_position;

	//エネミーとプレイヤーの距離が近かったら。
	if (diff.LengthSq() <= 1000.0f * 1000.0f)
	{
		//正規化
		diff.Normalize();
		//内積を求める。
		float cos = m_forward.Dot(diff);
		//内積から角度を求める。
		float angle = acosf(cos);
		//角度が120度よりも小さければ。
		if (angle <= (Math::PI / 360.0f) * 360.0f)
		{
			//プレイヤーを見つけた。
			return true;
		}
	}
	return false;
}

const bool LittleEnemy::SearchMain()const
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

void LittleEnemy::MakePoison()
{
	//毒ブレスのオブジェクトを作成。
	Poison* poison = NewGO<Poison>(0);
	Vector3 PoisonPosition = m_position;
	//座標を少し上に設定。
	PoisonPosition.y += 50.0f;
	//座標を設定。
	poison->SetPosition(PoisonPosition);
	//回転を設定。
	poison->SetRotation(m_rotation);
	//射手を設定する。
	poison->SetEnEnemy(Poison::enPoison_LittleEnemy);
}

void LittleEnemy::DeathEffect()
{
	//エフェクトの発生位置
	Vector3 m_effectPosition = m_position;
	m_effectPosition.y += 50.0f;

	//エフェクトの生成
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(8);//番号はRegistの登録番号
	m_effectEmitter->SetPosition(m_effectPosition);
	m_effectEmitter->SetScale(Vector3(30.0f, 30.0f, 30.0f));//大きさは調整
	m_effectEmitter->Play();//エフェクトの再生
}

void LittleEnemy::ProcessIdleStateTransition()
{
	//待機時間を加算。
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら
	if (m_idleTimer >= 0.9f)
	{
		//他のステートに遷移する。
		ProcessCommonStateTransition();
	}
}
void LittleEnemy::ProcessChaseStateTransition()
{
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら。
	if (m_chaseTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
		return;
	}
}

void LittleEnemy::ProcessPoisonAttackStateTransition()
{
	//被ダメージアニメーションの再生が終わったら。
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		ProcessCommonStateTransition();
		return;
	}
	m_poisonAttackCoolDown += g_gameTime->GetFrameDeltaTime();
	//追跡時間がある程度経過したら。
	if (m_poisonAttackCoolDown >= 1.0f)
	{
		ProcessCommonStateTransition();
		return;
	}
}	

void LittleEnemy::ProcessHondenStateTransition()
{
	//攻撃ができる距離になったら
	if (IsCanAttack() == true)
	{
		//他のステートに遷移する
		ProcessCommonStateTransition();
		return;
	}

	m_hondenTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時移行がある程度経過したら
	if (m_hondenTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
	}
}

void LittleEnemy::ProcessDamageStateTransition()
{
	//被ダメージアニメーションの再生が終わったら。
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		////攻撃されたら距離関係なしに退散させる。
		//m_enemyState = enEnemyState_Chase;
		//Vector3 diff = m_player->GetPosition() - m_position;
		//diff.Normalize();
		////移動速度を設定する。
		//m_moveSpeed = diff * 10.0f;
		ProcessCommonStateTransition();
	}
}

void LittleEnemy::ProcessDownStateTransition()
{
	m_deathEffectTimer += g_gameTime->GetFrameDeltaTime();

	if (!m_isDeadFlag)
	{
		DeathEffect();
		m_isDeadFlag = true;

		if (m_game == nullptr) {
			m_game = FindGO<Game>("game");
		}

		// null チェック
		if (m_game != nullptr) {
			m_game->m_totalCount--;
		}
	}
	
	if (m_deathEffectTimer >= 1.0f)
	{
		//Gameのインスタンスアドレスを検索
		m_game->m_totalCount--;
		DeleteGO(this);
	}
	
}

void LittleEnemy::ProcessCommonStateTransition()
{
	//各種タイマーをリセット。
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	m_poisonAttackCoolDown = 0.0f;
	m_hondenTimer = 0.0f;

	if (SearchMain() == true) {
		//プレイヤーとの距離を求める。
		if (SearchPlayer() == true)
		{
			Vector3 diff = m_player->GetPosition() - m_position;
			//正規化。
			diff.Normalize();
			//移動速度を計算する。
			m_moveSpeed = diff * 80.0f;
			//攻撃できる距離なら。
			if (IsCanAttack() == true)
			{
				int ram = rand() % 100;
				if (ram > 80)
				{
					m_enemyState = enEnemyState_Poison;
					return;
				}

				else
				{
					m_enemyState = enEnemyState_Chase;
					return;
				}
			}
			/*else
			{
				m_enemyState = enEnemyState_Idle;
				return;
			}*/

		}
		else
		{
			Vector3 diff = m_ringBell->GetPosition() - m_position;
			diff.Normalize();
			m_moveSpeed = diff * 80.0f;

			m_enemyState = enEnemyState_Honden;
			return;
		}
	}
}


void LittleEnemy::ManageState()
{
	switch (m_enemyState)
	{
		//待機状態
	case enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
		//追跡状態
	case enEnemyState_Chase:
		ProcessChaseStateTransition();
		break;
		//本殿追従状態
	case enEnemyState_Honden:
		ProcessHondenStateTransition();
		break;
		//遠距離攻撃状態
	case enEnemyState_Poison:
		ProcessPoisonAttackStateTransition();
		break;
		//被ダメージ状態
	case enEnemyState_Damage:
		ProcessDamageStateTransition();
		break;
		//ダウン状態
	case enEnemyState_Down:
		ProcessDownStateTransition();
		break;
	default:
		break;
	}
}

void LittleEnemy::PlayAnimation()
{
	//アニメーションの再生速度を設定。
	m_modelRender.SetAnimationSpeed(1.0f);
	switch (m_enemyState)
	{
	case enEnemyState_Idle:
		//待機状態
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.5f);
		break;
	case enEnemyState_Chase:
		//追跡状態
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
		//本殿追従状態
	case enEnemyState_Honden:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run,0.1f);
		break;
	case enEnemyState_Poison:
		//遠距離攻撃状態
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Poison, 0.1f);
		break;
		//被ダメージ状態
	case enEnemyState_Damage:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Damage, 0.1f);
		break;
	case enEnemyState_Down:
		//ダウン状態
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
	//アニメーションイベントの処理。
	if (wcscmp(eventName, L"magic_attack") == 0) {
		MakePoison();
	}
}

const bool LittleEnemy::IsCanAttack()const
{
	//プレイヤーとの距離を求める。
	Vector3 diff = m_player->GetPosition() - m_position;

	//プレイヤーとの距離が近かったら。
	if (diff.LengthSq() <= 700.0f * 700.0f)
	{
		//攻撃。
		return true;
	}
	//何もしない。
	return false;
}

void LittleEnemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}