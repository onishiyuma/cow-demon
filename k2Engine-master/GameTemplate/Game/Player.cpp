#include "stdafx.h"
#include "Player.h"
#include "Purification.h"

#include<time.h>

namespace
{
	int CHARGE_INCREASE_AMOUNT = 3;//チャージ増加量。
}

bool Player::Start()
{
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	//キャラコンを初期化
	m_charaConRadius = 25.0f;
	m_charaConHeight = 75.0f;
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

	//回転処理。
	Rotation();

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

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001 && fabsf(m_moveSpeed.z) < 0.001)
	{
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
	    //このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
    //m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	// //atan2を使用して、角度を求めている。
	// //これが回転角度になる。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	// //SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rotation);
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

//通常攻撃(遠距離)。
void Player::NormalAttack()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		MakePurification();
		/*m_playerATK;
		int ram = rand() % 100;
		if (ram > 5)
		{
			m_playerATK * 2;
		}*/
	}
}

//スキル
void Player::Skill()
{
	//チャージ量が100を超えていたら。
	if (m_skillCharge >= 100)
	{
		//スキル発動。
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//チャージ量をリセット。
			m_skillCharge = 0;
		}
	}
}

//発射するための準備。
void Player::MakePurification()
{
	//作成。
	Purification* purification = NewGO<Purification>(0);
	Vector3 PurificationPos = m_position;
	//座標を少し上げる。
	PurificationPos.y += 70.0f;
	//座標をセットする。
	purification->SetPosition(PurificationPos);
	purification->SetRotation(m_rotation);
	purification->SetName("purification");
}

void Player::ManageState()
{

}

void Player::Render(RenderContext&renderContext)
{
	//モデルを表示する。
	m_modelRender.Draw(renderContext);
}