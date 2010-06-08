/**	@file	InputsTask.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Tasks::InputsTask'
*/

#ifndef _ATHENA_TASKS_INPUTSTASK_H
#define _ATHENA_TASKS_INPUTSTASK_H

#include <Athena/Prerequisites.h>
#include <Athena/Tasks/Task.h>


namespace Athena {
namespace Tasks {

//-----------------------------------------------------------------------------------
/// @brief	Task that ticks the Inputs Unit each frame
//-----------------------------------------------------------------------------------
class ATHENA_SYMBOL InputsTask: public Tasks::Task
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    //-----------------------------------------------------------------------------------
	InputsTask();

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~InputsTask();


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
