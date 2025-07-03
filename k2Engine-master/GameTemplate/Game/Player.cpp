#include "stdafx.h"
#include "Player.h"
#include "Purification.h"
#include "Amulet.h"
#include "TukuyomiBlessing.h"
#include "GameOver.h"
#include "Shimenawa.h"
#include "GameCamera.h"
#include "PlayerLight.h"
#include "Lantern.h"
#include "UIheal.h"
#include "RingBell.h"
#include "BellSpriteRender.h"
#include "NoHeal.h"
#include "SpinStick.h"
#include <time.h>

namespace
{
	//モデルの座標
	const Vector3 MODEL_POSITION = { 70.0f,0.0f,-1000.0f };
	//文字の座標。
	const Vector3 FONT_POSITION = { -330.0f,-350.0f,0.0f };	
	//Lスティックの移動速度。
	const float L_STICK_MOVE_SPEED = 350.0f;
	//エフェクトの大きさ。
	const Vector3 EFFECT_SCALE = { 55.0f,55.0f,55.0f };
}


bool Player::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	EffectEngine::GetInstance()->ResistEffect(11, u"Assets/effect/RingBellEffect/Heal.efk");

	//モデルの座標を設定する。
	m_position.Set(MODEL_POSITION);

	//キャラコンを初期化。
	m_characterController.Init(m_charaConRadius, m_charaConHeight, m_position);
	
	//初期化。
	m_prevStickAngle = 0.0f;
	m_totalRotation = 0.0f;

	//プレイヤーのHPを設定する。
	m_playerHP = 100;

	//ヒールのクールタイム
	m_healCoolDown = 10.0f;

	//プレイヤーのMPを設定する。
	m_playerMP = m_playerMaxMP;

	//プレイヤーライトのインスタンスを生成。
	m_playerLight = NewGO<PlayerLight>(0, "playerLight");

	//インスタンスアドレスを検索。
	m_shimenawa = FindGO<Shimenawa>("shimenawa");
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_playerLight = FindGO<PlayerLight>("playerLight");
	m_uiHeal = FindGO<UIheal>("uiheal");
	m_game = FindGO<Game>("game");
	m_lantern = FindGO<Lantern>("lantern");
	m_ringBell = FindGO<RingBell>("ringbell");
	
	return true;
}

Player::Player()
{
	
}

Player::~Player()
{
	DeleteGO(m_playerLight);
	DeleteGO(m_effectEmitter);
	DeleteGO(m_bellSpriteRender);
}

void Player::Update()
{
	//カウントダウンしているときは判定を行わない。
	if ( !m_game->m_isCowntDownStart)
	{
		return;
	}

	//移動処理。
	Move();
	//判定を呼び出す。
	Collision();
	//回復できるように知らせる。
	UpdateHealHint();
	//攻撃処理。
	PlayerAttack();
	//毒状態の時はHPを減らす。
	PoisonState();
}

void Player::PlayerAttack()
{
	//灯籠に火が灯っていれば攻撃できる。
	if (!m_enemyIsCanAttack)
	{
		return;
	}

	//通常攻撃。
	NormalAttack();
	//スキル
	Skill();
	//月読の加護。
	SkillTukuyomiBlessing();
	//しめ縄。
	ItemShimenawa();
}

void Player::Move()
{
	//xの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stikL;
	stikL.x = g_pad[0]->GetLStickXF();
	stikL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y方向には移動をさせない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量を乗算する。
	right *= stikL.x * L_STICK_MOVE_SPEED;
	forward *= stikL.y * L_STICK_MOVE_SPEED;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	if (m_characterController.IsOnGround())
	{
		//重力をなくす。
		m_moveSpeed.y = 0.0f;
	}
	//地面についていなければ。
	else
	{
		//重力を発生させる。
		m_moveSpeed.y -= m_gravity;
	}

	//フレームごとに座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	//キャラコンが地面に付いていたら。
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}

	//モデルの座標をセットする。
	m_modelRender.SetPosition(m_position);
}

//-----------------------------------------------------------------------------------------------------------
//通常攻撃。
//-----------------------------------------------------------------------------------------------------------
void Player::NormalAttack()
{
	//クールタイムを減らす。
	m_attackCoolDown -= g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonRB2) && IsCoolDownReady(m_attackCoolDown) && HasEnoughMP(2))
	{
		//クリティカルダメージ。
		m_criticalATK = m_playerATK * m_cliticalDamage;

		//通常ダメージ。
		m_normalATK = m_playerATK;

		//クールタイムの設定。
		m_attackCoolDown = 0.389f;

		//通常攻撃の作成用関数。
		MakeNormalAttack();

		//プレイヤーのMPを減らす。
		HasEnoughMP(2);
	}
}

