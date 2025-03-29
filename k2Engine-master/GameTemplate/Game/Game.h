#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Enemy;

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

	BackGround* m_backGround;
	GameCamera* m_gameCamera;
	Player*m_player;
	Enemy* m_enemy;
	ModelRender m_modelRender;
	Vector3 m_pos;
	GameState m_gameState = enOutGame;//�A�E�g�Q�[���ɂ��Ă���
private:
};

