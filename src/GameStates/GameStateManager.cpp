/** @file	GameStateManager.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::GameStates::CGameStateManager'
*/

#include <Athena/GameStates/GameStateManager.h>
#include <Athena/Tasks/TaskManager.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Utils/StringConverter.h>
#include <Ogre/OgreException.h>

using namespace Athena;
using namespace Athena::GameStates;
using namespace Athena::Tasks;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*	__CONTEXT__ = "Game's State Manager";


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

GameStateManager::GameStateManager()
: m_command(COMMAND_NONE), m_pTaskManager(0)
{
	ATHENA_LOG_EVENT("Creation");
}

//---------------------------------------------------------------------

GameStateManager::~GameStateManager()
{
	ATHENA_LOG_EVENT("Destruction");

	// Clean up all the states
	while (!m_stack.empty())
	{
		m_stack.top()->exit();
		m_stack.pop();
	}

	while (!m_states.empty())
	{
		delete m_states.begin()->second;
		m_states.erase(m_states.begin());
	}
}


/******************************* MANAGEMENT OF THE STATES ******************************/

bool GameStateManager::registerState(tID ID, IGameState* pState)
{
	ATHENA_LOG_EVENT("Register a game state with the ID " + StringConverter::toString(ID));

	// Check that the ID isn't already used
	if (m_states.find(ID) != m_states.end())
	{
		ATHENA_LOG_ERROR("Failed to register the game state, the ID is already used");
		delete pState;
		return false;
	}

	// Add the state in the list
	m_states[ID] = pState;
	
	return true;
}

//---------------------------------------------------------------------

void GameStateManager::changeState(tID ID)
{
	// Check that the state exists
	if (m_states.find(ID) == m_states.end())
		return;

	m_command = COMMAND_CHANGE;
	m_ID = ID;
}

//---------------------------------------------------------------------

void GameStateManager::pushState(tID ID)
{
	// Check that the state exists
	if (m_states.find(ID) == m_states.end())
		return;

	m_command = COMMAND_PUSH;
	m_ID = ID;

	if (m_stack.empty())
		update();
}

//---------------------------------------------------------------------

void GameStateManager::popState()
{
	assert(!m_stack.empty());

	m_command = COMMAND_POP;
}

//---------------------------------------------------------------------

void GameStateManager::popAllStates(bool bKillAllTasks)
{
	m_command = (bKillAllTasks ? COMMAND_POP_ALL_KILL : COMMAND_POP_ALL);
}

//---------------------------------------------------------------------

void GameStateManager::processCurrentState()
{
	if (m_stack.empty())
		return;

	m_stack.top()->process();
}

//---------------------------------------------------------------------

void GameStateManager::update()
{
	switch (m_command)
	{
	case COMMAND_NONE:			return;
	case COMMAND_CHANGE:		doChangeCommand(); break;
	case COMMAND_PUSH:			doPushCommand(); break;
	case COMMAND_POP:			doPopCommand(); break;
	case COMMAND_POP_ALL_KILL:	doPopAllCommand(true); break;
	case COMMAND_POP_ALL:		doPopAllCommand(false); break;
	}

	m_command = COMMAND_NONE;
}

//---------------------------------------------------------------------

void GameStateManager::doChangeCommand()
{
	// Remove the current state
	if (!m_stack.empty())
	{
		m_stack.top()->exit();
		m_stack.pop();
	}

	// Store and enter the new state
	IGameState* pState = m_states[m_ID];
	assert(pState);

	try
	{
		pState->enter();
		m_stack.push(pState);
	}
	catch (Ogre::Exception ex)
	{
		ATHENA_LOG_ERROR("Failed to push the state #" + StringConverter::toString(m_ID) +
						 ", reason: " + ex.getFullDescription());
	}
	catch (...)
	{
		ATHENA_LOG_ERROR("Failed to push the state #" + StringConverter::toString(m_ID) +
						 ", unknown exception");
	}
}

//---------------------------------------------------------------------

void GameStateManager::doPushCommand()
{
	// Pause the current state
	if (!m_stack.empty())
		m_stack.top()->pause();

	// Store and enter the new state
	IGameState* pState = m_states[m_ID];
	assert(pState);

	try
	{
		pState->enter();
		m_stack.push(pState);
	}
	catch (Ogre::Exception ex)
	{
		ATHENA_LOG_ERROR("Failed to push the state #" + StringConverter::toString(m_ID) +
						 ", reason: " + ex.getFullDescription());
	}
	catch (...)
	{
		ATHENA_LOG_ERROR("Failed to push the state #" + StringConverter::toString(m_ID) +
						 ", unknown exception");
	}
}

//---------------------------------------------------------------------

void GameStateManager::doPopCommand()
{
	// Remove the current state
	m_stack.top()->exit();
	m_stack.pop();

	// Resume the previous state
	if (!m_stack.empty())
		m_stack.top()->resume();
	else if (m_pTaskManager)
		m_pTaskManager->killAllTasks();
}

//---------------------------------------------------------------------

void GameStateManager::doPopAllCommand(bool bKillAllTasks)
{
	while (!m_stack.empty())
	{
		m_stack.top()->exit();
		m_stack.pop();
	}

	if (bKillAllTasks && m_pTaskManager)
		m_pTaskManager->killAllTasks();
}
