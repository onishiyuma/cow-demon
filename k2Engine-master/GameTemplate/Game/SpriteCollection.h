#pragma once
class SpriteCollection:public IGameObject
{
public:
	//メンバ関数
	SpriteCollection();
	~SpriteCollection();

	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	SpriteRender m_spriteRender;

};

