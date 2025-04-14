#pragma once
class BackGround : public IGameObject
{
public:
	//ƒƒ“ƒoŠÖ”
	BackGround();
	~BackGround();
	bool Start();
	void Render(RenderContext& rc);

	//ƒƒ“ƒo•Ï”
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	
};

