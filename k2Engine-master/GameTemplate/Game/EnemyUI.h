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

	// Enemyポインタ取得
	Enemy* GetEnemy() const { return m_enemy; }
	LittleEnemy* GetLittleEnemy() const { return m_littleEnemy; }
	AnnoyingEnemy* GetAnnoyingEnemy() const { return m_annoyingEnemy; }
	BossEnemy* GetBossEnemy() const { return m_bossEnemy; }

	// ペアを切断する関数
	void UnlinkEnemy() { m_enemy = nullptr; }
	void UnlinkLittleEnemy() { m_littleEnemy = nullptr; }
	void UnlinkAnnoyingEnemy() { m_annoyingEnemy = nullptr; }
	void UnlinkBossEnemy() { m_bossEnemy = nullptr; }

private:
	Enemy* m_enemy = nullptr;
	LittleEnemy* m_littleEnemy = nullptr;
	AnnoyingEnemy* m_annoyingEnemy = nullptr;
	BossEnemy* m_bossEnemy = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera;

	SpriteRender m_HPSprite;
	SpriteRender m_HPFreamSprite;

	Vector2 m_position = Vector2::Zero;
	Vector3 m_scale = { 1.0f,1.0f,1.0f };
};

