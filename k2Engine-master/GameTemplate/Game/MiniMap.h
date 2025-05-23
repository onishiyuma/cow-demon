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
	//マップの座標を設定する。
	const bool WouldPositionConvertToMapPosition(Vector3 wourdCenterPosition, Vector3 wourdPosition, Vector3& mapPosition);	
	
	//メンバ変数。
	Enemy*			m_enemy = nullptr;		//敵。
	Player*			m_player = nullptr;		//プレイヤー。
	SpriteRender	m_spriteRender;			//マップの画像。
	SpriteRender	m_playerSprite;			//プレイヤーの画像。
	SpriteRender	m_enemySprite;			//敵の画像。

	bool			m_isImage = false;		//画像を表示するかどうか。

};

