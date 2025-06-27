#pragma once

class Game;
class Tutorial;
class GameManagement;

class Load : public IGameObject
{
public:
	//メンバ関数。
	Load();
	~Load();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// フェード中かどうか。
	/// </summary>
	/// <returns>フェードの状態。</returns>
	bool isLoad() const
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
	std::vector<SpriteRender*>tipsList;				//Tipsのリスト。
	Game*				m_game = nullptr;			//ゲームのインスタンス。
	Tutorial*           m_tutorial = nullptr;		//チュートリアル。
	GameManagement*		m_gameManagement = nullptr;	// ゲーム管理。
	SpriteRender		m_spriteLoad;				//ロードの画像。
	SpriteRender		m_spriteLoad_1;				//ロードの画像。
	SpriteRender		m_spriteLoad_2;				//ロードの画像。
	SpriteRender		m_spriteLoad_3;				//ロードの画像。
	SpriteRender		m_spriteLoadGage;			//ロードゲージ用スプライト。
	SpriteRender		m_spriteMask;				//マスクを動かす。
	const float			m_tipsInterval = 2.5f;		//ヒントの表示間隔。
	float				m_tipTimer = 0.0f;			//ヒントの表示時間。
	float				m_loadingProgress = 0.0f;	//ロード進行状況。
	float				m_load = 1.0f;				//フェード用アルファ値。
	int					m_currentTipsIndex = 0;		//現在のヒントのインデックス。
	bool				m_isLoading = true;			//最初は暗くする。
	bool				m_isdrawUI = false;			//UIを表示するか。
};