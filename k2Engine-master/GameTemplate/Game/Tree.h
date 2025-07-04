#pragma once
class Tree :public IGameObject
{
	//メンバ関数。
public:
	Tree();
	~Tree();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//メンバ変数。
	ModelRender		m_modelRender;					//モデルレンダー。
	Vector3			m_position=Vector3::Zero;		//現在位置。
};

