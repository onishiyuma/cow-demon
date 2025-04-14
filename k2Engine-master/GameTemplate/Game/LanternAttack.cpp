#include "stdafx.h"
#include "LanternAttack.h"
#include "Player.h"
#include "Stone.h"

bool LanternAttack::Start() 
{
	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/lanternJapan/lantern.tkm");

	m_player = FindGO <Player>("player");

	return true;
}

LanternAttack::LanternAttack() 
{

}

LanternAttack::~LanternAttack() 
{

}

void LanternAttack::Update() 
{
	//プレイヤーから灯籠に向かうベクトルを計算。
	Vector3 diff = m_player->m_position - m_position;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 200.0f)
	{


		//Aボタンを入力したら
		if (g_pad[0]->IsTrigger(enButtonA)) {
			//火打石をひとつ以上持っていたら
			if (m_player->m_stoneCount > 0) {

			}
			//火打石をひとつも持っていなかったら
			else {

			}
		}
		
		//自身を削除する。
		DeleteGO(this);
	}
}

void LanternAttack::Render(RenderContext& rc) 
{
	m_modelRender.Draw(rc);
}
