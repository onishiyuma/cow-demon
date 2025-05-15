#pragma once

#pragma once
class BellSpriteRender :public IGameObject
{
public:
	//メンバ関数
	BellSpriteRender();
	~BellSpriteRender();

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



