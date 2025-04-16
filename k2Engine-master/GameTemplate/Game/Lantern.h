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

class Lantern : public IGameObject
{
public:
	//メンバ関数
	Lantern();
	~Lantern();

	bool Start();
	
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	ModelRender m_modelRender;
	Vector3 m_firstPosition; //最初の座標
	Vector3 m_position;
	Player* m_player;
	Stone* m_stone;
	SpriteLight* m_spriteLight;
	SpriteNoStone* m_spriteNoStone;
	TimingBarA* m_timingBarA;
	TimingBarB* m_timingBarB;
	TimingBarC* m_timingBarC;
	Line* m_line;
	SpritePush* m_spritePush;

	int m_lanternCount = 0; //火を灯したカウント
	bool m_lightUI = false; //灯籠の近くにいるか？
	bool m_noStoneUI = false; //火打石がなかったら
	bool m_lanternAction = false; //「A:火を灯す」を押したら
	bool m_lightFlag = false;//火が灯っているか？
	int m_buttonAState = 0;
};

