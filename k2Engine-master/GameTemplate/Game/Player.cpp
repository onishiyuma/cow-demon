#include "stdafx.h"
#include "Player.h"
#include "Purification.h"
#include "Amulet.h"

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

	/*//灯籠に火が灯っていれば攻撃できる。
	if (m_enemyIsCanAttack != false)
	{
		//通常攻撃。
		NormalAttack();

		//スキル
		Skill();
	}*/

	//通常攻撃。
	NormalAttack();

	//スキル
	Skill();

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

	if (g_pad[0]->IsTrigger(enButtonRB2)&&m_attackCoolDown<=0.0f)
	{
		//通常攻撃の作成用関数。
		MakeNormalAttack();
		//クールタイムの設定。
		m_attackCoolDown = 0.38f;

		//会心の設定。
		m_playerATK;
		int ram = rand() % 100;
		if (ram > m_criticalRate)
		{
			//クリティカルダメージ。
			m_criticalATK=m_playerATK * m_cliticalDamage;
			//スキルを使うため
			m_skillCharge += CHARGE_INCREASE_AMOUNT;
		}
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

	//チャージ量が100を超えていたら。
	if (m_skillCharge >= 100)
	{
		//スキル発動。
		if (g_pad[0]->IsTrigger(enButtonLB2))
		{
			//スキルの作成用関数。
			MakeSkill();

			//スキルのダメージ。
			m_skillATK = m_playerATK * m_playerATKMagnification;

			//チャージ量をリセット。
			m_skillCharge = 0;
		}
	}
}

//通常攻撃作成
void Player::MakeNormalAttack()
{
	//作成。
	Purification* purification = NewGO<Purification>(0);
	Vector3 PurificationPos = m_position;
	//座標を少し上げる。
	PurificationPos.y += 70.0f;
	//座標をセットする。
	purification->SetPosition(PurificationPos);
	purification->SetName("purification");
}

//スキルの作成。
void Player::MakeSkill()
{
	Amulet* amulet = NewGO<Amulet>(0);
	Vector3 AmuletPos = m_position;
	//座標を少し下げる。
	AmuletPos.y += 70.0f;
	//座標をセットする。
	amulet->SetPosition(AmuletPos);
	amulet->SetName("amulet");
}

void Player::ManageState()
{

}

void Player::Render(RenderContext&renderContext)
{
	//モデルを表示する。
	m_modelRender.Draw(renderContext);
}