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
class LanternLight;
class LanternAttackLight;
class BlueFlame;
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
class EnemyUI;
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
	//灯籠用ライトのステート
	void LanternLightState();
	//灯籠用ライトの作成
	void CreateLanternLight();
	//灯籠用エフェクトの作成
	void CreateLanternEffect();
	//攻撃灯籠用ライトのステート
	void LanternAttackLightState();
	//攻撃灯籠用ライトの作成
	void CreateLanternAttackLight();
	//本殿の方を見る。
	void LookingMain();
	//空の明るさ調整用関数。
	void SetSkyLight();
  
	void Render(RenderContext& rc);


	//メンバ変数。
	GameClear*m_gameClear;//ゲームクリアー。
	RingBell* m_ringBell;//鈴。
	BackGround* m_backGround;//背景。
	GameCamera* m_gameCamera;//ゲームカメラ。
	Player*m_player;//プレイヤー。
	Enemy* m_enemy ;//敵。
	LittleEnemy* m_littleEnemy;//小さい敵。
	AnnoyingEnemy* m_annoyingEnemy;
	BossEnemy* m_bossEnemy;//ボス。
	CrossHair*m_crossHair;//クロスヘアー。
	ModelRender m_modelRender;//モデルレンダー。
	Shimenawa* m_shimenawa;//しめ縄。
	Fade* m_fade;//フェード処理。
	EnemyUI*m_enemyUI;
	SkyCube* m_skyCube;//スカイクラブ。

	Stone* m_stone1; //轣ｫ謇鍋浹
	Stone* m_stone2; //轣ｫ謇鍋浹
	Stone* m_stone3; //轣ｫ謇鍋浹
	Stone* m_stone4; //轣ｫ謇鍋浹
	Stone* m_stone5; //轣ｫ謇鍋浹
	Stone* m_stone6; //轣ｫ謇鍋浹
	Stone* m_stone7; //轣ｫ謇鍋浹

	UIStone* m_uiStone; //轣ｫ謇鍋浹縺ｮ謨ｰ

	Lantern* m_lantern;
	Lantern* m_lantern1; //轣ｯ邀
	Lantern* m_lantern2; //轣ｯ邀
	Lantern* m_lantern3; //轣ｯ邀
	Lantern* m_lantern4; //轣ｯ邀

	LanternLight* m_lanternLight1;
	LanternLight* m_lanternLight2;
	LanternLight* m_lanternLight3;
	LanternLight* m_lanternLight4;

	BlueFlame* m_blueFlame1;
	BlueFlame* m_blueFlame2;
	BlueFlame* m_blueFlame3;
	BlueFlame* m_blueFlame4;

	LanternAttack* m_lanternAttack1; //謾ｻ謦・畑轣ｯ邀
	LanternAttack* m_lanternAttack2; //謾ｻ謦・畑轣ｯ邀
	LanternAttack* m_lanternAttack3; //謾ｻ謦・畑轣ｯ邀

	LanternAttackLight* m_lanternAttackLight1;
	LanternAttackLight* m_lanternAttackLight2;
	LanternAttackLight* m_lanternAttackLight3;

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
	int m_lanternLightState = 0;
	int m_lanternEffectState = 0;
	int m_lanternAttackLightState = 0;
	float m_skyLuminance = 0.0002f; //空の明るさ。
	float m_skyAmbient = 0.0002f; //空の明るさの影響を受ける環境光。
	//灯籠用ライトのフラグ
	bool m_lanternLightFlag1 = false;
	bool m_lanternLightFlag2 = false;
	bool m_lanternLightFlag3 = false;
	bool m_lanternLightFlag4 = false;
	//灯籠用エフェクトのフラグ
	bool m_lanternEffectFlag1 = false;
	bool m_lanternEffectFlag2 = false;
	bool m_lanternEffectFlag3 = false;
	bool m_lanternEffectFlag4 = false;
	//攻撃灯籠用ライトのフラグ
	bool m_lanternAttackLightFlag1 = false;
	bool m_lanternAttackLightFlag2 = false;
	bool m_lanternAttackLightFlag3 = false;
	//空の明るさのフラグ
	bool m_isNight = false;
	bool m_isMidNight1 = false;
	bool m_isMidNight2 = false;
	bool m_isSunrise = false;
	bool m_isDawn1 = false;
	bool m_isDawn2 = false; 
	bool m_isDawn3 = false;
	bool m_isDay = false;

	float m_luminance = 0.0f; //空の明るさの変化量。

	const float m_nightStart = 0.0f;
	const float m_phase1Start = 120.0f;  // 夜明けの始まり
	const float m_phase2Start = 180.0f;  // 少し明るくなる
	const float m_phase3Start = 210.0f;  // 少し明るくなる
	const float m_phase4Start = 240.0f;  // 日の出開始
	const float m_phase5Start = 250.0f;  // 少しずつ明ける
	const float m_phase6Start = 260.0f;  // 少しずつ明ける
	const float m_phase7Start = 270.0f;  // 少しずつ明ける
	const float m_dayStart = 290.0f;     // 朝になる

	const float m_luminanceNight = 0.0003f;       // 夜の明るさ
	const float m_luminanceMidNight1 = 0.0005f;   // 夜の明るさ
	const float m_luminanceMidNight2 = 0.001f;     // 夜の明るさ
	const float m_luminanceSunrise = 0.0075f;       // 日の出
	const float m_luminanceDawn1 = 0.05f;          // 夜明け
	const float m_luminanceDawn2 = 0.1f;          // 夜明け
	const float m_luminanceDawn3 = 0.5f;          // 夜明け
	const float m_luminanceDay = 1.0f;            // 朝（最大）

};


