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
	//描画処理
	void Render(RenderContext& rc);

	//メンバ変数
	ModelRender m_modelRender;
	Vector3 m_firstPosition; //最初の座標
	Vector3 m_position;
	SoundSource* m_bgm; //効果音
	Player* m_player ; //プレイヤー
	SpriteCollection* m_spriteCollection;//「A：採る」の画像
	
	

	bool m_collectionFlag = false;//火打石の近くにいるか？
};

