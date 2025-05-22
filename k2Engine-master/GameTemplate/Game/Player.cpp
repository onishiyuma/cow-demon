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
#include "GameCamera.h"
#include "BellSpriteRender.h"
#include "NoHeal.h"
#include<time.h>

namespace
{
	Vector3 FONT_POSITION = { -330.0f,-300.0f,0.0f };
	Vector4 FONT_COLOR = { 1.0f,0.0f,1.0f,1.0f };
}
bool Player::Start()
{
	//モデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm");

	//モデルの座標をセットする。
	m_position.Set(70.0f, 0.0f, -1000.0f);
	//キャラコンを初期化。
	m_characterController.Init(m_charaConRadius, m_charaConHeight, m_position);
	
	//初期化。
	m_prevStickAngle = 0.0f;
	m_totalRotation = 0.0f;

	//プレイヤーのHPをセットする。
	m_playerHP = 100;

	//ヒールのクールタイム
	m_healCoolDown = 10.0f;

	//各種インスタンスアドレスの検索。
	m_shimenawa = FindGO<Shimenawa>("shimenawa");
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_playerLight = FindGO<PlayerLight>("playerLight");
	m_playerLight = NewGO<PlayerLight>(0, "playerLight");
	m_shimenawa = FindGO<Shimenawa>("shimenawa");
	m_gameCamera = FindGO<GameCamera>("gameCamera");
	m_lantern = FindGO<Lantern>("lantern");
	m_uiHeal = FindGO<UIheal>("uiheal");
	m_ringBell = FindGO<RingBell>("ringbell");


	return true;
}

Player::Player()
{
	
}

Player::~Player()
{
	DeleteGO(m_playerLight);
}

void Player::Update()
{	
	//移動処理。
	Move();

	//判定を呼び出す。
	Collision();

	//回復できるように知らせる。
	UpdateHealHint();

	//呪いの抵抗が0を下回っていたら。
	if (m_playerHP<=0)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}

	//灯籠に火が灯っていれば攻撃できる。
	if (m_enemyIsCanAttack)
	{
		//通常攻撃。
		NormalAttack();

		//スキル
		Skill();

		//月読の加護。
		SkillTukuyomiBlessing();

		//しめ縄。
		ItemShimenawa();
	}
	else
	{
		//文字の表示。
		wchar_t text[256] = { 0 };
		swprintf_s(text, 256, L"灯籠を全て灯すと攻撃できるぞ！");
		m_fontRender1.SetText(text);
		m_fontRender1.SetPosition(FONT_POSITION);
		m_fontRender1.SetColor(FONT_COLOR);
	}
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
	right *= stikL.x * 310.0f;
	forward *= stikL.y * 310.0f;

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

	if (g_pad[0]->IsTrigger(enButtonRB2) && m_attackCoolDown <= 0.0f)
	{
		//クリティカルダメージ。
		m_criticalATK = m_playerATK *m_cliticalDamage;
		//通常ダメージ。
		m_normalATK = m_playerATK;

		//クールタイムの設定。
		m_attackCoolDown = 0.389f;
		//通常攻撃の作成用関数。
		MakeNormalAttack();
	}
}

//------------------------------------------------------------------------------------------------------------
//スキル。
//------------------------------------------------------------------------------------------------------------
void Player::Skill()
{
	//スキル発動。
	if (g_pad[0]->IsTrigger(enButtonLB2) && m_skillCharge >= m_skillMax)
	{
		//スキルの作成用関数を呼び出す。
		MakeSkill();
		//チャージ量をリセット。
		m_skillCharge = 0;
	}
}

//-------------------------------------------------------------------------------------------------------------
//月読の加護。
//-------------------------------------------------------------------------------------------------------------
void Player::SkillTukuyomiBlessing()
{
	//クールタイムを減らす。
	m_tukuyomiBlessingCoolDown -= g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonX) && m_tukuyomiBlessingCoolDown <= m_tukuyomiMax)
	{
		//月読の加護作成用関数を呼び出す。
		MakeTukuyomiBlessing();
		//クールタイムの設定。 
		m_tukuyomiBlessingCoolDown = 40.0f;
	}
}

//-------------------------------------------------------------------------------------------------------------
//しめ縄。
//-------------------------------------------------------------------------------------------------------------
void Player::ItemShimenawa()
{
	//取得までの時間を増加。
	m_shimenawaGetTime += g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonY)&&m_shimenawaGetTime>=m_collectTime)
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
	//インスタンスを作成。
	Purification* purification = NewGO<Purification>(0);
	//座標を設定。
	Vector3 PurificationPos = m_position;
	//座標を少し上げる。
	PurificationPos.y += 70.0f;
	//座標をセットする。
	purification->SetPosition(PurificationPos);
	//名前をつける。
	purification->SetName("purification");
}

