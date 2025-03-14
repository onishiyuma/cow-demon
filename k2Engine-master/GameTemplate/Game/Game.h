#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;

class Game : public IGameObject
{
public:
	enum GameState
	{
		enInGame,//インゲーム。
		enOutGame,//アウトゲーム。
	};
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void Render(RenderContext& rc);


	GameCamera* m_gameCamera;
	Player*m_player;
	ModelRender m_modelRender;
	Vector3 m_pos;
	GameState m_gameState = enOutGame;//アウトゲームにしておく
private:
};

