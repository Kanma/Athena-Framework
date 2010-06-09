/** @file	GameStateTask.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::GameStateTask'
*/

#include <Athena/Tasks/GameStateTask.h>
#include <Athena/GameStates/GameStateManager.h>

using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::GameStates;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

GameStateTask::GameStateTask(GameStateManager* pGameStateManager)
: m_pGameStateManager(pGameStateManager)
{
    assert(m_pGameStateManager);
}

//---------------------------------------------------------------------

GameStateTask::~GameStateTask()
{
}


/******************************** MANAGEMENT OF THE TASK *******************************/

bool GameStateTask::start()
{
	return true;
}

//---------------------------------------------------------------------

void GameStateTask::update()
{
	m_pGameStateManager->processCurrentState();
}

//---------------------------------------------------------------------

void GameStateTask::stop()
{
}
