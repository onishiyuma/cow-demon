#include "stdafx.h"
#include "LoadManager.h"


bool LoadManager::Star()
{
	float LoadManager::m_progress= 0.0f;
	return true;
}

LoadManager::LoadManager()
{

}

LoadManager::~LoadManager()
{

}

void LoadManager::SetProgress(float progress)
{
    m_progress = progress;
}

float LoadManager::GetProgress()
{
    return m_progress;
}

void LoadManager::Finish()
{
    m_progress = 1.0f;
    m_finished = true;
}

bool LoadManager::IsFinished()
{
    return m_finished;
}
