#include "stdafx.h"
#include "MiniMap.h"
#include "Player.h"
#include "Enemy.h"

namespace
{
	//マップの初期位置。
	Vector3 MAP_POSITION = Vector3(-760.0f, 350.0f, 0.0f);
	//マップの半径。
	float MAP_RADIUS = 200.0f;
	//マップの大きさ。
	float LIMITED_RANGE_IMAGE = 300.0f;
}

MiniMap::MiniMap()
{

}

MiniMap::~MiniMap()
{

}

bool MiniMap::Start()
{
	//マップの下地。
	m_spriteRender.Init("Assets/MiniMap/Back.DDS", 450, 450);
	m_spriteRender.SetPosition(MAP_POSITION);

	//自キャラ。
	m_playerSprite.Init("Assets/MiniMap/ji.DDS", 60, 60);
	m_playerSprite.SetPosition(MAP_POSITION);

	//エネミー。
	m_enemySprite.Init("Assets/MiniMap/demon.DDS", 50, 50);

	//各種インスタンスアドレスを検索。
	m_enemy = FindGO<Enemy>("enemy");
	m_player = FindGO<Player>("player");

	return true;

}

void MiniMap::Update()
{
	//敵とプレイヤーの位置を取得。
	Vector3 playerPosition = m_player->GetPosition();
	Vector3 enemyPosition = m_enemy->GetPosition();

	Vector3 mapPosition;

	//マップに表示する範囲に敵がいたら。
	if (WouldPositionConvertToMapPosition(playerPosition, enemyPosition, mapPosition))
	{
		//マップに表示するように設定する。
		m_isImage = true;
		//スプライトレンダーに座標を設定。
		m_enemySprite.SetPosition(mapPosition);
	}
	//マップに表示する範囲に敵がいなかったら。
	else
	{
		//マップに表示しない。
		m_isImage = false;
	}

	m_spriteRender.Update();
	m_playerSprite.Update();
	m_enemySprite.Update();
}

const bool MiniMap::WouldPositionConvertToMapPosition(Vector3 wouldCenterPosition, Vector3 wouldPosition, Vector3& mapPosition)
{
	//Y座標はマップと関係ないので0にする。
	wouldCenterPosition.y = 0.0f;
	wouldPosition.y = 0.0f;
	Vector3 diff = wouldPosition - wouldCenterPosition;
	//マップの中心とするオブジェクトとの距離が一定ならば。
	if (diff.LengthSq() >= LIMITED_RANGE_IMAGE * LIMITED_RANGE_IMAGE)
	{
		//表示しないようにする。
		return false;
	}

	//ベクトルの長さを取得。
	float length = diff.Length();

	//カメラの前方向ベクトルから。
	//クヲータニオンを作成する。
	Vector3 forward = g_camera3D->GetForward();
	Quaternion rot;
	rot.SetRotationDegY(atan2(-forward.x, forward.z));

	//ベクトルにカメラの回転を適用。
	rot.Apply(diff);

	//ベクトルを正規化する。
	diff.Normalize();

	//ベクトルをマップ座標系に変換する。
	diff *= length * MAP_RADIUS / LIMITED_RANGE_IMAGE;

	//マップの中央座標と上記のベクトルを加算する。
	mapPosition = Vector3(MAP_POSITION.x + diff.x, MAP_POSITION.y + diff.z, 0.0f);
	return true;
}

void MiniMap::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_playerSprite.Draw(rc);
	//マップに表示する範囲に敵がいたら。
	if (m_isImage == false)
	{
		return;
	}
	m_enemySprite.Draw(rc);
}