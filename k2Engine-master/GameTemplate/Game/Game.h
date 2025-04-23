#pragma once

#include "Level3DRender/LevelRender.h"
#include <vector>
class Player;
class GameCamera;
class BackGround;
class Enemy;
class CrossHair;
class Shimenawa;
class Stone;
class UIStone;
class Lantern;
class LanternAttack;
class RingBell;
class GameClear;
class GameOver;
class LittleEnemy;
class UItukuyomi;
class UIskill;
class UISimenawa;
class UIcurseBar;
class UIheal;
class MiniMap;

class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	void GameManager();//
	void Render(RenderContext& rc);
	Vector3 Random();
	//メンバ変数。
	GameClear*m_gameClear;//ゲームクリアー。
	RingBell* m_ringBell;//鈴。
	BackGround* m_backGround;//背景。
	GameCamera* m_gameCamera;//ゲームカメラ。
	Player*m_player;//プレイヤー。
	Enemy* m_enemy ;//敵。
	LittleEnemy* m_littleEnemy;
	CrossHair*m_crossHair;//クロスヘアー。
	ModelRender m_modelRender;//モデルレンダー。
	Shimenawa* m_shimenawa;//しめ縄。
	Stone* m_stone1; //火打石
	Stone* m_stone2; //火打石
	Stone* m_stone3; //火打石
	Stone* m_stone4; //火打石
	Stone* m_stone5; //火打石
	Stone* m_stone6; //火打石
	Stone* m_stone7; //火打石
	UIStone* m_uiStone; //火打石の数
	Lantern* m_lantern1; //灯籠
	Lantern* m_lantern2; //灯籠
	Lantern* m_lantern3; //灯籠
	Lantern* m_lantern4; //灯籠
	LanternAttack* m_lanternAttack1; //攻撃用灯籠
	LanternAttack* m_lanternAttack2; //攻撃用灯籠
	LanternAttack* m_lanternAttack3; //攻撃用灯籠
	UItukuyomi* m_uiTukuyomi;
	UIskill* m_uiSkill;
	UISimenawa* m_uiSimenawa;
	MiniMap* m_miniMap;
	UIcurseBar* m_uiCurseBar;
	UIheal* m_uiHeal;
	Vector3 m_pos;//座標。
	SpriteRender m_spriteRender;//スプライトレンダー。
	FontRender m_fontRender;//時計
	//敵の一覧を取得するためのメソッドを取得
	const std::vector<Enemy*>& GetEnemies()const { return m_enemyList; }
	const std::vector<LittleEnemy*>& GetLittleEnemies() const { return m_littleEnemyList; }

	std::vector<Enemy*>   m_enemyList;
	std::vector<LittleEnemy*> m_littleEnemyList;
	float m_timer = 120.0f;
	bool m_lanternAction = false; 
	float m_timeLimit=0;//制限時間。

};

