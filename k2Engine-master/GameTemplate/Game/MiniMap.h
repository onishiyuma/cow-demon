#pragma once

class Player;
class Enemy;

class MiniMap:public IGameObject
{
public:
	MiniMap();
	~MiniMap();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);
private:

	const bool WouldPositionConvertToMapPosition(Vector3 wourdCenterPosition, Vector3 wourdPosition, Vector3& mapPosition);
	SpriteRender m_spriteRender;
	SpriteRender m_playerSprite;
	SpriteRender m_enemySprite;

	Enemy* m_enemy = nullptr;
	Player* m_player = nullptr;
	bool m_isImage = false;

};

