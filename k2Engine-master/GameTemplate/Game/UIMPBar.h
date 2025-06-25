#pragma once

class Player;
class Game;

class UIMPBar: public IGameObject
{
public:
	//メンバ関数
	UIMPBar();
	~UIMPBar();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
private:
	Player* m_player; // プレイヤー
	SpriteRender m_mpFrame; // MPフレーム
	SpriteRender m_mpBar; // MPバー
};

