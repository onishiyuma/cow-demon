#pragma once

class Player;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	
	void LockCamera(bool isLock) 
	{ 
		m_isLocked = isLock;
	}

	//繝｡繝ｳ繝仙､画焚縲・
	Player* m_player;//繝励Ξ繧､繝､繝ｼ縲・
	Vector3 m_toCameraPos;//豕ｨ隕也せ縺九ｉ隕也せ縺ｫ蜷代°縺・・繧ｯ繝医Ν縲・
	float m_nearClip = 1.0f;//繝九い繝ｼ繧ｯ繝ｪ繝・・
	float m_furClip = 20000.0f;//繝輔ぃ繝ｼ繧ｯ繝ｪ繝・・
	const int m_half=2;//蜊雁・縺ｫ縺吶ｋ
	bool m_isLocked = false;//繧ｫ繝｡繝ｩ繧貞●豁｢縺吶ｋ繧医≧繝輔Λ繧ｰ縲・
};

