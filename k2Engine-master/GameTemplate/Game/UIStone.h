#pragma once

class Stone;
class Player;


class UIStone: public IGameObject
{
public:
	//メンバ関数
	UIStone();
	~UIStone();

	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	FontRender m_fontRender;
	Stone* m_stone ;
	Player* m_player;

};

