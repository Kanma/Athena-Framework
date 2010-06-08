/**	@file	TaskEnd.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Tasks::TaskEnd'
*/

#ifndef _ATHENA_TASKS_TASKSTART_H
#define _ATHENA_TASKS_TASKSTART_H

#include <Athena/Prerequisites.h>
#include <Athena/Tasks/Task.h>


namespace Athena {
namespace Tasks {

//-----------------------------------------------------------------------------------
/// @brief	Last task executed each frame
//-----------------------------------------------------------------------------------
class ATHENA_SYMBOL TaskEnd: public Tasks::Task
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    //-----------------------------------------------------------------------------------
	TaskEnd();

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~TaskEnd();


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
