#pragma once



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
	//通常攻撃の作成。
	void MakeNormalAttack();
	//スキルの作成。
	void MakeSkill();
    //月詠の加護の作成。
    void MakeTukuyomiBlessing();
	//移動処理。
	void Move();
	//ステート管理
	void ManageState();


	//座標を取得する関数。
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//メンバ変数
	ModelRender m_modelRender;//モデルレンダー。
	CharacterController m_characterController;//キャラコン。
	Vector3 m_position = Vector3::Zero;//座標。
	Vector3 m_forward = Vector3::AxisZ;//前方向
	Vector3 m_moveSpeed;//移動速度。
	const int m_charaConRadius = 25.0f;//キャラコンの半径。
	const int m_charaConHeight = 75.0f;//キャラコンの高さ。
	const int m_playerATK = 5;//プレイヤーの攻撃力。
	const int m_skillMagnification=5;//攻撃の倍率を上げる。
	const int m_TukuyomiMagnification = 7;//月読の加護の倍率を設定。
	const int m_criticalRate = 10;//会心率。
	const int m_cliticalDamage = 2;//会心ダメ。
	float m_attackCoolDown = 0.0f;//攻撃のクールダウン。
	float m_tukuyomiBlessingCoolDown = 0.0f;//月読の加護のクールダウン。
	int m_playerHP = 0;//プレイヤーのHP。
	int m_skillCharge = 0;//スキルのチャージ。
	int m_normalATK=0;//通常攻撃ダメージ。
	int m_criticalATK = 0;//クリティカルを考慮した攻撃。
	int m_skillATK=0;//スキル総ダメージ。
	int m_TukuyomiATK;//月読の加護の総ダメージ。
	bool m_enemyIsCanAttack=false;//敵を攻撃できるか？
};
