#include "stdafx.h"
#include "Player.h"
#include "Purification.h"
#include "Amulet.h"
#include "TukuyomiBlessing.h"
#include "Shimenawa.h"
#include "GameOver.h"
#include "Shimenawa.h"

#include<time.h>

bool Player::Start()
{
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	//キャラコンを初期化
	m_position.Set(70.0f, 50.0f, -1300.0f);
	m_characterController.Init(m_charaConRadius, m_charaConHeight, m_position);
	//プレイヤーのHPをセットする。
	m_playerHP = 100;

	m_shimenawa = FindGO<Shimenawa>("shimenawa");

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
	if (m_enemyIsCanAttack != true)
	{
		//通常攻撃。
		NormalAttack();

		//スキル
		Skill();

		//月読の加護。
	    TukuyomiBlessing();

		//しめ縄。
	    ItemShimenawa();
	}*/
	////////////////////////////////////////////////////////////////////////////


	////////////////////////////ここは削除する/////////////////////////
	//通常攻撃。
	NormalAttack();

	//スキル。
	Skill();

	//月読の加護。
	SkillTukuyomiBlessing();

	//しめ縄。
	ItemShimenawa();
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

	if (g_pad[0]->IsTrigger(enButtonRB1)&&m_attackCoolDown<=0.0f)
	/////////////////デバック用///////////////////////////////////
	/*if (g_pad[0]->IsTrigger(enButtonA) && m_attackCoolDown <= 0.0f)
	{
		//クールタイムの設定。
		m_attackCoolDown = 0.38f;
		//通常攻撃の作成用関数。
		MakeNormalAttack();
	}*/
	///////////////////////////////////////////////////////////////


	////////////////正式なボタン配置///////////////////////
	if (g_pad[0]->IsTrigger(enButtonRB2) && m_attackCoolDown <= 0.0f)
	{
		//クールタイムの設定。
		m_attackCoolDown = 0.38f;
		//通常攻撃の作成用関数。
		MakeNormalAttack();
	}
}

//スキル。
void Player::Skill()
{
	////////////////デバック用///////////////////////////////////
	//スキル発動。
	/*if (g_pad[0]->IsTrigger(enButtonB) && m_skillCharge >= 50)
	{
		//スキルの作成用関数を呼び出す。
		MakeSkill();
		//チャージ量をリセット。
			m_skillCharge = 0;
	}*/
	///////////////////////////////////////////////////////////////


	////////////////正式なボタン配置///////////////////////
	//スキル発動。
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_skillCharge >= 50)
	{
		//スキルの作成用関数を呼び出す。
		MakeSkill();
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
	}
}

//しめ縄。(アイテム)
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



////////////////ここから先は作成用関数////////////////////////////////////


//通常攻撃作成
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

////////////////////////////////終わり///////////////////////////////////////////////
 
//プレイヤーの管理。
void Player::ManageState()
{

}

void Player::Render(RenderContext&renderContext)
{
	//モデルを表示する。
	//m_modelRender.Draw(renderContext);
}