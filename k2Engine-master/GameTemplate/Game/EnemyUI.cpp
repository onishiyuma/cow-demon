#include "stdafx.h"
#include "EnemyUI.h"
#include "Enemy.h"
#include "LittleEnemy.h"
#include"AnnoyingEnemy.h"
#include "BossEnemy.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"

namespace
{
	//HPゲージのサイズ
	const Vector3 HP_GAUGE_SCALE = { 180.0f,13.0f,1.0f };
	//HPフレームのサイズ
	const Vector3 HP_FREAM_SCALE = { 195.0f,22.0f,1.0f };

	//HPのポジション
	const float ENEMY_HP = 160.0f;
	//赤
	Vector4 RED = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	//黒
	Vector4 BLACK = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
}

EnemyUI::EnemyUI()
{

}

EnemyUI::~EnemyUI()
{

}

bool EnemyUI::Start()
{
	//ゲージ部分
	m_HPSprite.Init("Assets/UI/white.DDS", HP_GAUGE_SCALE.x, HP_GAUGE_SCALE.y);
	m_HPSprite.SetScale(m_scale);
	m_HPSprite.SetMulColor(RED);
	//枠の部分
	m_HPFreamSprite.Init("Assets/UI/white.DDS", HP_FREAM_SCALE.x, HP_FREAM_SCALE.y);
	m_HPFreamSprite.SetScale(m_scale);
	m_HPFreamSprite.SetMulColor(BLACK);
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	return true;
}

void EnemyUI::Update()
{
	
	//大きさの処理
	Scale();

	//位置調整の処理
	Position();


	m_HPFreamSprite.Update();
	m_HPSprite.Update();
}

void EnemyUI::Position()
{
	

	Vector3 position;

	//親によってポジションを変える
	if (m_enemy != nullptr)
	{
		//ポジションの取得
		position = m_enemy->GetPosition();

		//エネミー上部に表示
		position.y += ENEMY_HP;
	}

	else if (m_littleEnemy != nullptr)
	{
		position = m_littleEnemy->GetPosition();

		//エネミー上部に表示
		position.y += ENEMY_HP;
	}

	else if (m_annoyingEnemy != nullptr)
	{
		position = m_annoyingEnemy->GetPosition();

		//エネミー上部に表示
		position.y += ENEMY_HP;
	}

	else if (m_bossEnemy != nullptr)
	{
		position = m_bossEnemy->GetPosition();

		//エネミー上部に表示
		position.y += ENEMY_HP;
	}

	//ワールド座標からスクリーン座標
	g_camera3D->CalcScreenPositionFromWorldPosition(m_position, position);
	//フレームをセットする
	m_HPFreamSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));


	//画像を左に寄せる
	Vector3 BarSizeSubtraction = SendHPBer(HP_GAUGE_SCALE, m_scale);
	m_position.x -= BarSizeSubtraction.x;

	//HPバーをセットする
	m_HPSprite.SetPosition(Vector3(m_position.x, m_position.y, 0.0f));


}

void EnemyUI::Scale()
{
	//体力の計算
	if (m_enemy != nullptr)
	{
		float m_enemyHp = m_enemy->GetHP();
		float m_maxHP = m_enemy->GetMaxHP();
		float wari = (float)m_enemyHp / (float)m_maxHP;
		Vector3 scale = { 1.0f,1.0f,1.0f };
		m_HPFreamSprite.SetScale(scale);


		if (m_enemyHp <= 100) {
			m_HPSprite.SetScale(scale);
		}
	}

	if (m_littleEnemy != nullptr)
	{
		float m_enemyHp = m_littleEnemy->GetHP();
		float m_maxHP = m_littleEnemy->GetMaxHP();
		float wari = (float)m_enemyHp /(float)m_maxHP;
		Vector3 scale = { 1.0f,1.0f,1.0f };
		m_HPFreamSprite.SetScale(scale);


		if (m_enemyHp <= 100) {
			m_HPSprite.SetScale(scale);
		}
	}

	if (m_bossEnemy != nullptr)
	{
		float m_enemyHp = m_bossEnemy->GetHP();
		float m_maxHP = m_bossEnemy->GetMaxHP();
		float wari = (float)m_enemyHp /(float)m_maxHP;
		Vector3 scale = { 1.0f,1.0f,1.0f };
		m_HPFreamSprite.SetScale(scale);


		if (m_enemyHp <= 100) {
			m_HPSprite.SetScale(scale);
		}
	}

	if (m_annoyingEnemy != nullptr)
	{
		float m_enemyHp = m_annoyingEnemy->GetHP();
		float m_maxHP = m_annoyingEnemy->GetMaxHP();
		float wari = (float)m_enemyHp /(float)m_maxHP;
		Vector3 scale = { 1.0f,1.0f,1.0f };
		m_HPFreamSprite.SetScale(scale);


		if (m_enemyHp <= 100) {
			m_HPSprite.SetScale(scale);
		}
	}

}

Vector3 EnemyUI::SendHPBer(Vector3 size, Vector3 scale)
{
	Vector3 BarSize = size;
	Vector3 changedBarSize = Vector3::Zero;
	Vector3 BarSizeSubtraction = Vector3::Zero;

	changedBarSize.x = BarSize.x * scale.x;
	BarSizeSubtraction.x = BarSize.x - changedBarSize.x;
	BarSizeSubtraction.x *= 0.5f;

	return BarSizeSubtraction;
}

template<class T>
bool EnemyUI::Angle(T Enemy)
{
	//カメラからエネミーの位置のベクトルを求める
	Vector3 toEnemy = Enemy->GetPosition() - m_gameCamera->GetCameraPos();
	float distance = toEnemy.Length();
	toEnemy.Normalize();

	//カメラの前方向とカメラからエネミーのベクトルの内積を求める
	float dot = m_gameCamera->GetCameraForward().Dot(toEnemy);

	//内積の結果から角度を求める
	float angleRad = acos(dot);
	//カメラから見てエネミーが一定角度の時
	if (fabsf(angleRad) <= Math::DegToRad(50.0f))
	{
		return true;
		
	}
	return false;
}

void EnemyUI::SetEnemy(Enemy* enemy) {
	m_enemy = enemy;
	m_littleEnemy = nullptr;
}

void EnemyUI::SetLittleEnemy(LittleEnemy* littleEnemy) {
	m_littleEnemy = littleEnemy;
	m_enemy = nullptr;
}

void EnemyUI::SetAnnoyingEnemy(AnnoyingEnemy* annoyingEnemy)
{
	m_annoyingEnemy = annoyingEnemy;
	m_bossEnemy = nullptr;
}
void EnemyUI::SetBossEnemy(BossEnemy* bossEnemy)
{
	m_bossEnemy = bossEnemy;
	m_annoyingEnemy = nullptr;
}

void EnemyUI::Render(RenderContext& rc)
{
	if (m_enemy&& !Angle(m_enemy))return;
	if (m_littleEnemy&& !Angle(m_littleEnemy))return;
	if (m_annoyingEnemy && !Angle(m_annoyingEnemy))return;
	if (m_bossEnemy && !Angle(m_bossEnemy))return;

	m_HPFreamSprite.Draw(rc);
	m_HPSprite.Draw(rc);
}



