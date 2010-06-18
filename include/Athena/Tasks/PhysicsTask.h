/**	@file	PhysicsTask.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Tasks::PhysicsTask'
*/

#ifndef _ATHENA_TASKS_PHYSICSTASK_H
#define _ATHENA_TASKS_PHYSICSTASK_H

#include <Athena/Prerequisites.h>
#include <Athena/Tasks/Task.h>


namespace Athena {
namespace Tasks {

//-----------------------------------------------------------------------------------
/// @brief	Task that updates the physical simulations each frame
//-----------------------------------------------------------------------------------
class ATHENA_SYMBOL PhysicsTask: public Tasks::Task
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    //-----------------------------------------------------------------------------------
	PhysicsTask();

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~PhysicsTask();


	//_____ Management of the task __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Start the task
    /// @return	'true' if successful
    //-----------------------------------------------------------------------------------
	virtual bool start();

    //-----------------------------------------------------------------------------------
    /// @brief	Called each time the task must perform its job
    //-----------------------------------------------------------------------------------
	virtual void update();

    //-----------------------------------------------------------------------------------
    /// @brief	Stop the task
    //-----------------------------------------------------------------------------------
	virtual void stop();
};

}
}

#endif
