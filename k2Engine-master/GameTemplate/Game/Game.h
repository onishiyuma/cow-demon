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
	Stone* m_stone; //火打石
	Stone* m_stone1; //火打石
	UIStone* m_uiStone; //火打石の数
	Lantern* m_lantern; //灯籠
	LanternAttack* m_lanternAttack; //攻撃用灯籠
	Vector3 m_pos;//座標。
	GameState m_gameState = enOutGame;//�A�E�g�Q�[���ɂ��Ă���
	SpriteRender m_spriteRender;//スプライトレンダー。
	bool m_lanternAction = false; 

};

