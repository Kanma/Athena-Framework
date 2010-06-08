/**	@file	TaskManager.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Tasks::TaskManager'
*/

#ifndef _ATHENA_TASKS_TASKMANAGER_H_
#define _ATHENA_TASKS_TASKMANAGER_H_

#include <Athena/Prerequisites.h>
#include <Athena-Core/Utils/Timer.h>
#include <map>


namespace Athena {
namespace Tasks {

//---------------------------------------------------------------------------------------
/// @brief	Represents the Task Manager
/// 
/// This manager is responsible of the storing/destruction of the tasks.
///
/// A task is an object that does some job once per frame. The tasks are sorted by
/// priority (the lower is the first one to be executed).
///	
/// The Task Manager can be seen as the implementation of the main loop of the game.
/// Once started, it don't return until the task list is empty. The Task Manager also
/// holds the main timer.
/// 
/// Athena defines some standard tasks. The user can add custom tasks between any of those
/// tasks (there is always enough room for 100 custom tasks between two standard tasks).
/// 
/// A task can be suspended and resumed later.
/// 
/// At shutdown, the destruction of the remaining tasks is handled by the manager.
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL TaskManager
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    //-----------------------------------------------------------------------------------
	TaskManager();

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	~TaskManager();


	//_____ Management of the tasks __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Process the tasks, looping until there isn't any task anymore
    //-----------------------------------------------------------------------------------
	void execute();

    //-----------------------------------------------------------------------------------
    /// @brief	Process the tasks, without looping
    //-----------------------------------------------------------------------------------
	void step();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Add a task in the list
    /// 
    /// @param	priority	The priority of the task
    /// @param	pTask		The task
    /// @return				'true' is successful
    //-----------------------------------------------------------------------------------
	bool addTask(tPriority priority, Task* pTask);

    //-----------------------------------------------------------------------------------
    /// @brief	Suspend a task
    /// 
    /// @param	priority	Priority of the task
    //-----------------------------------------------------------------------------------
	void suspendTask(tPriority priority);

    //-----------------------------------------------------------------------------------
    /// @brief	Resume a suspended task
    /// 
    /// @param	priority	Priority of the task
    //-----------------------------------------------------------------------------------
	void resumeTask(tPriority priority);

    //-----------------------------------------------------------------------------------
    /// @brief	Remove a task from the list
    /// 
    /// @param	priority	Priority of the task
    //-----------------------------------------------------------------------------------
	void removeTask(tPriority priority);

    //-----------------------------------------------------------------------------------
    /// @brief	Kill all the tasks in the list
    //-----------------------------------------------------------------------------------
	void killAllTasks();

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the main timer of the application
    //-----------------------------------------------------------------------------------
    inline Utils::Timer* getMainTimer()
    {
        return &m_mainTimer;
    }


	//_____ Internal types __________
private:
	typedef std::map<tPriority, Task*>	tTasksMap;
	typedef tTasksMap::iterator			tTasksIterator;


	//_____ Attributes __________
private:
	tTasksMap	    m_tasks;	    ///< The list of registered tasks
    Utils::Timer    m_mainTimer;    ///< Main timer of the application
};

}
}

#endif
