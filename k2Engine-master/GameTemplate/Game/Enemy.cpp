
#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"


#include"collision/CollisionObject.h"
#include<time.h>
#include<stdlib.h>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
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

	m_modelRender.Init("Assets/modelData/enemy/enemy.tkm", m_animationClips, enAnimationClip_Num);

	////座標を更新する
	//m_modelRender.SetPosition(m_position);
	//回転を設定する
	m_modelRender.SetRotation(m_rotation);
	////大きさを設定する
	//m_modelRender.SetScale(m_scale);
	m_charaCon.Init(
		20.0f,
		20.0f,
		m_position
	);

	//ボーンのIDを取得する
	m_FangBoneId = m_modelRender.FindBoneID(L"Fang");
	//Vector3  scale(1.0f, 1.0f, 1.0f);
	//SetScale(scale);
	//アニメーションイベント用の関数を設定する
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OneAnimationEvent(clipName, eventName);
		});
	m_player = FindGO<Player>("player");
	/*m_tou = FindGO<Tou>("tou");*/
	//乱数を初期化する
	srand((unsigned)time(NULL));
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
	return true;
}



void Enemy::Update()
{
	//追跡処理
	Chase();
	//本殿追跡処理
	/*Goal();*/
	//回転処理
	Rotation();
	//当たり判定
	Collision();
	//攻撃処理
	Attack();
	//ステートの遷移処理
	ManageState();
	//アニメーションの再生
	PlayAnimation();
	//モデルの更新
	m_modelRender.Update();
}

void Enemy::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f &&
		fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotationY(-angle);

	//回転を設定する
	m_modelRender.SetRotation(m_rotation);

	//プレイヤーの前ベクトルを計算する
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);

}

void Enemy::Chase()
{
	//追跡ステートでないなら、追跡処理はしない
	if (m_enemyState != enEnemyState_Chase)
	{
		return;
	}
	/*m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();*/
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_charaCon.IsOnGround()) {
		//地面についた
		m_moveSpeed.y = 0.0f;
	}
	Vector3 modelPosition = m_position;

	m_modelRender.SetPosition(modelPosition);
}

//void Enemy::Goal()
//{
//	//追跡ステートでないなら、追跡処理はしない
//	if (m_enemyState != enEnemyState_Goal)
//	{
//		return;
//	}
//	/*m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();*/
//	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
//	if (m_charaCon.IsOnGround()) {
//		//地面についた
//		m_moveSpeed.y = 0.0f;
//	}
//	Vector3 modelPosition = m_position;
//
//	m_modelRender.SetPosition(modelPosition);
//}


void Enemy::Collision()
{
	/*被ダメージ、あるいはダウンステートの時は
	当たり判定処理はしない*/
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
				m_hp -= 5;
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

	//プレイヤーのスキル用のコリジョンを取得する
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("amulet");
	//for文で配列を回す
	for (auto collision : collisions)
	{
		//コリジョンとキャラコンが衝突する
		if (collision->IsHit(m_charaCon))
		{
			m_hp -= 10;
			//HPが0になったら
			if (m_hp < 0)
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

void Enemy::Attack()
{
	//攻撃処理要ステートが出ないなら処理はしない
	if (m_enemyState != enEnemyState_Attack)
	{
		return;
	}

	//攻撃中であれば
	if (m_isUnderAttack == true)
	{
		//攻撃用のコリジョンを作成する
		MakeAttackCollision();
	}

}


const bool Enemy::SearchPlayer()const
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
		if (angle <= (Math::PI / 180.0f) * 120.0f)
		{
			//プレイヤーを見つけられた
			return true;
		}
		return false;
	}
}

//const bool Enemy::SearchGoal()const
//{
//	Vector3 diff = m_tou->GetPosition()-m_position;
//	//対象に向かう
//	if (diff.LengthSq() <= 10000*10000)
//	{
//		//エネミーから本殿に向かうベクトルを正規化する
//		diff.Normalize();
//		//内積(cos0)を調べる
//		float cos = m_forward.Dot(diff);
//		//内積から角度を求める
//		float angle = acosf(cos);
//		if (angle <= (Math::PI / 360.0f) * 360.0f)
//		{
//			return true;
//		}
//		return false;
//		
//	}
//}

void Enemy::MakeAttackCollision()
{
	//攻撃判定用のコリジョンオブジェクトを作成する
	auto collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	collisionPosition += m_forward * 15.0f;
	collisionObject->CreateSphere(collisionPosition,
		Quaternion::Identity,
		70.0f
	);
	collisionObject->SetName("enemy_attack");
	////近接攻撃のボーンワールド行列を取得する
	//Matrix matrix = m_modelRender.GetBone(m_FangBoneId)->GetWorldMatrix();
	////ボックス状のコリジョンを作成する
	//collisionObject->CreateBox(m_position, Quaternion::Identity, Vector3(50.0f, 50.0f, 50.0f));
	//collisionObject->SetWorldMatrix(matrix);
	//collisionObject->SetName("enemy_attack");
}

void Enemy::ProcessIdleStateTransition()
{
	m_idleTimer += g_gameTime->GetFrameDeltaTime();
	//待機時間がある程度経過したら
	if (m_idleTimer >= 0.9f)
	{
		//他のステートに遷移する
		ProcessCommonStateTransition();
	}
}



void Enemy::ProcessChaseStateTransition()
{
	//攻撃ができる距離になったら
	if (IsCanAttack() == true)
	{
		//他のステートに遷移する
		ProcessCommonStateTransition();
		return;
	}
	m_chaseTimer += g_gameTime->GetFrameDeltaTime();
	//追跡時移行がある程度経過したら
	if (m_chaseTimer >= 0.8f)
	{
		ProcessCommonStateTransition();
	}
}

void Enemy::ProcessAttackStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false) {
		ProcessCommonStateTransition();
	}
}

