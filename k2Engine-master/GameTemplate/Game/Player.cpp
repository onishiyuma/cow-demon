#include "stdafx.h"
#include "Player.h"
#include "Purification.h"
#include "Amulet.h"
#include "TukuyomiBlessing.h"
#include "Shimenawa.h"
#include "GameOver.h"
#include "Shimenawa.h"

#include<time.h>

//定数を設定する場所
namespace
{
	int CHARGE_INCREASE_AMOUNT = 3;//チャージ増加量。
}


bool Player::Start()
{
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	//キャラコンを初期化
	m_characterController.Init(m_charaConRadius, m_charaConHeight, m_position);
	m_position.Set(0.0f, 0.0f, 0.0f);
	//プレイヤーのHPをセットする。
	m_playerHP = 100;

	//乱数を初期化。
	srand((unsigned)time(NULL));

	return true;
}

Player::Player()
{
	
}

Player::~Player()
{
	DeleteGO(this);
}

void Player::Update()
{
	//移動処理。
	Move();

	/////////////////////コメントアウト解除を忘れずに/////////////////////////////
	/*//灯籠に火が灯っていれば攻撃できる。
	if (m_enemyIsCanAttack != false)
	{
		//通常攻撃。
		NormalAttack();

		//スキル
		Skill();

		//月読の加護。
	    TukuyomiBlessing();
	}*/
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////ここは削除する/////////////////////////
	//通常攻撃。
	NormalAttack();

	//スキル。
	Skill();

	//月読の加護。
	SkillTukuyomiBlessing();
	/////////////////////////////////////////////////////////////////

	//呪いの抵抗が0を下回っていたら。
	if (m_playerHP<=0)
	{
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}


	//モデルを更新する。
	m_modelRender.Update();
}

void Player::Move()
{
	//xの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stikL;
	stikL.x = g_pad[0]->GetLStickXF();
	stikL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動をさせない。
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量を乗算する
	right *= stikL.x * 250.0f;
	forward *= stikL.y * 250.0f;

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

	//キャラコンを使って座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	//フレームごとに座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	//キャラコンが地面に付いていたら。
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}

	//モデルの座標をセットする
	m_modelRender.SetPosition(m_position);
}

//通常攻撃。
void Player::NormalAttack()
{
	//クールタイムを減らす。
	m_attackCoolDown -= g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonA)&&m_attackCoolDown<=0.0f)
	{
		//通常攻撃の作成用関数。
		MakeNormalAttack();
		//クールタイムの設定。
		m_attackCoolDown = 0.38f;

		//呪いの抵抗の侵食値を減らしていく。
		m_playerHP -= 1;

		//会心の設定。
		int ram = rand() % 100;
		if (ram > m_criticalRate)
		{
			//クリティカルダメージ。
			m_criticalATK=m_playerATK * m_cliticalDamage;
			//スキルを使うため
			m_skillCharge += CHARGE_INCREASE_AMOUNT;
		}
		//非会心。
		else
		{
			//通常ダメージ。
			m_normalATK=m_playerATK;
		}
	}
}

//スキル。
void Player::Skill()
{
		//スキル発動。
		if (g_pad[0]->IsTrigger(enButtonB)&&m_skillCharge >= 50)
		{
			//スキルの作成用関数を呼び出す。
			MakeSkill();

			//スキルのダメージ。
			m_skillATK = m_playerATK * m_skillMagnification;

			//チャージ量をリセット。
			m_skillCharge = 0;
		}
}

//月読の加護。
void Player::SkillTukuyomiBlessing()
{
	//クールタイムを減らす。
	m_tukuyomiBlessingCoolDown -= g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonX) && m_tukuyomiBlessingCoolDown <= 0.0f)
	{
		//月読の加護作成用関数を呼び出す。
		MakeTukuyomiBlessing();
		//クールタイムの設定。
		m_tukuyomiBlessingCoolDown = 40.0f;

		//月読の加護のダメージ。
		m_TukuyomiATK = m_playerATK * m_TukuyomiMagnification;

	}
}

//しめ縄。(アイテム)
void Player::ItemShimenawa()
{
	//取得までの時間を増加。
	m_shimenawaGetTime += g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonY)&&m_shimenawaGetTime>=5.0f)
	{
		//しめ縄を設置。
		m_shimenawa->SetPosition(this->m_position);
		
		//タイマーをリセット。
		m_shimenawaGetTime = 0.0f;
	}
}

//通常攻撃作成
void Player::MakeNormalAttack()
{
	//インスタンスを作成。
	Purification* purification = NewGO<Purification>(0);
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
	Vector3 TukuyomoBlessingPos = m_position;
	//座標をセットする。
	tukuyomiBlessing->SetPosition(TukuyomoBlessingPos);
	//名前をつける。
	tukuyomiBlessing->SetName("tukuyomiBlessing");
}

void Player::MakeShimenawa()
{
	//インスタンスを作成。
	Shimenawa* shimenawa = NewGO<Shimenawa>(0);
	Vector3 ShimenawaPos = m_position;
	//座標をセットする。
	shimenawa->SetPosition(ShimenawaPos);
	//名前をつける。
	shimenawa->SetName("shimenawa");
}

//プレイヤーの管理。
void Player::ManageState()
{

}

void Player::Render(RenderContext&renderContext)
{
	//モデルを表示する。
	//m_modelRender.Draw(renderContext);
}