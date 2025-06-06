#pragma once
class Mountain:public IGameObject
{
	//メンバ関数
public:	
	Mountain();
	~Mountain();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//メンバ変数
	Vector3 m_firstPosition = Vector3::Zero; // 初期位置
	Vector3 m_position; // 現在位置

	ModelRender m_modelRender; // モデルレンダラー

};