void Enemy::ProcessDamageStateTransition()
{
	if (m_modelRender.IsPlayingAnimation() == false)
	{
		m_enemyState = enEnemyState_Chase;
		Vector3 diff = m_player->GetPosition() - m_position;
		diff.Normalize();
		m_moveSpeed = diff * 250.0f;
	}
	ProcessCommonStateTransition();
}

void Enemy::ProcessDownStateTransition()
{
	if (m_enemyState == enEnemyState_Down) {
		Game* game = FindGO<Game>("game");
		//自身を削除する
		DeleteGO(this);
	}
}

//void Enemy::ProcessGoalStateTransition()
//{
//	if (SearchGoal() == false)
//	{
//		ProcessCommonStateTransition();
//	}
//}

void Enemy::ProcessCommonStateTransition()
{
	//各タイマーを初期化
	m_idleTimer = 0.0f;
	m_chaseTimer = 0.0f;

	//エネミーからプレイヤーに向かうベクトルを計算する
	Vector3 diff1 = m_player->GetPosition() - m_position;
	//Vector3 diff2 = m_tou->GetPosition() - m_position;
	//プレイヤーを見つけたら
	if (SearchPlayer() == true)
	{

		//ベクトルを正規化する
		diff1.Normalize();
		//移動速度を設定する
		m_moveSpeed = diff1 * 250.0f;
		//攻撃できる距離なら
		if (IsCanAttack() == true)
		{
			//乱数によって、攻撃するか待機させるかを決定する
			int ram = rand() % 100;
			if (ram > 30)
			{
				m_enemyState = enEnemyState_Attack;
				m_isUnderAttack = false;
				return;
			}
			else
			{
				//待機ステートに遷移する
				m_enemyState = enEnemyState_Idle;
				return;
			}

		}
		//攻撃できない距離なら
		if (IsCanAttack() == false) {
			m_enemyState = enEnemyState_Chase;
			return;
		}
	}

	////本殿へ向かう
	//if (SearchGoal() == true)
	//{
	//	diff2.Normalize();
	//	m_moveSpeed = diff2 * 250.0f;
	//	//本殿を目指すステートに遷移する
	//	m_enemyState = enEnemyState_Goal;
	//	return;
	//}

	//何も見つけられなければ
	else
	{
		//待機ステートに遷移する
		m_enemyState = enEnemyState_Idle;
		return;
	}
}



void Enemy::ManageState()
{
	switch (m_enemyState)
	{
		//待機ステート
	case Enemy::enEnemyState_Idle:
		ProcessIdleStateTransition();
		break;
		/*case Enemy::enEnemyState_Goal:
			ProcessGoalStateTransition();
			break;*/
			//追跡ステート
	case  Enemy::enEnemyState_Chase:
		ProcessChaseStateTransition();
		break;
		//攻撃ステート
	case Enemy::enEnemyState_Attack:
		ProcessAttackStateTransition();
		break;
		//被ダメージステート
	case Enemy::enEnemyState_Damage:
		ProcessDamageStateTransition();
		break;
		//死ステート
	case Enemy::enEnemyState_Down:
		ProcessDownStateTransition();
		break;
	default:
		break;
	}
}

void Enemy::PlayAnimation()
{
	m_modelRender.SetAnimationSpeed(1.0f);
	switch (m_enemyState)
	{
	case Enemy::enEnemyState_Idle:
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.1f);
		break;
	case Enemy::enEnemyState_Chase:
		m_modelRender.SetAnimationSpeed(1.2f);
		m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
		break;
		/*case Enemy::enEnemyState_Goal:
			m_modelRender.SetAnimationSpeed(1.2f);
			m_modelRender.PlayAnimation(enAnimationClip_Run, 0.1f);
			break;*/
	case Enemy::enEnemyState_Attack:
		m_modelRender.SetAnimationSpeed(1.6f);
		m_modelRender.PlayAnimation(enAnimationClip_Attack, 0.1f);
		break;
	case enEnemyState_Damage:
		m_modelRender.SetAnimationSpeed(1.3f);
		m_modelRender.PlayAnimation(enAnimationClip_Damage, 0.1f);
	case Enemy::enEnemyState_Down:
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
		//攻撃中判定をtrueにする
		m_isUnderAttack = true;
	}
	else if (wcscmp(eventName, L"attack_end") == 0) {
		m_isUnderAttack = false;
	}
}

const bool Enemy::IsCanAttack() const
{
	Vector3 diff = m_player->GetPosition() - m_position;
	//エネミーとプレイヤーの距離が近かったら
	if (diff.LengthSq() <= 100.0f * 100.0f)
	{
		//攻撃可
		return true;
	}
	//攻撃不可
	return false;
}


void Enemy::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}