//------------------------------------------------------------------------------------------------------------
//スキル。
//------------------------------------------------------------------------------------------------------------
void Player::Skill()
{
	//スキル発動。
	if (g_pad[0]->IsTrigger(enButtonLB2) && m_skillCharge >= m_skillMax && HasEnoughMP(10))
	{
		//スキルの作成用関数を呼び出す。
		MakeSkill();

		//チャージ量をリセット。
		m_skillCharge = 0;

		ConsumeMP(10);
	}
}

//-------------------------------------------------------------------------------------------------------------
//月読の加護。
//-------------------------------------------------------------------------------------------------------------
void Player::SkillTukuyomiBlessing()
{
	//クールタイムを減らす。
	m_tukuyomiBlessingCoolDown -= g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonX) && IsCoolDownReady(m_tukuyomiBlessingCoolDown, m_tukuyomiMax) && HasEnoughMP(25))
	{
		//月読の加護作成用関数を呼び出す。
		MakeTukuyomiBlessing();
		//クールタイムの設定。 
		m_tukuyomiBlessingCoolDown = 40.0f;
		ConsumeMP(25);
	}
}

//-------------------------------------------------------------------------------------------------------------
//しめ縄。
//-------------------------------------------------------------------------------------------------------------
void Player::ItemShimenawa()
{
	//取得までの時間を増加。
	m_shimenawaGetTime += g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonY) && m_shimenawaGetTime >= m_collectTime)
	{
		//しめ縄作成用関数を呼び出す。
		MakeShimenawa();
		//タイマーをリセット。
		m_shimenawaGetTime = 0.0f;
	}
}



//--------------------------------------------------------------------------------------------------------------
//ここから作成用関数
//--------------------------------------------------------------------------------------------------------------

//通常攻撃作成。
void Player::MakeNormalAttack()
{
	g_soundEngine->ResistWaveFileBank(72, "Assets/sound/Attack.wav");
	m_nomalAttack = NewGO<SoundSource>(72);
	m_nomalAttack->Init(72);
	m_nomalAttack->Play(false);
	//インスタンスを作成。
	Purification* purification = NewGO<Purification>(0);
	//座標を設定。
	Vector3 PurificationPos = m_position;
	//座標を少し上げる。
	PurificationPos.y += 85.0f;
	//座標をセットする。
	purification->SetPosition(PurificationPos);
	//名前をつける。
	purification->SetName("purification");
}

//スキルの作成。
void Player::MakeSkill()
{
	g_soundEngine->ResistWaveFileBank(52, "Assets/sound/skill.wav");
	m_skill = NewGO<SoundSource>(52);
	m_skill->Init(52);
	m_skill->Play(false);
	//インスタンスを作成。
	Amulet* amulet = NewGO<Amulet>(0);
	//座標を設定。
	Vector3 AmuletPos = m_position;
	//座標を少し下げる。
	AmuletPos.y += 85.0f;
	//座標をセットする。
	amulet->SetPosition(AmuletPos);
	//名前をつける。
	amulet->SetName("amulet");
}	

//月読の加護の作成関数。
void Player::MakeTukuyomiBlessing()
{
	//インスタンスを作成。
	TukuyomiBlessing* tukuyomiBlessing = NewGO<TukuyomiBlessing>(0);
	//座標を設定。
	Vector3 TukuyomiBlessingPos = m_position;
	//座標をセットする。
	tukuyomiBlessing->SetPosition(TukuyomiBlessingPos);
	//名前をつける。
	tukuyomiBlessing->SetName("tukuyomiBlessing");
}

//しめ縄の作成。
void Player::MakeShimenawa()
{
	g_soundEngine->ResistWaveFileBank(53, "Assets/sound/rope.wav");
	m_simenawa = NewGO<SoundSource>(53);
	m_simenawa->Init(53);
	m_simenawa->Play(false);
	//インスタンスを作成。
	Shimenawa* shimenawa = NewGO<Shimenawa>(0);
	//座標を設定。
	Vector3 ShimenawaPos = m_position;
	//座標をセットする。
	shimenawa->SetPosition(ShimenawaPos);
	//名前をつける。
	shimenawa->SetName("shimenawa");
}
//-----------------------------------------------------------------------------------------------------------------
//終わり。
//-----------------------------------------------------------------------------------------------------------------



