#pragma once

class Player;
class Stone;

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
	int m_lanternCount = 0; //火を灯したカウント


};

