#include "stdafx.h"
#include "UIheal.h"
#include "Game.h"
#include "Player.h"

namespace
{
	//配列に座標を設定する。
	const Vector3 SOUL_POSITIONS[3] =
	{
		Vector3(-660.0f,-450.0f,0.0f),
		Vector3(-748.0f,-450.0f,0.0f),
		Vector3(-850.0f,-450.0f,0.0f)
	};
	const char* SOUL_TEXTURE_PATH = "Assets/UI/gage.DDS";
	const float SPRITE_SIZE = 150.0f;
	const int MAX_HEAL = 3;
}


UIheal::UIheal()
{
	
}

UIheal::~UIheal()
{

}

bool UIheal::Start()
{
	//インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");

	//画像を初期化。
	for (int i = 0; i < MAX_HEAL; i++)
	{
		//画像を読み込む。
		m_soulSprites[i].Init(SOUL_TEXTURE_PATH, SPRITE_SIZE, SPRITE_SIZE);
		//座標を設定。
		m_soulSprites[i].SetPosition(SOUL_POSITIONS[i]);
	}

	//回復回数を初期化。
	m_useHeal = MAX_HEAL;

	return true;
}

void UIheal::Update()
{
	for (int i = 0; i < MAX_HEAL; i++)
	{
		m_soulSprites[i].Update();
	}
}

void UIheal::Render(RenderContext& rc)
{
	if (m_useHeal <= 0)
	{
		m_isDelete = true;
		DeleteGO(this);
		return;
	}

	for (int i = MAX_HEAL - m_useHeal; i < MAX_HEAL; i++)
	{
		m_soulSprites[i].Draw(rc);
	}
}