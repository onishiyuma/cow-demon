#pragma once

class Lantern;

class Line :public IGameObject
{
public:
	Line();
	~Line();

	bool Start();
	void Move();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数。
public:
	Vector3			m_position;				//座標。
private:
	//灯籠各種のインスタンス。
	Lantern*		m_lantern1;
	Lantern*		m_lantern2;
	Lantern*		m_lantern3;
	Lantern*		m_lantern4;
	SpriteRender	m_spriteRender;			//ラインの画像。

	Vector3			m_firstPosition;		//初期座標。

	int				m_directionState = 0;	//移動方向の状態。
	bool			m_isMoving = false;		//移動中か。
};

