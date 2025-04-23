#pragma once
#include "sound/SoundSource.h"

class Player;
class SpriteCollection;

class Stone: public IGameObject
{
public:
	//メンバ関数	
	Stone();
	~Stone();


	bool Start();
	//移動処理
	void Move();
	//更新処理
	void Update();
	//コリジョンの作成。
	//void CreateCollision();
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	ModelRender m_modelRender;
	Vector3 m_firstPosition; //最初の座標
	Vector3 m_position;
	SoundSource* m_bgm; //効果音
	Player* m_player ; //プレイヤー
	SpriteCollection* m_spriteCollection;//「A：採る」の画像
	//PhysicsStaticObject m_physicsStaticObject;
	//CollisionObject* m_collisionObject;//コリジョン
	//Vector3 m_position = Vector3{ 0.0f, 95.0f, -1325.0f };//座標。
	//const Vector3 m_collisionScale = Vector3{ 400.0f,50.0f,190.0f };//コリジョンの大きさ。
	bool m_collectionFlag = false;//火打石の近くにいるか？
};

