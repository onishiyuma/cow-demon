#include "stdafx.h"
#include "SpriteCollection.h"

bool SpriteCollection::Start() 
{
	
	m_spriteRender.Init("Assets/sprite/collectionButton.DDS", 600.0f, 400.0f); //‰æ‘œ‚ğ“Ç‚İ‚Ş
	m_spriteRender.SetPosition(Vector3(300.0f, 0.0f, 0.0f)); //À•W‚Ìİ’è
	m_spriteRender.SetScale({ 10.0f,10.0f,10.0f }); //‘å‚«‚³‚Ìİ’è

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

}

void SpriteCollection::Render(RenderContext& rc) 
{
	m_spriteRender.Draw(rc);
}
