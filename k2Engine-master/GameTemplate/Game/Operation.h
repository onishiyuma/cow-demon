#pragma once

class GameManagement;
class Title;

class Operation:public IGameObject
{
public:
	//メンバ関数
	Operation();
	~Operation();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_position; // 位置
	SpriteRender m_operationController; // コントローラーの説明
	SpriteRender m_operationPlayer; // プレイヤーのスキル説明

	GameManagement* m_gameManagement = nullptr; // ゲーム管理クラスへのポインタ
	Title* m_title = nullptr; // タイトルクラスへのポインタ

	int m_count = 0;// ボタン押した回数

	bool m_isController = false; // コントローラーの説明を表示しているか
	bool m_isPlayer = false; // プレイヤーのスキル説明を表示しているか

};

