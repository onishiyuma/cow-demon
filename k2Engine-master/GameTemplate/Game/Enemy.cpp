
#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "GameOver.h"
#include "RingBell.h"
#include "BackGround.h"
#include "collision/CollisionObject.h"
#include "GameCamera.h"
#include <time.h>
#include <stdlib.h>

//定数を設定する場所。
namespace
{
	int CHARGE_INCREASE_AMOUNT = 10;//チャージ増加量。
}

bool Enemy::Start()
{
	//アニメーションクリップの読み込み。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/enemy/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/enemy/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/enemy/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Attack].Load("Assets/animData/enemy/attack.tka");
	m_animationClips[enAnimationClip_Attack].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Damage].Load("Assets/animData/enemy/receivedamage.tka");
	m_animationClips[enAnimationClip_Damage].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/enemy/down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);

	//モデルとアニメーションの初期化。
	m_modelRender.Init("Assets/modelData/enemy/enemy.tkm", m_animationClips, enAnimationClip_Num);
	EffectEngine::GetInstance()->ResistEffect(6,u"Assets/effect/EnemyEffects/Usioni_Down/Usioni_Down.efk");
	////座標を更新する。
	m_modelRender.SetPosition(m_farstPosition);
	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	
	//キャラコンの初期化。
	m_charaCon.Init(
		50.0f,
		50.0f,
		m_position
	);

	//ボーンのIDを取得する。
	m_FangBoneId = m_modelRender.FindBoneID(L"Fang");

	//アニメーションイベント用の関数を設定する。
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OneAnimationEvent(clipName, eventName);
		});
	//インスタンスアドレスを検索する。
	m_player = FindGO<Player>("player");
	m_ringBell = FindGO<RingBell>("ringbell");
	m_game = FindGO<Game>("game");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	
	
	//乱数を初期化する。
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

	return true;
}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	if (m_effectEmitter) {
		m_effectEmitter->Stop();
		DeleteGO(m_effectEmitter);
		m_effectEmitter = nullptr;
	}
}

void Enemy::Update()
{
	//追跡処理。
	Chase();
	//本殿追跡処理。
	IsHonden();
	//回転処理。
	Rotation();
	//当たり判定。
	Collision();
	//攻撃処理。
	Attack();
	//ステートの遷移処理。
	ManageState();
	//アニメーションの再生。
	PlayAnimation();
	//モデルの更新。
	m_modelRender.Update();
}

void Enemy::Rotation()
{
	//移動がないなら回転を更新しない。
	if (fabsf(m_moveSpeed.x) < 0.001f &&fabsf(m_moveSpeed.z) < 0.001f)
	{
		return;
	}
	//Y軸回転角を計算。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);

	//プレイヤーの前ベクトルを計算する。
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void Enemy::Chase()
{
	//追跡ステートでないなら、追跡処理はしない。
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}
	
	//キャラコンを使って移動。
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	//地面についていたらY方向の速度をリセット。
	if (m_charaCon.IsOnGround()) 
	{
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}
    //重力を追加。
	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//座標をセット。
	Vector3 modelPosition = m_position;
	m_modelRender.SetPosition(modelPosition);
}

void Enemy::IsHonden()
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


void Enemy::Collision()
{
	//被ダメージ、あるいはダウンステートの時は当たり判定処理はしない。
	if (m_enemyState == enEnemyState_Damage ||m_enemyState == enEnemyState_Down)
	{
		return;
	}

	//-----------------------------------------
	//プレイヤーの攻撃判定処理。
	//-----------------------------------------

	//プレイヤー攻撃用のコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("purification");
	//コリジョンの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_charaCon))
		{
			//スキルを使うための。
			m_player->m_skillCharge += CHARGE_INCREASE_AMOUNT;

			//会心の設定。
			int ram = rand() % 100;
			if (ram < m_player->m_criticalRate)
			{
				m_enemyHP -= m_player->m_criticalATK;

				if (m_enemyHP <= 0)
				{

					m_enemyHP -= m_player->m_criticalATK;

					if (m_enemyHP <= 0)
					{
						//HPが0になったら。
						m_enemyState = enEnemyState_Down;
					}
					else {
						//被ダメージステートに遷移する
						m_enemyState = enEnemyState_Damage;
					}

					//スキルを使うための。
					m_player->m_skillCharge += CHARGE_INCREASE_AMOUNT;

					//HPが0になったら。
					m_enemyState = enEnemyState_Down;

				}
				else {
					//被ダメージステートに遷移する
					m_enemyState = enEnemyState_Damage;
				}
			}
			//非会心。
			else
			{
				m_enemyHP -= m_player->m_normalATK;

				if (m_enemyHP <= 0)
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

	//-----------------------------------------
	//本殿に接触したらゲームオーバーする処理。
	//-----------------------------------------
	{
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
				return;
			}
		}
	}
}

void Enemy::Attack()
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

const bool Enemy::SearchPlayer()const
{
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
		if (angle <= (Math::PI / 180.0f) * 120.0f)
		{
			//プレイヤーを見つけられた。
			return true;
		}
	}
	return false;
}

const bool Enemy::SearchMain()const
{
	Vector3 diff2 = m_ringBell->GetPosition() - m_position;
	//対象に向かう。
	if (diff2.LengthSq() <= 10000 * 10000)
	{
		//エネミーから本殿に向かうベクトルを正規化する。
		diff2.Normalize();
		//内積(cos0)を調べる。
		float cos = m_forward.Dot(diff2);
		//内積から角度を求める。
		float angle = acosf(cos);
		if (angle <= (Math::PI / 360.0f) * 360.0f)
		{
			return true;
		}
		return false;

	}
}

