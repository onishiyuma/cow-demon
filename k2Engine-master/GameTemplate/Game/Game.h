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
	//繧ｨ繝阪Α繝ｼ縺ｮ逕滓・縲・
	void CreateEnemy();
	//繧ｲ繝ｼ繝繧ｪ繝ｼ繝舌・縲√ご繝ｼ繝繧ｯ繝ｪ繧｢繝ｼ繧貞他縺ｶ髢｢謨ｰ縲・
	void GameManager();

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
	//繝｡繝ｳ繝仙､画焚縲・
	GameClear*m_gameClear;//繧ｲ繝ｼ繝繧ｯ繝ｪ繧｢繝ｼ縲・
	RingBell* m_ringBell;//驤ｴ縲・
	BackGround* m_backGround;//閭梧勹縲・
	GameCamera* m_gameCamera;//繧ｲ繝ｼ繝繧ｫ繝｡繝ｩ縲・
	Player*m_player;//繝励Ξ繧､繝､繝ｼ縲・
	Enemy* m_enemy ;//謨ｵ縲・
	LittleEnemy* m_littleEnemy;
	CrossHair*m_crossHair;//繧ｯ繝ｭ繧ｹ繝倥い繝ｼ縲・
	ModelRender m_modelRender;//繝｢繝・Ν繝ｬ繝ｳ繝繝ｼ縲・
	Shimenawa* m_shimenawa;//縺励ａ邵・・

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

	std::vector<Enemy*>   m_enemyList;
	std::vector<LittleEnemy*> m_littleEnemyList;
	std::vector<BossEnemy*>m_BossEnemyList;

	//敵の最大数
	int m_maxCount = 0;
	int m_totalCount = 0;
  	float m_timer = 120.0f;
	bool m_lanternAction = false; 
	float m_timeLimit=0;//蛻ｶ髯先凾髢・

};

