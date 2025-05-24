#include "stdafx.h"
#include "Lantern.h"
#include "Player.h"
#include "Stone.h"
#include "SpriteLight.h"
#include "SpriteNoStone.h"
#include "TimingBarA.h"
#include "TimingBarB.h"
#include "TimingBarC.h"
#include "Line.h"
#include "SpritePush.h"
#include "LanternLight.h"

bool Lantern::Start() 
{
	//モデルを読み込む
	m_modelRender.Init("Assets/modelData/lanternJapan/lantern.tkm");
	m_modelRender.SetScale(0.6f, 0.6f, 0.6f);

	//各種インスタンスアドレスを検索。
	m_player = FindGO <Player>("player");
	m_stone = FindGO<Stone>("stone");
	m_spriteLight = FindGO<SpriteLight>("spriteLight");
	m_spriteNoStone = FindGO<SpriteNoStone>("spriteNoStone");
	m_timingBarA = FindGO<TimingBarA>("timingBarA");
	m_timingBarB = FindGO<TimingBarB>("timingBarB");
	m_timingBarC = FindGO<TimingBarC>("timingBarC");
	m_line = FindGO<Line>("line");
	m_spritePush = FindGO<SpritePush>("spritePush");

	return true;
}

Lantern::Lantern() 
{

}

Lantern::~Lantern() 
{
	DeleteGO(m_spriteLight);
	DeleteGO(m_spriteNoStone);
	DeleteGO(m_timingBarA);
	DeleteGO(m_line);
	DeleteGO(m_spritePush);
}