void Enemy::MakeAttackCollision()
{
	//攻撃判定用のコリジョンオブジェクトを作成する。
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	collisionPosition += m_forward * 15.0f;
	collisionObject->CreateSphere(collisionPosition,
		Quaternion::Identity,
		70.0f
	);
	collisionObject->SetName("enemy_attack");
}

void Enemy::DeathEffect()
{
	//エフェクトの発生位置
	Vector3 m_effectPosition = m_position;
	m_effectPosition.y += 50.0f;

	//エフェクトの生成
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(6);//番号はRegistの登録番号
	m_effectEmitter->SetPosition(m_effectPosition);
	m_effectEmitter->SetScale(Vector3(30.0f, 30.0f, 30.0f));//大きさは調整
	m_effectEmitter->Play();//エフェクトの再生
}


void Enemy::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら。
	if (m_idleTimer >= 0.9f)
	{
		//他のステートに遷移する。
		ProcessCommonStateTransition();
	}
}

void Enemy::ProcessChaseStateTransition()
{
	//攻撃ができる距離になったら。
	if (IsCanAttack() == true)
	{
		//他のステートに遷移する。
		ProcessCommonStateTransition();
		return;
	}
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時移行がある程度経過したら。
	if (m_chaseTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
	}
}

void Enemy::ProcessAttackStateTransition()
{
	//アニメーション再生が終わっていたら。
	if (m_modelRender.IsPlayingAnimation() == false) 
	{
		ProcessCommonStateTransition();
	}
}

void Enemy::ProcessDamageStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		//プレイヤーへの方向を求めて移動速度をセット。
		m_enemyState = enEnemyState_Chase;
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		m_moveSpeed = diff * 250.0f;
	}
	/*ProcessCommonStateTransition();*/
}

void Enemy::ProcessDownStateTransition()
{
	if (!m_isDeadFlag)
	{
		//死亡エフェクトを発生させる。
		DeathEffect();
		m_isDeadFlag = true;
	}

	if (m_modelRender.IsPlayingAnimation()==false) {
       
		Game* game = FindGO<Game>("game");
		//自身を削除する
		DeleteGO(this);
	}
}

void Enemy::ProcessMainStateTransition()
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

void Enemy::ProcessCommonStateTransition()
{
	//各タイマーを初期化。
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;
	m_hondenTimer = 0.0f;


	if (SearchMain() == true)
	{   //プレイヤーを見つけたら。
		if (SearchPlayer() == true) {
			Vector3 diff = m_player->GetPosition() - m_position;
			//ベクトルを正規化する。
			diff.Normalize();
			//移動速度を設定する。
			m_moveSpeed = diff * 150.0f;
			//攻撃できる距離なら。
			int ram = rand() % 100;
			if (IsCanAttack() == true)
			{
				if (ram > 70)
				{


					m_enemyState = enEnemyState_Attack;
					m_isUnderAttack = false;
					return;
				}

				else
				{
					m_enemyState = enEnemyState_Chase;
				}

			}
			//攻撃できない距離なら。
			else
			{
				m_enemyState = enEnemyState_Chase;
				return;
			}
		}
		else {
			Vector3 diff = m_ringBell->GetPosition() - m_position;
			diff.Normalize();
			m_moveSpeed = diff * 150.0f;

			m_enemyState = enEnemyState_Honden;
			return;
		}

	}
}

void Enemy::ManageState()
{
	switch (m_enemyState)
	{
		//待機ステート。
	case Enemy::enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
	case Enemy::enEnemyState_Honden:
		ProcessMainStateTransition();
		break;
		//追跡ステート。
	case  Enemy::enEnemyState_Chase:
		ProcessChaseStateTransition();
		break;
		//攻撃ステート。
	case Enemy::enEnemyState_Attack:
		ProcessAttackStateTransition();
		break;
		//被ダメージステート。
	case Enemy::enEnemyState_Damage:
		ProcessDamageStateTransition();
		break;
		//死亡ステート。
	case Enemy::enEnemyState_Down:
		ProcessDownStateTransition();
		break;
	default:
		break;
	}
}

void Enemy::PlayAnimation()
{
	//アニメーションの速度の初期値。
	m_modelRender.SetAnimationSpeed(1.0f);
	//再生するアニメーションクリップ。
	switch (m_enemyState)
	{
	case Enemy::enEnemyState_Idle:
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.1f);
		break;
	case Enemy::enEnemyState_Honden:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
	case Enemy::enEnemyState_Chase:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
	case Enemy::enEnemyState_Attack:
		m_modelRender.SetAnimationSpeed(1.6f);
		m_modelRender.PlayAnimation(enAnimationClip_Attack, 0.1f);
		break;
	case Enemy::enEnemyState_Damage:
		m_modelRender.SetAnimationSpeed(1.3f);
		m_modelRender.PlayAnimation(enAnimationClip_Damage, 0.1f);
		break;
	case Enemy::enEnemyState_Down:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Down, 0.1f);
		break;
	default:
		break;
	}
}

void Enemy::OneAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"attack_start") == 0) {
		//攻撃中判定をtrueにする。
		m_isUnderAttack = true;
	}
	else if (wcscmp(eventName, L"attack_end") == 0) {
		m_isUnderAttack = false;
	}
}

const bool Enemy::IsCanAttack() const
{
	Vector3 diff = m_player->GetPosition() - m_position;
	//エネミーとプレイヤーの距離が近かったら。
	if (diff.LengthSq() <= 100.0f * 100.0f)
	{
		//攻撃可。
		return true;
	}
	//攻撃不可。
	return false;
}

void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}