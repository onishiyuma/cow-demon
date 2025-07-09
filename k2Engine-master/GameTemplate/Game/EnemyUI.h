#pragma once
class Enemy;
class LittleEnemy;
class AnnoyingEnemy;
class BossEnemy;
class Player;
class Game;
class GameCamera;

class EnemyUI :public IGameObject, Noncopyable
{
public:
	EnemyUI();
	~EnemyUI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Scale();
	void Position();

	void SetEnemy(Enemy* enemy);
	void SetLittleEnemy(LittleEnemy* littleEnemy);
	void SetAnnoyingEnemy(AnnoyingEnemy* annoyingEnemy);
	void SetBossEnemy(BossEnemy* bossEnemy);
	Vector3 SendHPBer(Vector3 size, Vector3 scale);

	template<class T>

	bool Angle(T Enemy);

	// Enemy各種のポインタ取得。
	Enemy* GetEnemy() const 
	{
		return m_enemy; 
	}

	LittleEnemy* GetLittleEnemy() const 
	{
		return m_littleEnemy;
	}

	AnnoyingEnemy* GetAnnoyingEnemy() const
	{
		return m_annoyingEnemy;
	}

	BossEnemy* GetBossEnemy() const
	{
		return m_bossEnemy; 
	}

	// ペアを切断する関数
	void UnlinkEnemy() 
	{
		m_enemy = nullptr;
	}

	void UnlinkLittleEnemy() 
	{
		m_littleEnemy = nullptr;
	}

	void UnlinkAnnoyingEnemy()
	{
		m_annoyingEnemy = nullptr;
	}

	void UnlinkBossEnemy()
	{
		m_bossEnemy = nullptr;
	}

private:
	Enemy*				m_enemy = nullptr;				//敵。
	LittleEnemy*		m_littleEnemy = nullptr;		//小さい敵。
	AnnoyingEnemy*		m_annoyingEnemy = nullptr;		//ウザイ敵。
	BossEnemy*			m_bossEnemy = nullptr;			//ボス。
	Player*				m_player = nullptr;				//プレイヤー。
	Game*				m_game = nullptr;				//ゲーム。
	GameCamera*			m_gameCamera;					//ゲームカメラ。
	SpriteRender		m_HPSprite;						//HPの画像。
	SpriteRender		m_HPFreamSprite;				//HPのフレーム。
	Vector2				m_position = Vector2::Zero;		//ポジション。
	Vector3				m_scale = Vector3::One;			//大きさ。
};