//スキルの作成。
void Player::MakeSkill()
{
	//インスタンスを作成。
	Amulet* amulet = NewGO<Amulet>(0);
	//座標を設定。
	Vector3 AmuletPos = m_position;
	//座標を少し下げる。
	AmuletPos.y += 70.0f;
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
//終わり
//-----------------------------------------------------------------------------------------------------------------
 
//プレイヤーの管理。
void Player::ManageState()
{

}

//回復用判定。
void Player::Collision()
{
	// 鈴のコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("ringbell");
	bool isBellHit = false;

	for (auto collision : collisions)
	{
		if (collision->IsHit(m_characterController))
		{
			isBellHit = true;

			//コリジョン内に入ったら画像を表示する。
			if (m_bellSpriteRender == nullptr)
			{
				m_bellSpriteRender = NewGO<BellSpriteRender>(0);
			}
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				if (m_distSq <= contactThresholdSq)
				{
					Distance();
					// ヒールUIが有効な場合のみ回転処理。
					if (!m_uiHeal->m_isDelete)
					{
						RotationCamera();
					}
					else
					{
						m_totalRotation = 0.0f;
					}
					// 接触中の鈴が見つかったら抜け出す。
					break;
				}
			}
		}
	}

	// 鈴に接触していなければ鈴の画像を削除する。
	if (!isBellHit)
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
	}


	// Aボタンを押していない間は回転量と角度をリセット。
	m_totalRotation = 0.0f;
	m_prevStickAngle=0.0f;
}

//鈴との距離を測る。
void Player::Distance()
{
	if (m_ringBell == nullptr) {
		return;
	}

	//360度回した回復。
	if (m_totalRotation >= 360.0f)
	{
		//HPを回復する。
		HealHP(100);
		m_totalRotation = 0.0f;
	}
			
	// プレイヤーと鈴の位置を取得。
	Vector3 bellPos = m_ringBell->GetPosition();
	Vector3 playerPos = m_position;

	// 距離を測って接触判定。
	m_distSq = (playerPos - bellPos).LengthSq();
}

void Player::RotationCamera()
{
	// 右スティックのx,y値。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	// 入力が小さいときは無視する。
	float stickLengthSq = x * x + y * y;
	if (stickLengthSq < 0.01f) 
	{
		return;
	}

	// スティックの現在の角度。
	float angle = atan2f(y, x) * (180.0f / 3.14159265f);

	// 角度差分。
	float delta = angle - m_prevStickAngle;

	// -180〜180度の範囲に収める。
	if (delta > 180.0f)
	{
		delta -= 360.0f;
	}
	else if (delta < -180.0f)
	{
		delta += 360.0f;
	}

	// 累積回転量に加算。
	m_totalRotation += fabsf(delta);

	// 現在の角度を保存。
	m_prevStickAngle = angle;

	// スティックを回すと回復。
	if (m_totalRotation >= 100.0f)
	{
		if (m_healCoolDown <= 0)
		{
			//接触していない場合は回転角をリセット。
			m_totalRotation = 0.0f;
			if (m_uiHeal->m_useHeal >= 0)
			{
				m_healCoolDown = 10.0f;
				HealHP(100);
				m_uiHeal->m_useHeal--;
			}
			else
			{
				if (m_noHeal == nullptr)
				{
					m_noHeal = NewGO<NoHeal>(0);
				}
			}
		}
	}

	//回転量と角度をリセット。
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
		wchar_t text[256] = { 0 };
		swprintf_s(text, 256, L"本殿の前でAボタンを押すと回復できるぞ！");
		m_fontRender2.SetText(text);
		m_fontRender2.SetPosition({ -300.0f,-250.0f,0.0f });
		m_fontRender2.SetColor({ 1.0f,0.0f,1.0f,1.0f });
	}

	//回復のクールタイムを減らす。
	m_healCoolDown -= g_gameTime->GetFrameDeltaTime();
}

void Player::Render(RenderContext& rc)
{
	//灯籠が灯っていれば描画しない。
	if (!m_enemyIsCanAttack)
	{
		m_fontRender1.Draw(rc);
	}
	//HPが100以上あれば描画しない。
	if (m_playerHP<=90)
	{
		m_fontRender2.Draw(rc);
		m_isDisplay = false;
	}
}
