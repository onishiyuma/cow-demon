#pragma once

class Shimenawa;
class GameCamera;
class Lantern;
class UIheal;
class RingBell;
class GameCamera;

class Player:public IGameObject
{
public:
	//メンバ関数。
	Player();
	~Player();

	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//通常攻撃
	void NormalAttack();
	//スキル。
	void Skill();
	//月読の加護。
	void SkillTukuyomiBlessing();
	//しめ縄。
	void ItemShimenawa();
	//通常攻撃の作成。
	void MakeNormalAttack();
	//スキルの作成。
	void MakeSkill();
    //月詠の加護の作成。
    void MakeTukuyomiBlessing();
	//しめ縄の作成。
	void MakeShimenawa();
	//移動処理。
	void Move();
	//ステート管理
	void ManageState();
	//鈴の当たり判定。
	void Collision();
	//距離の計算。
	void Distance();
	//カメラの回転処理。
	void RotationCamera();
	//回復用処理。
	void HealHP(int amount);


	//座標を取得する関数。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//座標を設定する関数
	void SetPosition(Vector3 position)
	{
		m_position = position;
	}


	//メンバ変数
	RingBell* m_ringBell;//鈴。
	UIheal* m_uiHeal;//回復できるゲージ。
	Lantern* m_lantern;//ランタン。
	GameCamera*m_gameCamera;//ゲームカメラ。
	Shimenawa* m_shimenawa;//しめ縄。
	ModelRender m_modelRender;//モデルレンダー。
	CharacterController m_characterController;//キャラコン。
	FontRender m_fontRender;//フォントレンダー。

	Vector3 m_position = Vector3::Zero;//座標。
	Vector3 m_forward = Vector3::AxisZ;//前方向
	Vector3 m_moveSpeed;//移動速度。
	const float m_collectTime = 15.0f;//しめ縄を設置できる時間。
	const float m_gravity = 10.5f;//重力を発生させる。
	const float m_tukuyomiMax = 0.0f;//月読の加護のマックス値。
	const float contactThresholdSq= 100.0f * 100.0f;
	const int m_charaConRadius = 25.0f;//キャラコンの半径。
	const int m_charaConHeight = 75.0f;//キャラコンの高さ。
	const int m_playerATK = 5;//プレイヤーの攻撃力。
	const int m_skillMax = 100;//スキルをチャージできるマックス値。
	const int m_skillMagnification=5;//攻撃の倍率を上げる。
	const int m_TukuyomiMagnification = 7;//月読の加護の倍率を設定。
	const int m_criticalRate = 20;//会心率。
	const int m_cliticalDamage = 2;//会心ダメ。
	float m_attackCoolDown = 0.0f;//攻撃のクールダウン。
	float m_tukuyomiBlessingCoolDown = 0.0f;//月読の加護のクールダウン。
	float m_healCoolDown = 0.0f;//回復のクールタイム。
	float m_deleteTimer=0.0f;//削除までの時間。
	float m_shimenawaGetTime = 0.0f;//しめ縄を時間で取得する。
	float m_totalRotationRotation = 0.0f;//回した合計値。
	float m_prevStickAngle = 0.0f;
	float distSq = 0.0f;
	bool m_deleteFlag = false;//削除するか。
	bool m_enemyIsCanAttack = false;//敵を攻撃できるか？。
	bool m_isRotating = false;//回転フラグ。
	int m_playerHP = 0;//プレイヤーのHP。
	int m_playerMaxHP = 100;//プレイヤーの最大体力。
	int m_skillCharge = 0;//スキルのチャージ。
	int m_normalATK = 0;//通常攻撃ダメージ。
	int m_criticalATK = 0;//クリティカルを考慮した攻撃。
	int m_stoneCount = 0; //火打石のアイテムカウント
	int m_LanternCount = 0; //火を灯した灯籠の数
	int m_skillATK = 0;//スキル総ダメージ。
	int m_tukuyomiATK = 0;//月読の加護の総ダメージ。
	int m_lanternCount = 0;//灯籠のカウント。
};
