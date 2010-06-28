/**	@file	TasksManager.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::TasksManager'
*/

#include <Athena/Tasks/TaskManager.h>
#include <Athena/Tasks/Task.h>
#include <Athena-Core/Utils/Timer.h>
#include <Athena-Core/Utils/StringConverter.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Entities/ScenesManager.h>
#include <Athena-Entities/Scene.h>
#include <Athena-Graphics/Visual/World.h>
#include <Ogre/OgreRoot.h>
#include <Ogre/OgreSceneManager.h>
#include <Ogre/OgreWindowEventUtilities.h>


using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Entities;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Utils;
using namespace Athena::Log;
using namespace std;

using Ogre::WindowEventUtilities;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char* __CONTEXT__ = "Tasks Manager";


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

TaskManager::TaskManager()
: m_ulMicroseconds(0), m_ulMilliseconds(0), m_ulElapsedMicroseconds(0),
  m_ulElapsedMilliseconds(0), m_fElapsedSeconds(0.0f)
{
	ATHENA_LOG_EVENT("Creation");
}

//---------------------------------------------------------------------

TaskManager::~TaskManager()
{
	ATHENA_LOG_EVENT("Destruction");

	// Declarations
	tTasksIterator	iter, iterEnd;

	// Process each task
	for (iter = m_tasks.begin(), iterEnd = m_tasks.end(); iter != iterEnd; ++iter)
		delete iter->second;
}


/****************************** MANAGEMENT OF THE TASKS ********************************/

void TaskManager::execute()
{
	ATHENA_LOG_EVENT("Starts the execution");

    ScenesManager::tScenesIterator iter = ScenesManager::getSingletonPtr()->getScenesIterator();
    while (iter.hasMoreElements())
    {
        Scene* pScene = iter.getNext();
        if (pScene->isEnabled())
        {
            World* pWorld = dynamic_cast<World*>(pScene->getMainComponent(COMP_VISUAL));
            if (pWorld && pWorld->getSceneManager())
                pWorld->getSceneManager()->_updateSceneGraph(0);
        }
    }

	// Reset the main timer
	m_timer.reset();
	m_ulMicroseconds		= 0;
	m_ulMilliseconds		= 0;
	m_ulElapsedMicroseconds = 0;
	m_ulElapsedMilliseconds = 0;
	m_fElapsedSeconds		= 0.0f;

	// Process each task one after another
	while (!m_tasks.empty())
	{
		WindowEventUtilities::messagePump();

		// Process the tasks
		step();
	}

	ATHENA_LOG_EVENT("End of the execution");
}

//---------------------------------------------------------------------

void TaskManager::step()
{
	// Declarations
	tTasksIterator	iter, iter2, iterEnd;
	Task*			pTask;

	// Process each task
	for (iter = m_tasks.begin(), iterEnd = m_tasks.end(); iter != iterEnd; )
	{
		pTask = iter->second;
		iter2 = iter;
		++iter;
		
		// Test if te task must be killed
		if (pTask->mustBeKilled())
		{
			pTask->stop();
			delete pTask;
			m_tasks.erase(iter2);
			
			continue;
		}

		// Tell the task to do its job (if it isn't suspended)
		if (!pTask->isSuspended())
			pTask->update();
	}

    // Update the timings
	unsigned long ulLastMicroseconds = m_ulMicroseconds;
	unsigned long ulLastMilliseconds = m_ulMilliseconds;

	m_ulMicroseconds = m_timer.getMicroseconds();
	m_ulMilliseconds = (unsigned long) (m_ulMicroseconds * 0.001f);

	m_ulElapsedMicroseconds = m_ulMicroseconds - ulLastMicroseconds;
	m_ulElapsedMilliseconds = m_ulMilliseconds - ulLastMilliseconds;
	m_fElapsedSeconds		= (float) m_ulElapsedMilliseconds * 0.001f;
}

//---------------------------------------------------------------------

bool TaskManager::addTask(tPriority priority, Task* pTask)
{
	assert(pTask);

	ATHENA_LOG_EVENT("Adding a task, with the priority " + StringConverter::toString(priority));

	// Check that there isn't any other task with the same priority
	if (m_tasks.find(priority) != m_tasks.end())
	{
		ATHENA_LOG_ERROR("A task with the same priority already exists");
		delete pTask;
		return false;
	}

	// Start the task
	if (!pTask->start())
	{
		ATHENA_LOG_ERROR("Failed to start the task");
		delete pTask;
		return false;
	}

	// Put the task in the tasks pool
	m_tasks[priority] = pTask;
	
	return true;
}

//---------------------------------------------------------------------

void TaskManager::suspendTask(tPriority priority)
{
	// Declarations
	tTasksIterator iter;

	// Retrieve the task
    iter = m_tasks.find(priority);
	if (iter == m_tasks.end())
		return;

	// Check that the task isn't already suspended
	if (iter->second->isSuspended())
		return;

	// Suspend the task
	iter->second->onSuspend();
	iter->second->suspend(true);
}

//---------------------------------------------------------------------

void TaskManager::resumeTask(tPriority priority)
{
	// Declarations
	tTasksIterator iter;

	// Retrieve the task
    iter = m_tasks.find(priority);
	if (iter == m_tasks.end())
		return;

	// Check that the task is suspended
	if (!iter->second->isSuspended())
		return;

	// Resume the task
	iter->second->suspend(false);
	iter->second->onResume();
}

//---------------------------------------------------------------------

void TaskManager::removeTask(tPriority priority)
{
	// Declarations
	tTasksIterator iter;

	// Retrieve the task
    iter = m_tasks.find(priority);
	if (iter == m_tasks.end())
		return;

	// Mark the task as 'to be killed'
	iter->second->flagAsKillable();
}

//---------------------------------------------------------------------

void TaskManager::killAllTasks()
{
	// Declarations
	tTasksIterator iter, iterEnd;

	// // Mark all tasks as 'to be killed'
	for (iter = m_tasks.begin(), iterEnd = m_tasks.end(); iter != iterEnd; ++iter)
		iter->second->flagAsKillable();
}
