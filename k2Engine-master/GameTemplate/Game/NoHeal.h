#pragma once


class NoHeal :public IGameObject
{
public:
	//メンバ関数
	NoHeal();
	~NoHeal();

	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	SpriteRender m_spriteRender;
	Vector3 m_firstPosition;
	Vector3 m_position;

};