//コリジョン判定。
void Player::Collision()
{
	RingBellCollision();                // 回復。
	EnemyAttackCollision();				// 通常の敵。
	AnnoyingEnemyAttackCollision();		// ウザイ敵。
	BossEnemyAttackCollision();			// ボス。
	BossEnemyPoisonCollision();			// ボスの毒。
	LittleEnemyPoisonCollision();		// 小さい敵の毒。
	ExplosionCollision();				// 爆発。
}

//鈴との距離を測る。
void Player::Distance()
{
	if (m_ringBell == nullptr) 
	{
		return;
	}

	//プレイヤーと鈴の位置を取得。
	Vector3 bellPos = m_ringBell->GetPosition();
	Vector3 playerPos = m_position;

	//距離を測って接触判定。
	m_distSq = (playerPos - bellPos).LengthSq();
}

void Player::RotationCamera()
{
	//クールダウン中ならカウントを減らすだけ。
	if (m_healCoolDown > 0.0f)
	{
		m_healCoolDown -= g_gameTime->GetFrameDeltaTime();
		return;
	}

	//右スティックのx,y値。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	//入力が小さいときは無視する(デッドゾーン)。
	float stickLengthSq = x * x + y * y;
	if (stickLengthSq < 0.01f)
	{
		return;
	}

	//スティックの現在の角度。
	float angle = atan2f(y, x) * (180.0f / 3.14159265f);
	//角度差分。
	float delta = angle - m_prevStickAngle;
	//累積回転量に加算。
	m_totalRotation += fabsf(delta);
	//現在の角度を保存。
	m_prevStickAngle = angle;
	//-180〜180度の範囲に収める。
	if (delta > 180.0f)
	{
		delta -= 360.0f;
	}
	else if (delta < -180.0f)
	{
		delta += 360.0f;
	}

	//一周回っていないのであれば何もしない。
	if (m_totalRotation < 360.0f)
	{
		return;
	}

	//回復回数がない場合はリセット。
	if (m_totalRotation < 360.0f || m_uiHeal->m_useHeal <= 0)
	{
		return;
	}

	//SEを再生。
	g_soundEngine->ResistWaveFileBank(50, "Assets/sound/hell.wav");
	m_hell = NewGO<SoundSource>(50);
	m_hell->Init(50);
	m_hell->Play(false);
	//回復するHPをセット。
	HealHP(100);
	//回復のエフェクトを再生。
	CreateEffect();
	//回復の回数を減らす。
	m_uiHeal->m_useHeal--;
	//回復モードを戻す。
	m_isHealMode = false;
	//回復にクールタイムを設ける。
	m_healCoolDown = 3.0f;
	//回復のスティック回転をリセット。
	m_totalRotation = 0.0f;
}

void Player::HealHP(int amount)
{
	//HPを回復する。
	m_playerHP += amount;
	//HP上限を超えて回復しないようにする。
	if (m_playerHP >m_playerMaxHP)
	{
		m_playerHP = m_playerMaxHP;
	}
}

void Player::UpdateHealHint()
{
	//HPが減っていたら回復できるように知らせる。
	if (m_playerHP <= 90)
	{
		m_isDisplay = true;
	}

	//一回だけ表示させたいので。
	if (m_isDisplay)
	{
		m_isDisplay = false;
	}

	//回復のクールタイムを減らす。
	m_healCoolDown -= g_gameTime->GetFrameDeltaTime();
}

void Player::PoisonState()
{
	//ステータスが毒状態ではなければスキップ。
	if (m_playerState != enPlayerState_Poison)
	{
		return;
	}

	//毒を1秒ずつ減らす。
	m_poisonCoolDown += g_gameTime->GetFrameDeltaTime();
	if (m_poisonCoolDown >= 1.0f)
	{
		//毒状態の時はHPを減らす。
		m_playerHP -= m_poisonDamage;
		m_poisonCoolDown = 0.0f;
	}

	//毒状態の時はプレイヤーの状態を毒状態にする。
	m_poisonTimer += g_gameTime->GetFrameDeltaTime();
	if (m_poisonTimer >= m_poisonDuration)
	{
		//ステータスを初期化。
		m_playerState = enPlayerState_None;
		//初期化。
		m_poisonTimer = 0.0f;
		m_poisonCoolDown = 0.0f;
	}
}

