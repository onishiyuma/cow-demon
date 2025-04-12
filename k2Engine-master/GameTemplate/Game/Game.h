#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Enemy;
class CrossHair;
class Shimenawa;
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
	UItukuyomi* m_uitukuyomi;
	UIskill* m_uiskill;
	UISimenaw* m_uisimenaw;
	MiniMap* m_miniMap;
	UIcurseBar* m_uicursebar;
	UIheal* m_uiheal;
	Vector3 m_pos;//座標。
	GameState m_gameState = enOutGame;//�A�E�g�Q�[���ɂ��Ă���
	SpriteRender m_spriteRender;//スプライトレンダー。
private:
};

