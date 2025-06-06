#pragma once

class Player;
class Stone;
class SpriteLight;
class SpriteNoStone;
class TimingBarA;
class TimingBarB;
class TimingBarC;
class Line;
class SpritePush;
class LanternLight;

class Lantern : public IGameObject
{
public:
	//メンバ関数。
	Lantern();
	~Lantern();
	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//リセット用関数。
	void ResetLanternState();

	//メンバ変数。
public:
	Vector3				m_firstPosition;			//最初の座標
	Vector3				m_position;					//座標。
	bool				m_isLight = false;			//火が灯っているか。
private:
	ModelRender			m_modelRender;				//モデルレンダー。
	Player*				m_player;					//プレイヤー。
	Stone*				m_stone;					//石。
	SpriteLight*		m_spriteLight;				//灯籠の画像。
	SpriteNoStone*		m_spriteNoStone;			//石がない画像。
	TimingBarA*			m_timingBarA;				//タイミングバーA。
	TimingBarB*			m_timingBarB;				//タイミングバーB。
	TimingBarC*			m_timingBarC;				//タイミングバーC。
	Line*				m_line;						//線。
	SpritePush*			m_spritePush;				//プッシュ画像。
	LanternLight*		m_lanternLight = nullptr;	//灯籠。
	ModelInitData       m_initData;
	bool				m_isNoStoneUI = false;		//火打石があるか。
	bool				m_isLanternAction = false;	//「A:火を灯す」灯籠を灯したか。
	bool				m_isLightUI = false;		//灯籠の近くにいるか。
	bool                m_isLightAction = false;	//灯籠に火を灯したか。
	const float			m_lightUpDistance = 100.0f;	//灯籠を灯す距離。	
	int					m_buttonAState = 0;			//Aボタンの入力ステート管理。
	int					m_lanternCount = 0;			//火を灯したカウント。

};