void Player::RingBellCollision()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("ringbell");
	for (auto collision : collisions)
	{
		if (collision->IsHit(m_characterController))
		{
			m_isBellHit = true;
			if (m_uiHeal->m_useHeal < 0)
			{
				if (m_spinStick != nullptr)
				{
					DeleteGO(m_spinStick);
					m_spinStick = nullptr;
				}
				if (m_bellSpriteRender != nullptr)
				{
					DeleteGO(m_bellSpriteRender);
					m_bellSpriteRender = nullptr;
				}

				if (m_noHeal == nullptr)
				{
					m_noHeal = NewGO<NoHeal>(0);
				}
			}
			if (m_bellSpriteRender == nullptr)
			{
				m_bellSpriteRender = NewGO<BellSpriteRender>(0);
			}

			//鈴の位置を取得。
			Distance();

			//Aボタン単押しで回復モードに入る。
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				m_isHealMode = true;
				if (m_spinStick == nullptr)
				{
					m_spinStick = NewGO<SpinStick>(0);
				}
			}

			//回復モード中のみスティック回転を受け付ける。
			if (m_isHealMode)
			{
				if (!m_uiHeal->m_isDelete)
				{
					RotationCamera();
				}
				else
				{
					m_totalRotation = 0.0f;
				}
			}
			// 一定距離より離れたら画像を非表示
			if (m_distSq > m_contactThresholdSq)
			{
				if (m_bellSpriteRender != nullptr)
				{
					DeleteGO(m_bellSpriteRender);
					m_bellSpriteRender = nullptr;
				}
				if (m_spinStick != nullptr)
				{
					DeleteGO(m_spinStick);
					m_spinStick = nullptr;
				}
				if (m_noHeal != nullptr)
				{
					DeleteGO(m_noHeal);
					m_noHeal = nullptr;
				}
				m_isHealMode = false;
				break;
			}
			break;
		}
	}
	// Aボタンを押していない間は回転量と角度をリセット
	if (!g_pad[0]->IsPress(enButtonA) && !m_isHealMode)
	{
		m_totalRotation = 0.0f;
		m_prevStickAngle = 0.0f;
	}
	if (!m_isBellHit)
	{
		if (m_bellSpriteRender != nullptr)
		{
			DeleteGO(m_bellSpriteRender);
			m_bellSpriteRender = nullptr;
		}
		if (m_noHeal != nullptr)
		{
			DeleteGO(m_noHeal);
			m_noHeal = nullptr;
		}
		if (m_spinStick != nullptr)
		{
			DeleteGO(m_spinStick);
			m_spinStick = nullptr;
		}
	}
}

void Player::EnemyAttackCollision()
{
	if (m_isDamage_Enemy)
	{
		return;
	}

	//敵の攻撃用コリジョンチェック。
	{
		//敵の攻撃用のコリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy_attack");
		//配列をfor文で回す。
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突したら。
			if (collision->IsHit(m_characterController))
			{
				//HPを減らす。
				m_playerHP -= 5;
				m_isDamage_Enemy = true;
				//タイマーリセット。
				m_invincibleTime_Enemy = 0.0f;
				return;
			}
		}
	}

	//無敵時間の設定。
	if (!m_isDamage_Enemy)
	{
		return;
	}
	
	m_invincibleTime_Enemy += g_gameTime->GetFrameDeltaTime();

	//敵の攻撃を受けたら無敵にする。
	if (m_invincibleTime_Enemy >= m_invincibleTimeDuration)
	{
		m_invincibleTime_Enemy = 0.0f;
		m_isDamage_Enemy = false;
	}
}

void Player::AnnoyingEnemyAttackCollision()
{
	if (m_isDamage_Annoying)
	{
		return;
	}

	{
		//うざい敵の攻撃用コリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("annoyingenemy_attack");
		//配列をfor文で回す。
		for (auto collision : collisions)
		{
			if (collision->IsHit(m_characterController))
			{
				//HPを減らす。
				m_playerHP -= 1;
				m_isDamage_Annoying = true;
				//タイマーリセット。
				m_invincibleTime_Enemy = 0.0f;
				m_playerState = enPlayerState_Poison;

				return;
			}
		}
	}

	//無敵時間の設定。
	if (m_isDamage_Annoying)
	{
		return;
	}

	m_invincibleTime_Annoying += g_gameTime->GetFrameDeltaTime();

	if (m_invincibleTime_Annoying >= m_invincibleTimeDuration)
	{
		m_invincibleTime_Annoying = 0.0f;
		m_isDamage_Annoying = false;
	}
}

