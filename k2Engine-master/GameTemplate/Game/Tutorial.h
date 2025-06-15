#pragma once

class GameManagement;
class GameCamera;
class Player;
class Enemy;
class BackGround;
class CrossHair;
class UItukuyomi;
class UIskill;
class UISimenawa;
class UIcurseBar;
class UIheal;
class SpriteAttack;
class SpriteSkil;
class SpriteSimenawa;
class SpriteTukuyomi;
class SpriteClear;
class Load;
class Title;

class Tutorial:public IGameObject
{
public:
	//メンバ関数
	Tutorial();
	~Tutorial();
	bool Start();
	void Update();
	void CreateUI();
	void Font();
	void ButtonUI();
	void State();
	void NormalAttack();
	void Skill();
	void Simenawa();
	void Protection();
	void End();
	void Render(RenderContext& rc);

	//メンバ変数
	int m_clearCount = 0;//チュートリアルの項目クリアカウント

	float m_timer = 0.0f;
	float m_endTimer = 0.0f;
	
	bool m_isClear = false;//項目をクリアしたか
	bool m_isSprite = false;//説明の画像を出力するか
	bool m_isClearSprite = false;//クリアの画像を出力するか
	bool m_isEnd = false;//チュートリアルを終了するか
	bool m_isLoad = true;

	Vector3 m_backPos = { 0.0f,0.0f,0.0f };
	Vector3 m_enemyPos = { 0.0f,10.0f,1000.0f };

	//チュートリアル項目のカウント
	FontRender                m_fontClearCount;
	FontRender                m_fontClearCount1;

	//それぞれの項目のミッション
	FontRender                m_nomalAttack;
	FontRender                m_skill;
	FontRender                m_simenawa;
	FontRender				  m_tukuyomi;

	//チュートリアル終了用文字
	FontRender                m_tutorialEnd;

	//ボタンUIの表示
	FontRender                m_skip;
	SpriteRender              m_bButton;
	FontRender                m_fontNomalAttack;
	SpriteRender              m_xButton;
	SpriteRender              m_yButton;
	SpriteRender              m_ltButton;
	SpriteRender              m_rtButton;

	SkyCube*                  m_skyCube;            //スカイキューブ      
	GameManagement*           m_gameManagement;     //ゲーム全体を管理するマネージャー
	GameCamera*               m_gameCamera;         //ゲームカメラ
	Player*                   m_player;             //プレイヤー
	Enemy*                    m_enemy;              //牛鬼
	BackGround*               m_backGround;         //ステージ
	CrossHair*                m_crossHair;          //クロスヘアー
	UItukuyomi*               m_uiTukuyomi;         //ツクヨミの加護
	UIskill*                  m_uiSkill;            //スキル
	UISimenawa*               m_uiSimenawa;         //しめ縄
	UIcurseBar*               m_uiCurseBar;         //呪いゲージ
	UIheal*                   m_uiHeal;             //回復ゲージ
	SpriteAttack*             m_spriteAttack;       //通常攻撃の説明画像
	SpriteSkil*               m_spriteSkil;         //スキルの説明画像
	SpriteSimenawa*           m_spriteSimenawa;     //しめ縄の説明画像
	SpriteTukuyomi*           m_spriteTukuyomi;     //ツクヨミの加護の説明画像
	SpriteClear*              m_spriteClear;        //項目クリア用の画像
	Load*                     m_load;               //ロード画面
	Title*                    m_title;              //タイトル画面
};

