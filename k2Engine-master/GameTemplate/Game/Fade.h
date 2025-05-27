#pragma once

class Game;

class Fade : public IGameObject
{
public:
	//メンバ関数。
	Fade();
	~Fade();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// フェード中かどうか。
	/// </summary>
	/// <returns>フェードの状態。</returns>
	bool isFade() const
	{
		if (m_load > 0.0f)
		{
			return true;
		}
		return false;
	}

private:
	/// <summary>
	/// 次のシーンをロードする関数。
	/// </summary>
	void LoadingProgress();
	//ヒントを表示する
	void Tips();

private:
	//メンバ変数。
	std::vector<std::wstring> tipsList;				//表示するtipsを入れる可変長配列。
	Game*				m_game = nullptr;			//ゲームのインスタンス。
	SpriteRender		m_spriteLoad;				//ロードの画像。
	SpriteRender		m_spriteLoadGage;			//ロードゲージ用スプライト。
	SpriteRender		m_spriteMask;				//マスクを動かす。
	FontRender			m_fontRenderTips;			//フォントレンダー。

	const float			m_tipInterval = 3.4f;		//ヒントの表示間隔。
	float				m_tipTimer = 0.0f;			//ヒントの表示時間。
	float				m_loadingProgress = 0.0f;	//ロード進行状況。
	float				m_load = 1.0f;				//フェード用アルファ値。
	int					m_currentTipIndex = 0;		//現在のヒントのインデックス。
	bool				m_isFadingOut = true;		//最初は暗くする。
	bool				m_drawUI = false;			//UIを表示するか。
};