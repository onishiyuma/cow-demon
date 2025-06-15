#pragma once

class Title;
class Load;
class Tutorial;
class Game;

//title,Load,Tutorial,Gameの流れを管理するクラス
class GameManagement:public IGameObject
{
public:
	//メンバ関数
	GameManagement();
	~GameManagement();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
	bool m_isGame = false;
	bool m_isTutorial = false;




	Title* m_title = nullptr;//タイトル画面
	Load* m_load = nullptr;//ロード画面
	Tutorial* m_tutorial = nullptr;//ゲームのチュートリアル
	Game* m_game = nullptr;//ゲーム

};

