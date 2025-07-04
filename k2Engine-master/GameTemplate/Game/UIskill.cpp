#include "stdafx.h"
#include "UIskill.h"
#include "Game.h"
#include "Player.h"

namespace 
{
	//ゲージのピボット。
	const Vector2 GAGE_PIVOT(0.5f, 0.0f);
	//スキル。
	const Vector3 SKILL_FREME_POSITION(600.0f, -425.0f, 0.0f);
	//スキルゲージ。
	const Vector3 SKILL_GAUGE_POSITION(600.0f, -485.0f, 0.0f);
	//スキルフォント。
	const Vector3 SKILL_FONT_POSITION(620.0f, -450.0f, 0.0f);
	//フォントの大きさ。
	const float FONT_SCALE = 0.6f;
	//ゲージの最大値。
	const Vector3 GAGE_SCALE(1.0f, 1.0f, 1.0f);
	//緑。
	const Vector4 GREEN(0.0f, 1.0f, 0.0f, 1.0f);
	//薄い緑。
	const Vector4 LIGHT_GREEN(0.0f, 1.0f, 0.0f, 0.2f);
	//白。
	const Vector4 WHITE(1.0f, 1.0f, 1.0f, 1.0f);
	//黒。
	const Vector4 BLACK(0.0f, 0.0f, 0.0f, 1.0f);
	//透明。
	const Vector4 TOUMEI(1.0f, 1.0f, 1.0f, 0.0f);
	//スキルゲージの最大値。
	const int SKILL_GAUGE_MAX = 100; 
}

UIskill::UIskill()
{

}

UIskill::~UIskill()
{

}

bool UIskill::Start()
{
	//インスタンスアドレスを検索。
	m_player = FindGO<Player>("player");

	//スキルゲージ。
	m_skillGageSprite.Init("Assets/UI/White.DDS", 124, 124);
	m_skillGageSprite.SetPosition(SKILL_GAUGE_POSITION);
	m_skillGageSprite.SetPivot(GAGE_PIVOT);

	//スキルスプライト。
	m_skillSprite.Init("Assets/UI/skilmax.DDS", 130, 130);
	m_skillSprite.SetPosition(SKILL_FREME_POSITION);

	//文字の座標と大きさを設定。
	m_fontRender.SetPosition(SKILL_FONT_POSITION);
	m_fontRender.SetScale(FONT_SCALE);

	return true;
}

void UIskill::Update()
{
	//スキルゲージの最大値を取得。
	m_skillGage = m_player->m_skillCharge;
    m_skillMax = m_player->m_skillMax;

	float wari = (float)m_skillGage /(float) m_skillMax;

	Vector3 scale = { 1.0f,	wari,1.0f };

	//スキルが使える状態だと濃い緑になる。
	if (m_skillGage>=m_skillMax) 
	{
		m_skillGageSprite.SetScale(GAGE_SCALE);
		m_skillGageSprite.SetMulColor(GREEN);
		
	}

	else 
	{
        m_skillGageSprite.SetScale(scale);
		m_skillGageSprite.SetMulColor(LIGHT_GREEN);
        m_fontRender.SetColor(WHITE);
    
	}
	

	

	//表示する文字を設定。
	wchar_t wcsbuf[256];
	int m_skillFont =m_skillGage;
	if (m_skillFont > SKILL_GAUGE_MAX)
	{
		m_skillFont = SKILL_GAUGE_MAX;
	}
	swprintf_s(wcsbuf, 256, L"%01d",m_skillFont);
    m_fontRender.SetText(wcsbuf);
	
	m_skillSprite.Update();
	m_skillGageSprite.Update();
}

void UIskill::Render(RenderContext& rc)
{
	if (m_skillGage>0)
	{
		m_skillGageSprite.Draw(rc);
        
	}

	m_skillSprite.Draw(rc);

	if (m_player->m_enemyIsCanAttack)
	{
      m_fontRender.Draw(rc);
	}
}