#pragma once
#include "Game.h";
class UISimenawa :public IGameObject
{
public:
	//メンバ関数。
	UISimenawa();
	~UISimenawa();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//しめ縄の時間が0になったら、しめ縄のゲージを非表示にする。
	void UpdateShimenawaGaugeVisibility();

private:
	//メンバ変数。
	Player*			m_player;						//プレイヤー。
	SpriteRender	m_ropeSprite;					//しめ縄の画像。
	SpriteRender	m_ropeGage;						//しめ縄のゲージ。
	FontRender		m_fontRender;					//フォントレンダー。
	float			m_ropeTimer = 0.0f;				//しめ縄の時間。
	float			m_ShimenawaUseTimer = 15.0;		//しめ縄を使うための時間。
	float			m_CountDownTime = 1.0f;			//カウントダウンの時間。
	float			m_waitTimer = 0.1f;				//待機時間。
	int				m_displayTime = 0;				//表示される時間。
	bool			m_isReset = false;				//リセットできるか。
};

