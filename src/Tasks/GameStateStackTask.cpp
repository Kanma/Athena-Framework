/** @file	GameStateStackTask.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::GameStateStackTask'
*/

#include <Athena/Tasks/GameStateStackTask.h>
#include <Athena/GameStates/GameStateManager.h>

using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::GameStates;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

GameStateStackTask::GameStateStackTask(GameStateManager* pGameStateManager)
: m_pGameStateManager(pGameStateManager)
{
    assert(m_pGameStateManager);
}

//---------------------------------------------------------------------

GameStateStackTask::~GameStateStackTask()
{
}


/******************************** MANAGEMENT OF THE TASK *******************************/

bool GameStateStackTask::start()
{
	return true;
}

//---------------------------------------------------------------------

void GameStateStackTask::update()
{
	m_pGameStateManager->update();
}

//---------------------------------------------------------------------

void GameStateStackTask::stop()
{
}
