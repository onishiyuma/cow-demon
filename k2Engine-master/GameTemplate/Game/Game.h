#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Enemy;
class CrossHair;
class Shimenawa;
class Stone;
class UIStone;
class Lantern;
class LanternAttack;

class UItukuyomi;
class UIskill;
class UISimenaw;
class UIcurseBar;
class UIheal;
class MiniMap;

class Game : public IGameObject
{
public:
	enum GameState
	{
		enInGame,//�C���Q�[���B
		enOutGame,//�A�E�g�Q�[���B
	};
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	BackGround* m_backGround;//背景。
	GameCamera* m_gameCamera;//ゲームカメラ。
	Player*m_player;//プレイヤー。
	Enemy* m_enemy;//敵。
	CrossHair*m_crossHair;//クロスヘアー。
	ModelRender m_modelRender;//モデルレンダー。
	Shimenawa* m_shimenawa;//しめ縄。
	Stone* m_stone1; //火打石
	Stone* m_stone2; //火打石
	Stone* m_stone3; //火打石
	Stone* m_stone4; //火打石
	Stone* m_stone5; //火打石
	Stone* m_stone6; //火打石
	Stone* m_stone7; //火打石
	UIStone* m_uiStone; //火打石の数
	Lantern* m_lantern1; //灯籠
	Lantern* m_lantern2; //灯籠
	Lantern* m_lantern3; //灯籠
	Lantern* m_lantern4; //灯籠
	LanternAttack* m_lanternAttack1; //攻撃用灯籠
	LanternAttack* m_lanternAttack2; //攻撃用灯籠
	LanternAttack* m_lanternAttack3; //攻撃用灯籠
	UItukuyomi* m_uitukuyomi;
	UIskill* m_uiskill;
	UISimenaw* m_uisimenaw;
	MiniMap* m_miniMap;
	UIcurseBar* m_uicursebar;
	UIheal* m_uiheal;
	Vector3 m_pos;//座標。
	GameState m_gameState = enOutGame;//�A�E�g�Q�[���ɂ��Ă���
	SpriteRender m_spriteRender;//スプライトレンダー。
	

};