void Player::BossEnemyAttackCollision()
{
	if (m_isDamage_BossEnemy)
	{
		return;
	}

	{
		//ボスの攻撃用コリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("Boss_enemy_attack");
		//配列をfor文で回す。
		for (auto collision : collisions)
		{
			if (collision->IsHit(m_characterController))
			{
				//HPを減らす。
				m_playerHP -= 15;
				m_isDamage_BossEnemy = true;
				m_invincibleTime_BossEnemy = 0.0f;
				return;
			}
		}
	}

	//無敵時間の設定。
	if (m_isDamage_BossEnemy)
	{
		return;
	}

	m_invincibleTime_BossEnemy += g_gameTime->GetFrameDeltaTime();

	if (m_invincibleTime_BossEnemy >= m_invincibleTimeDuration)
	{
		m_invincibleTime_BossEnemy = 0.0f;
		m_isDamage_BossEnemy = false;
	}
}

void Player::BossEnemyPoisonCollision()
{
	if (m_isDamage_BossPoison)
	{
		return;
	}

	{
		//ボスの毒攻撃用コリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("BossEnemy_Poison");
		//配列をfor文で回す。
		for (auto collision : collisions)
		{
			if (collision->IsHit(m_characterController))
			{
				//HPを減らす。
				m_playerHP -= 10;
				m_isDamage_BossPoison = true;
				//タイマーリセット。
				m_invincibleTime_BossPoison = 0.0f;
				m_playerState = enPlayerState_Poison;
				return;
			}
		}
	}

	//無敵時間の設定。
	if (!m_isDamage_BossPoison)
	{
		return;
	}
	m_invincibleTime_BossPoison += g_gameTime->GetFrameDeltaTime();
	if (m_invincibleTime_BossPoison >= m_invincibleTimeDuration)
	{
		m_invincibleTime_BossPoison = 0.0f;
		m_isDamage_BossPoison = false;
	}
}

void Player::LittleEnemyPoisonCollision()
{
	if (m_isDamage_LittlePoison)
	{
		return;
	}

	{
		//小さい敵の攻撃用コリジョンを取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("LittleEnemy_Poison");
		//配列をfor文で回す。
		for (auto collision : collisions)
		{
			if (collision->IsHit(m_characterController))
			{
				//HPを減らす。
				m_playerHP -= 1;
				m_isDamage_LittlePoison = true;
				//タイマーリセット。
				m_invincibleTime_LittlePoison = 0.0f;
				m_playerState = enPlayerState_Poison;
				return;
			}
		}
	}

	//無敵時間の設定。
	if (m_isDamage_LittlePoison)
	{
		return;
	}
	m_invincibleTime_LittlePoison += g_gameTime->GetFrameDeltaTime();
	if (m_invincibleTime_LittlePoison >= m_invincibleTimeDuration)
	{
		m_invincibleTime_LittlePoison = 0.0f;
		m_isDamage_LittlePoison = false;
	}
}

void Player::ExplosionCollision()
{
	if (m_isDamage_Explosion)
	{
		return;
	}

	{
		//爆発のコリジョン判定。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("explosion");
		//配列をfor文で回す。
		for (auto collision : collisions)
		{
			if (collision->IsHit(m_characterController))
			{
				//HPを減らす。
				m_playerHP -= 20;
				m_isDamage_Explosion = true;
				//タイマーをリセット。
				m_invincibleTime_Explosion = 0.0f;
				return;
			}
		}
	}

	//無敵時間の設定。
	if (m_isDamage_Explosion)
	{
		return;
	}
	m_invincibleTime_Explosion += g_gameTime->GetFrameDeltaTime();
	if (m_invincibleTime_Explosion >= m_invincibleTimeDuration)
	{
		m_invincibleTime_Explosion = 0.0f;
		m_isDamage_Explosion = false;
	}
}

void Player::CreateEffect()
{
	//エフェクトエミッターのインスタンスを生成。
	m_effectEmitter = NewGO<EffectEmitter>(0);
	m_effectEmitter->Init(11);
	//エフェクトのサイズを設定する。
	m_effectEmitter->SetScale(EFFECT_SCALE);

	//回復のエフェクトをプレイヤーの位置より少し下にする。
	m_healEffectPosition = m_position;
	m_healEffectPosition.y -= 20.0f;

	//エフェクトの座標を設定する。
	m_effectEmitter->SetPosition(m_healEffectPosition);
	//エフェクトを再生。
	m_effectEmitter->Play();
}

void Player::Render(RenderContext& rc)
{
	//HPが100以上あれば描画しない。
	if (m_playerHP <= 90)
	{
		m_isDisplay = false;
	}
}
