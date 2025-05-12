#pragma once

#include "Level3DRender/LevelRender.h"
#include <vector>
class Player;
class GameCamera;
class BackGround;
class Enemy;
class BossEnemy;
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
class AnnoyingEnemy;
class UItukuyomi;
class UIskill;
class UISimenawa;
class UIcurseBar;
class UIheal;
class MiniMap;
class Fade;

class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();
	//オブジェクトを作成。
	void CreateObject();
	//火打石の生成。
	//轣ｫ謇鍋浹縺ｮ逕滓・縲・
	void CreateStone();
	//轣ｯ邀縺ｮ菴懈・縲・
	void CreateLantern();
	//謾ｻ謦・畑轣ｯ邀縺ｮ菴懈・縲・
	void CreateAttackLantern();
	//UI繧帝未謨ｰ蛹悶・
	void CreateUI();
	//UIのタイマー。
	void UITimer();
	//繧ｨ繝阪Α繝ｼ縺ｮ逕滓・縲・
	void CreateEnemy();
	//繧ｲ繝ｼ繝繧ｪ繝ｼ繝舌・縲√ご繝ｼ繝繧ｯ繝ｪ繧｢繝ｼ繧貞他縺ｶ髢｢謨ｰ縲・
	void GameManager();
	//本殿の方を見る。
	void LookingMain();

	void Render(RenderContext& rc);


	//メンバ変数。
	GameClear*m_gameClear;//ゲームクリアー。
	RingBell* m_ringBell;//鈴。
	BackGround* m_backGround;//背景。
	GameCamera* m_gameCamera;//ゲームカメラ。
	Player*m_player;//プレイヤー。
	Enemy* m_enemy ;//敵。
	LittleEnemy* m_littleEnemy;//小さい敵。
	BossEnemy* m_bossEnemy;//ボス。
	CrossHair*m_crossHair;//クロスヘアー。
	ModelRender m_modelRender;//モデルレンダー。
	Shimenawa* m_shimenawa;//しめ縄。
	Fade* m_fade;//フェード処理。

	Stone* m_stone1; //轣ｫ謇鍋浹
	Stone* m_stone2; //轣ｫ謇鍋浹
	Stone* m_stone3; //轣ｫ謇鍋浹
	Stone* m_stone4; //轣ｫ謇鍋浹
	Stone* m_stone5; //轣ｫ謇鍋浹
	Stone* m_stone6; //轣ｫ謇鍋浹
	Stone* m_stone7; //轣ｫ謇鍋浹

	UIStone* m_uiStone; //轣ｫ謇鍋浹縺ｮ謨ｰ

	Lantern* m_lantern1; //轣ｯ邀
	Lantern* m_lantern2; //轣ｯ邀
	Lantern* m_lantern3; //轣ｯ邀
	Lantern* m_lantern4; //轣ｯ邀

	LanternAttack* m_lanternAttack1; //謾ｻ謦・畑轣ｯ邀
	LanternAttack* m_lanternAttack2; //謾ｻ謦・畑轣ｯ邀
	LanternAttack* m_lanternAttack3; //謾ｻ謦・畑轣ｯ邀

	UItukuyomi* m_uiTukuyomi;
	UIskill* m_uiSkill;
	UISimenawa* m_uiSimenawa;
	/*MiniMap* m_miniMap;*/
	UIcurseBar* m_uiCurseBar;
	UIheal* m_uiHeal;


	SpriteRender m_spriteRender;//繧ｹ繝励Λ繧､繝医Ξ繝ｳ繝繝ｼ
	FontRender m_timerFontRender;//譎りｨ・
	Vector3 m_pos;//蠎ｧ讓・
	Vector3 Random(); //繧ｨ繝阪Α繝ｼ縺ｮ繝ｩ繝ｳ繝繝繧ｹ繝昴・繝ｳ

	//謨ｵ縺ｮ荳隕ｧ繧貞叙蠕励☆繧九◆繧√・繝｡繧ｽ繝・ラ繧貞叙蠕・
	const std::vector<Enemy*>& GetEnemies()const
	{
		return m_enemyList;
	}

	const std::vector<LittleEnemy*>& GetLittleEnemies() const
	{
		return m_littleEnemyList;
	}
	
	const std::vector<BossEnemy*>& GetBossEnemy() const
	{
		return m_bossEnemyList;
	}

	const std::vector<AnnoyingEnemy*>& GetAnnoyingEnemy() const
	{
		return m_annoyingEnemyList;
	}

	std::vector<Enemy*>   m_enemyList;
	std::vector<LittleEnemy*> m_littleEnemyList;
	std::vector<BossEnemy*> m_bossEnemyList;
	std::vector<AnnoyingEnemy*> m_annoyingEnemyList;

	int m_maxCount = 0;	//敵の最大数。
	int m_totalCount = 0;//敵の合計。
  	float m_timer = 120.0f;//タイマー。
	bool m_lanternAction = false; 
	float m_timeLimit=0;//蛻ｶ髯先凾髢・
};


