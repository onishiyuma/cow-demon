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
	const Vector3 HP_GAUGE_SCALE = { 195.0f,22.0f,1.0f };
	//HPフレームのサイズ
	const Vector3 HP_FREAM_SCALE = { 195.0f,22.0f,1.0f };
	//HPフレームのポジション
	const float ENEMY_HP = 160.0f;
	//HPスプライトのポジション
	const float ENEMY_HP_GAUGE = 170.0f;
	//赤。
	Vector4 RED = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	//黒。
	Vector4 BLACK = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	//透明。
	Vector4 TOUMEI = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	//ボス紫
	Vector4 BOSS = { 1.0f,0.0f,1.0f,1.0f };
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
	//m_HPSprite.SetScale(m_scale);
	m_HPSprite.SetPivot(Vector2{ 0.0f,1.0f });
	m_HPSprite.SetScale(m_scale
	);
	m_HPSprite.SetMulColor(RED);
	//枠の部分
	m_HPFreamSprite.Init("Assets/UI/white.DDS", HP_FREAM_SCALE.x, HP_FREAM_SCALE.y);
	m_HPFreamSprite.SetScale(m_scale);
	m_HPFreamSprite.SetPivot(Vector2{ 0.0f,1.0f });
	m_HPFreamSprite.SetMulColor(BLACK);
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	return true;
}

void EnemyUI::Update()
{
	// どの敵も指していない場合はバーを非表示
	if (!m_enemy && !m_littleEnemy && !m_annoyingEnemy && !m_bossEnemy) {
		m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f)); // 幅0で非表示
		m_HPFreamSprite.SetMulColor(TOUMEI);            // 透明
		return; // このフレームは何もしない
	}
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


	// --- ゲージ（バー）描画位置 ---
	float frameWidth = HP_FREAM_SCALE.x;
	float gaugeWidth = HP_GAUGE_SCALE.x;
	float offsetX = (frameWidth - gaugeWidth) * -1.0f;


	// ピボットが左上なので、x座標にoffsetXを加えるだけでOK
	m_HPSprite.SetPosition(Vector3(m_position.x + offsetX, m_position.y, 0.0f));

}

void EnemyUI::Scale()
{
	//体力の計算
	if (m_enemy != nullptr)
	{
		if (m_enemy->IsDead())
		{
			// 必ずバーを非表示にしてからポインタ切断
			m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
			m_enemy = nullptr; // ポインタ切断
			return;
		}

		float m_enemyHp = m_enemy->GetHP();
		float m_maxHP = m_enemy->GetMaxHP();
		float wari = (float)m_enemyHp/(float)m_maxHP;
		Vector3 scale = { wari,1.0f,1.0f };

		if (m_enemyHp <= 0.0f) {
			m_HPSprite.SetScale(Vector3(0.0f,1.0f,1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
		}
		else if (m_enemyHp <= m_maxHP) {
			m_HPSprite.SetScale(scale);
		}
	}

	if (m_littleEnemy != nullptr)
	{
		if (m_littleEnemy->IsDead())
		{
			// 必ずバーを非表示にしてからポインタ切断
			m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
			m_littleEnemy = nullptr; // ポインタ切断
			return;
		}

		float m_enemyHp = m_littleEnemy->GetHP();
		float m_maxHP = m_littleEnemy->GetMaxHP();
		float wari = (float)m_enemyHp /(float)m_maxHP;
		Vector3 scale = { wari,1.0f,1.0f };

		if (m_enemyHp <= 0.0f) {
			m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
		}
		else if (m_enemyHp <= m_maxHP) {
			m_HPSprite.SetScale(scale);
		}
	}

	if (m_bossEnemy != nullptr)
	{
		if (m_bossEnemy->IsDead())
		{
			// 必ずバーを非表示にしてからポインタ切断
			m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
			m_bossEnemy = nullptr; // ポインタ切断
			return;
		}

		float m_enemyHp = m_bossEnemy->GetHP();
		float m_maxHP = m_bossEnemy->GetMaxHP();
		float wari = (float)m_enemyHp /(float)m_maxHP;
		Vector3 scale = { wari,1.0f,1.0f };

		if (m_enemyHp <= 0.0f) {
			m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
		}
		else if (m_enemyHp <= m_maxHP) {
			m_HPSprite.SetScale(scale);
			m_HPSprite.SetMulColor(BOSS);
		}
	}

	if (m_annoyingEnemy != nullptr)
	{
		if (m_annoyingEnemy->IsDead())
		{
			// 必ずバーを非表示にしてからポインタ切断
			m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
			m_annoyingEnemy = nullptr; // ポインタ切断
			return;
		}
		float m_enemyHp = m_annoyingEnemy->GetHP();
		float m_maxHP = m_annoyingEnemy->GetMaxHP();
		float wari = (float)m_enemyHp /(float)m_maxHP;
		Vector3 scale = { wari,1.0f,1.0f };
		
		if (m_enemyHp <= 0.0f) {
			m_HPSprite.SetScale(Vector3(0.0f, 1.0f, 1.0f));
			m_HPFreamSprite.SetMulColor(TOUMEI);
		}
		else if (m_enemyHp <= m_maxHP) {
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
	////カメラからエネミーの位置のベクトルを求める
	Vector3 toEnemy = Enemy->GetPosition() - m_gameCamera->GetCameraPos();
	float distance = toEnemy.Length();
	toEnemy.Normalize();

	//カメラの前方向とカメラからエネミーのベクトルの内積を求める
	float dot = m_gameCamera->GetCameraForward().Dot(toEnemy);

	//内積の結果から角度を求める
	float angleRad = acos(dot);
	//カメラから見てエネミーが一定角度の時
	if (fabsf(angleRad) <= Math::DegToRad(40.0f))
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



