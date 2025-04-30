#include "stdafx.h"
#include "SpriteCollection.h"

bool SpriteCollection::Start() 
{
	
	m_spriteRender.Init("Assets/sprite/collectionButton.DDS", 600.0f, 400.0f); //画像を読み込む
	m_spriteRender.SetPosition(Vector3(300.0f, -150.0f, 0.0f)); //座標の設定
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); //大きさの設定
	m_spriteRender.Update();

	return true;

}

SpriteCollection::SpriteCollection()
{

}

SpriteCollection::~SpriteCollection() 
{

}

void SpriteCollection::Update() 
{
	m_spriteRender.SetPosition(m_position);
}

void SpriteCollection::Render(RenderContext& rc) 
{
	m_spriteRender.Draw(rc);
}
