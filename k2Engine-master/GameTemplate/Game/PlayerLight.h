#pragma once

class Player;

class PlayerLight:public IGameObject
{
public:
	//メンバ関数
	PlayerLight();
	~PlayerLight();
	bool Start();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_position; //ライトの座標
	Vector3 m_direction; //ライトの向き
	Player* m_player; //プレイヤー
	SpotLight m_spotLight; //スポットライト
};