void Lantern::Update() 
{
	//モデルレンダーの更新。
	m_modelRender.Update();
	//座標の更新。
	m_modelRender.SetPosition(m_position);
	//プレイヤーから灯籠に向かうベクトルを計算。
	Vector3 diff = m_position - m_player->m_position;


	/*//灯籠に火が灯っていなかったら。
	if (!m_isLight)
	{
		//ベクトルの長さが条件よりも小さいか。
		if (diff.Length() <= m_lightUpDistance)
		{
			if (!m_isLightUI)
			{

				m_isLightUI = true;

				//「Ａ：火を灯す」を読み込む。
				m_spriteLight = NewGO<SpriteLight>(0, "spriteLight");
			}
			if (m_buttonAState == 0) {

				//Aボタンを入力したら。
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//火打石をひとつ以上持っていたら。
					if (m_player->m_stoneCount > 0) 
					{

						//ミニゲームをしていなかったら。
						if (!m_isLanternAction) 
						{

							//ミニゲーム中にする。
							m_isLanternAction = true;

							//「A:火を灯す」。
							DeleteGO(m_spriteLight);

							//タイミングバーを読み込む。
							m_timingBarB = NewGO<TimingBarB>(0, "timingBarB");

							//バーのラインを読み込む。
							m_line = NewGO<Line>(0, "line");


							//「A：タイミングよくボタンを押せ」を読み込む。
							m_spritePush = NewGO<SpritePush>(0, "spritePush");

							m_buttonAState = 1;
						}
					}
					//火打石をひとつも持っていなかったら。
					else
					{
						if (!m_isNoStoneUI) 
						{

							m_isNoStoneUI = true;

							//「A:火打石が足りない」を読み込む
							m_spriteNoStone = NewGO<SpriteNoStone>(0, "spriteNoStone");
						}
					}
				}
				if (m_buttonAState == 1)
				{

					//Aボタンをおしたら。
					if (g_pad[0]->IsTrigger(enButtonA))
					{
						m_buttonAState = 0;
						m_isLanternAction = false;

						//バーのラインが、-10.0ｆ以上10.0ｆ以下（成功の場所）だったら。
						if (m_line->m_position.x <= 10.0f && m_line->m_position.x >= -10.0f)
						{

							//陽が灯っている灯籠のカウントを増やす。
							m_player->m_lanternCount++;

							//火打石の数を減らす。
							m_player->m_stoneCount--;

							//各種画像を削除する。
							DeleteGO(m_timingBarB);
							DeleteGO(m_line);
							DeleteGO(m_spritePush);

							//灯籠に火が灯っている判定にする。
							m_isLight = true;
						}
					}
				}
			}
		}
		//灯籠から離れたら。
		else 
		{

			//各種フラグをfalseにする。
			m_isLightUI = false;
			m_isNoStoneUI = false;
			m_isLanternAction = false;

			m_buttonAState = 0;

			//画像を削除する。
			if (m_spriteLight != nullptr)
			{
				DeleteGO(m_spriteLight);
				m_spriteLight = nullptr;
			}
			if (m_spriteNoStone != nullptr)
			{
				DeleteGO(m_spriteNoStone);
				m_spriteNoStone = nullptr;
			}
			if (m_timingBarB != nullptr)
			{
				DeleteGO(m_timingBarB);
				m_timingBarB = nullptr;
			}
			if (m_line != nullptr)
			{
				DeleteGO(m_line);
				m_line = nullptr;
			}
			if (m_spritePush != nullptr)
			{
				DeleteGO(m_spritePush);
				m_spritePush = nullptr;
			}
		}
	}
	
	//灯籠4つに火がともっていたら攻撃できる。
	if (m_player->m_lanternCount == 4)
	{
		m_player->m_enemyIsCanAttack = true;
	}*/

	//灯籠に火が灯っていなかったら。
	if (!m_isLight)
	{
		//ベクトルの長さが条件よりも小さいか。
		if (diff.Length() <=m_lightUpDistance)
		{
			if (!m_isLightUI)
			{
				m_isLightUI = true;
	
				//「Ａ：火を灯す」を読み込む。
				m_spriteLight = NewGO<SpriteLight>(0, "spriteLight");
			}

			if (m_buttonAState == 0) 
			{
				//Aボタンを入力したら。
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					//火打石をひとつ以上持っていたら。
					if (m_player->m_stoneCount > 0)
					{

						//ミニゲームをしていなかったら。
						if (!m_isLanternAction)
						{
							//ミニゲーム中にする。
							m_isLanternAction = true;

							//「A:火を灯す」。
							DeleteGO(m_spriteLight);

							//タイミングバーを読み込む。
							m_timingBarB = NewGO<TimingBarB>(0, "timingBarB");

							//バーのラインを読み込む。
							m_line = NewGO<Line>(0, "line");
							//「A：タイミングよくボタンを押せ」を読み込む。
							m_spritePush = NewGO<SpritePush>(0, "spritePush");

							m_buttonAState = 1;
						}
					}
					//火打石をひとつも持っていなかったら。
					else
					{
						if (!m_isNoStoneUI)
						{

							m_isNoStoneUI = true;

							//「A:火打石が足りない」を読み込む
							m_spriteNoStone = NewGO<SpriteNoStone>(0, "spriteNoStone");
						}
					}
				}
			}
			if (m_buttonAState == 1)
			{
				//Aボタンをおしたら。
				if (g_pad[0]->IsTrigger(enButtonA))
				{
					m_buttonAState = 0;
					m_isLanternAction = false;

					//バーのラインが、-10.0ｆ以上10.0ｆ以下（成功の場所）だったら。
					if (m_line->m_position.x <= 10.0f && m_line->m_position.x >= -10.0f)
					{
						//陽が灯っている灯籠のカウントを増やす。
						m_player->m_lanternCount++;

						//火打石の数を減らす。
						m_player->m_stoneCount--;

						//各種画像を削除する。
						DeleteGO(m_timingBarB);
						DeleteGO(m_line);
						DeleteGO(m_spritePush);

						//灯籠に火が灯っている判定にする。
						m_isLight = true;
					}
				}
			}
		}
		//灯籠から離れたら。
		else
		{
			ResetLanternState();
		}
	}
	//灯籠4つに火がともっていたら攻撃できる。
	if (m_player->m_lanternCount == 4)
	{
		m_player->m_enemyIsCanAttack = true;
	}
}



void Lantern::ResetLanternState()
{
	//各種フラグをfalseにする。
	m_isLightUI = false;
	m_isNoStoneUI = false;
	m_isLanternAction = false;
	m_buttonAState = 0;

	//画像を削除する。
	if (m_spriteLight != nullptr)
	{
		DeleteGO(m_spriteLight);
		m_spriteLight = nullptr;
	}
	if (m_spriteNoStone != nullptr)
	{
		DeleteGO(m_spriteNoStone);
		m_spriteNoStone = nullptr;
	}
	if (m_timingBarB != nullptr)
	{
		DeleteGO(m_timingBarB);
		m_timingBarB = nullptr;
	}
	if (m_line != nullptr)
	{
		DeleteGO(m_line);
		m_line = nullptr;
	}
	if (m_spritePush != nullptr)
	{
		DeleteGO(m_spritePush);
		m_spritePush = nullptr;
	}
}

void Lantern::Render(RenderContext& rc) 
{
	m_modelRender.Draw(rc);
}
