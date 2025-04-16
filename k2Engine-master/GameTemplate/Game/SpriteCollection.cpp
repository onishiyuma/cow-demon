#include "stdafx.h"
#include "SpriteCollection.h"

bool SpriteCollection::Start() 
{
	
	m_spriteRender.Init("Assets/sprite/collectionButton.DDS", 600.0f, 400.0f); //‰æ‘œ‚ğ“Ç‚İ‚Ş
	m_spriteRender.SetPosition(Vector3(300.0f, -150.0f, 0.0f)); //À•W‚Ìİ’è
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); //‘å‚«‚³‚Ìİ’è
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
