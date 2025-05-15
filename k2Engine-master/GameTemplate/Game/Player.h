#pragma once

class Shimenawa;
class GameCamera;
class PlayerLight;
class Lantern;
class UIheal;
class RingBell;
class GameCamera;
class BellSpriteRender;
class NoHeal;

class Player :public IGameObject
{
	
public:
	//繝｡繝ｳ繝宣未謨ｰ縲・
	Player();
	~Player();
	bool Start();
	//譖ｴ譁ｰ蜃ｦ逅・・
	void Update();
	//謠冗判蜃ｦ逅・・
	void Render(RenderContext& rc);
	//騾壼ｸｸ謾ｻ謦・
	void NormalAttack();
	//繧ｹ繧ｭ繝ｫ縲・
	void Skill();
	//譛郁ｪｭ縺ｮ蜉隴ｷ縲・
	void SkillTukuyomiBlessing();
	//縺励ａ邵・・
	void ItemShimenawa();
	//騾壼ｸｸ謾ｻ謦・・菴懈・縲・
	void MakeNormalAttack();
	//繧ｹ繧ｭ繝ｫ縺ｮ菴懈・縲・
	void MakeSkill();
    //譛郁ｩ縺ｮ蜉隴ｷ縺ｮ菴懈・縲・
    void MakeTukuyomiBlessing();
	//縺励ａ邵・・菴懈・縲・
	void MakeShimenawa();
	//遘ｻ蜍募・逅・・
	void Move();
	//繧ｹ繝・・繝育ｮ｡逅・
	void ManageState();
	//驤ｴ縺ｮ蠖薙◆繧雁愛螳壹・
	void Collision();
	//霍晞屬縺ｮ險育ｮ励・
	void Distance();
	//繧ｫ繝｡繝ｩ縺ｮ蝗櫁ｻ｢蜃ｦ逅・・
	void RotationCamera();
	//蝗槫ｾｩ逕ｨ蜃ｦ逅・・
	void HealHP(int amount);


	//蠎ｧ讓吶ｒ蜿門ｾ励☆繧矩未謨ｰ縲・
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	//蠎ｧ讓吶ｒ險ｭ螳壹☆繧矩未謨ｰ
	void SetPosition(Vector3 position)
	{
		m_position = position;
	}

