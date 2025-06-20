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

class LanternAttack:public IGameObject
{
public:
	//メンバ関数。
	LanternAttack();
	~LanternAttack();

	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

	//メンバ変数。
public:
	Vector3			m_firstPosition;					//最初の座標。
	Vector3			m_position;							//座標。
	bool			m_isLight = false;					//火が灯っているか。
private:
	ModelRender		m_modelRender;						//モデルレンダー。
	Player*			m_player;							//プレイヤー。
	Stone*			m_stone;							//石。
	SpriteLight*	m_spriteLight;						//ライトの画像。
	SpriteNoStone*	m_spriteNoStone;					//石を持っていない画像。
	SpritePush*		m_spritePush;						//プッシュ画像。
	const int       m_attack = 5;						//攻撃力。
	int				m_buttonAState = 0;					//「A:火を灯す」ボタンの状態。
	int				m_lanternCount = 0;					//火を灯したカウント。
	bool			m_isLightUI = false;				//灯籠の近くにいるか。
	bool			m_isNoStoneUI = false;				//火打石がなかったら。
	bool			m_isLanternAttackAction = false;	//「A:火を灯す」を押したら。


};

