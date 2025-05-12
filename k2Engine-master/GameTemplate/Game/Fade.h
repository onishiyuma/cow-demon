#pragma once

class Game;

class Fade:public IGameObject
{
public:
	Fade();
	~Fade();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//次のシーンをロードする関数。
	void LoadingProgress();


	SpriteRender m_spriteLoad;
	SpriteRender m_spriteLoadGage; // ロードゲージ用スプライト
	SpriteRender m_spriteMask;//マスクを動かす。
	Game* m_game = nullptr;//ゲーム。

	float m_alpha = 1.0f; // フェード用アルファ値。
	bool m_isFadingOut = true; // 最初は暗くする。
	float m_loadingProgress = 0.0f; // ロード進行状況。
	bool m_drawUI = false;//UIを表示するか？。
};