	//繝｡繝ｳ繝仙､画焚
	NoHeal* m_noHeal;//
	BellSpriteRender* m_bellSpriteRender;//
	RingBell* m_ringBell;//驤ｴ縲・
	UIheal* m_uiHeal;//蝗槫ｾｩ縺ｧ縺阪ｋ繧ｲ繝ｼ繧ｸ縲・
	Lantern* m_lantern;//繝ｩ繝ｳ繧ｿ繝ｳ縲・
	GameCamera*m_gameCamera;//繧ｲ繝ｼ繝繧ｫ繝｡繝ｩ縲・
	Shimenawa* m_shimenawa;//縺励ａ邵・・
	ModelRender m_modelRender;//繝｢繝・Ν繝ｬ繝ｳ繝繝ｼ縲・
	CharacterController m_characterController;//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縲・
	FontRender m_fontRender;//繝輔か繝ｳ繝医Ξ繝ｳ繝繝ｼ縲・
	PlayerLight* m_playerLight; //繝励Ξ繧､繝､繝ｼ逕ｨ諛蝉ｸｭ髮ｻ轣ｯ
	Vector3 m_position = Vector3::Zero;//蠎ｧ讓吶・
	Vector3 m_forward = Vector3::AxisZ;//蜑肴婿蜷・
	Vector3 m_moveSpeed;//遘ｻ蜍暮溷ｺｦ縲・
	const float m_collectTime = 15.0f;//縺励ａ邵・ｒ險ｭ鄂ｮ縺ｧ縺阪ｋ譎る俣縲・
	const float m_gravity = 10.5f;//驥榊鴨繧堤匱逕溘＆縺帙ｋ縲・
	const float m_tukuyomiMax = 0.0f;//譛郁ｪｭ縺ｮ蜉隴ｷ縺ｮ繝槭ャ繧ｯ繧ｹ蛟､縲・
	const float contactThresholdSq= 100.0f * 100.0f;
	const int m_charaConRadius = 25.0f;//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺ｮ蜊雁ｾ・・
	const int m_charaConHeight = 75.0f;//繧ｭ繝｣繝ｩ繧ｳ繝ｳ縺ｮ鬮倥＆縲・
	const int m_playerATK = 5;//繝励Ξ繧､繝､繝ｼ縺ｮ謾ｻ謦・鴨縲・
	const int m_skillMax = 100;//繧ｹ繧ｭ繝ｫ繧偵メ繝｣繝ｼ繧ｸ縺ｧ縺阪ｋ繝槭ャ繧ｯ繧ｹ蛟､縲・
	const int m_skillMagnification=5;//謾ｻ謦・・蛟咲紫繧剃ｸ翫￡繧九・
	const int m_TukuyomiMagnification = 7;//譛郁ｪｭ縺ｮ蜉隴ｷ縺ｮ蛟咲紫繧定ｨｭ螳壹・
	const int m_criticalRate = 20;//莨壼ｿ・紫縲・
	const int m_cliticalDamage = 2;//莨壼ｿ・ム繝｡縲・
	float m_attackCoolDown = 0.0f;//謾ｻ謦・・繧ｯ繝ｼ繝ｫ繝繧ｦ繝ｳ縲・
	float m_tukuyomiBlessingCoolDown = 0.0f;//譛郁ｪｭ縺ｮ蜉隴ｷ縺ｮ繧ｯ繝ｼ繝ｫ繝繧ｦ繝ｳ縲・
	float m_healCoolDown = 0.0f;//蝗槫ｾｩ縺ｮ繧ｯ繝ｼ繝ｫ繧ｿ繧､繝縲・
	float m_deleteTimer=0.0f;//蜑企勁縺ｾ縺ｧ縺ｮ譎る俣縲・
	float m_shimenawaGetTime = 0.0f;//縺励ａ邵・ｒ譎る俣縺ｧ蜿門ｾ励☆繧九・
	float m_totalRotation = 0.0f;//蝗槭＠縺溷粋險亥､縲・
	float m_prevStickAngle = 0.0f;
	float m_distSq = 0.0f;
	bool m_deleteFlag = false;//蜑企勁縺吶ｋ縺九・
	bool m_enemyIsCanAttack = false;//謨ｵ繧呈判謦・〒縺阪ｋ縺具ｼ溘・
	bool m_isRotating = false;//蝗櫁ｻ｢繝輔Λ繧ｰ縲・
	int m_playerHP = 0;//繝励Ξ繧､繝､繝ｼ縺ｮHP縲・
	int m_playerMaxHP = 100;//繝励Ξ繧､繝､繝ｼ縺ｮ譛螟ｧ菴灘鴨縲・
	int m_skillCharge = 0;//繧ｹ繧ｭ繝ｫ縺ｮ繝√Ε繝ｼ繧ｸ縲・
	int m_normalATK = 0;//騾壼ｸｸ謾ｻ謦・ム繝｡繝ｼ繧ｸ縲・
	int m_criticalATK = 0;//繧ｯ繝ｪ繝・ぅ繧ｫ繝ｫ繧定・・縺励◆謾ｻ謦・・
	int m_stoneCount = 0; //轣ｫ謇鍋浹縺ｮ繧｢繧､繝・Β繧ｫ繧ｦ繝ｳ繝・
	int m_LanternCount = 0; //轣ｫ繧堤・縺励◆轣ｯ邀縺ｮ謨ｰ
	int m_skillATK = 0;//繧ｹ繧ｭ繝ｫ邱上ム繝｡繝ｼ繧ｸ縲・
	int m_tukuyomiATK = 0;//譛郁ｪｭ縺ｮ蜉隴ｷ縺ｮ邱上ム繝｡繝ｼ繧ｸ縲・
	int m_lanternCount = 0;//轣ｯ邀縺ｮ繧ｫ繧ｦ繝ｳ繝医・
};
