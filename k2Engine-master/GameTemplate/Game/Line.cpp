#include "stdafx.h"
#include "Line.h"
#include "Lantern.h"

Line::Line() 
{

}

Line::~Line()
{

}

bool Line::Start() 
{
	//画像を読み込む。
	m_spriteRender.Init("Assets/sprite/line.DDS", 600.0f, 400.0f); 
	//座標の設定。
	m_spriteRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f)); 
	//大きさの設定。
	m_spriteRender.SetScale({ 1.0f,1.0f,1.0f }); 
	m_spriteRender.Update();

	//各種インスタンスアドレスを検索。
	m_lantern1 = FindGO<Lantern>("lantern1");
	m_lantern2 = FindGO<Lantern>("lantern2");
	m_lantern3 = FindGO<Lantern>("lantern3");
	m_lantern4 = FindGO<Lantern>("lantern4");

	return true;
}

void Line::Move()
{
	//moveStateが0の時。
	if (m_directionState == 0)
	{
			//右に移動する。
			m_position.x += 10.0f;
	}
	//moveStateが1の時。
	else if (m_directionState == 1)
	{
		//左に移動する。
		m_position.x -= 10.0f;
	}

	//y座標が初期座標y+100.0fを超えたら。
	if (m_position.x >= m_firstPosition.x + 400.0f)
	{
		//moveStateを1にする(下に移動するようにする)。
		m_directionState = 1;
	}
	//y座標が初期座標-100.0fより下になったら。
	else if (m_position.x <= m_firstPosition.x - 400.0f)
	{
		//moveStateを0にする(上に移動するようにする)。
		m_directionState = 0;
	}

	//座標設定。
	m_spriteRender.SetPosition(m_position);
	//画像を更新。
	m_spriteRender.Update();
}

void Line::Update()
{
	Move();
	//if (m_lantern1->m_buttonAState == 1 or m_lantern2->m_buttonAState == 1 or m_lantern3->m_buttonAState == 1 or m_lantern4->m_buttonAState == 1) {

		//if (m_moving == false) {

			/*while (m_moving==true) {

					Move();
					m_spriteRender.SetPosition(m_position);
					m_spriteRender.Update();

				if (m_lantern1->m_buttonAState == 0 or m_lantern2->m_buttonAState == 0 or m_lantern3->m_buttonAState == 0 or m_lantern4->m_buttonAState == 0) {
					m_spriteRender.SetPosition(m_position);
					m_spriteRender.Update();
					break;
				}
			}*/
		//}

	//}
}

void Line::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}