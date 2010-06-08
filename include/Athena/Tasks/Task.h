/**	@file	Task.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Tasks::Task'
*/

#ifndef _ATHENA_TASKS_TASK_H
#define _ATHENA_TASKS_TASK_H

#include <Athena/Prerequisites.h>


namespace Athena {
namespace Tasks {

//-----------------------------------------------------------------------------------
/// @brief	Base class for all the tasks
//-----------------------------------------------------------------------------------
class ATHENA_SYMBOL Task
{
	//_____ Construction / Destruction __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Constructor
	//-----------------------------------------------------------------------------------
	Task()	: m_bToKill(false), m_bSuspended(false)	{};

	//-----------------------------------------------------------------------------------
	/// @brief	Destructor
	//-----------------------------------------------------------------------------------
	virtual ~Task()
	{
	};


	//_____ Methods to implement __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Start the task
	/// 
	/// Must be implemented by each task
	/// @return		'true' if successful
	//-----------------------------------------------------------------------------------
	virtual bool start() = 0;

	//-----------------------------------------------------------------------------------
	/// @brief	Called when the task is being suspended
	//-----------------------------------------------------------------------------------
	virtual void onSuspend() {};

	//-----------------------------------------------------------------------------------
	/// @brief	Called each time the task must perform its job
	/// 
	/// Must be implemented by each task
	//-----------------------------------------------------------------------------------
	virtual void update() = 0;

	//-----------------------------------------------------------------------------------
	/// @brief	Called when the task is being resumed
	//-----------------------------------------------------------------------------------
	virtual void onResume() {};

	//-----------------------------------------------------------------------------------
	/// @brief	Stop the task
	/// 
	/// Must be implemented by each task
	//-----------------------------------------------------------------------------------
	virtual void stop() = 0;


	//_____ Management of the task __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Suspend/Resume the task
	/// @param	bSuspend	Indicates if the task must be suspended
	//-----------------------------------------------------------------------------------
	inline void suspend(bool bSuspend) { m_bSuspended = bSuspend; }

	//-----------------------------------------------------------------------------------
	/// @brief	Indicates if the task is suspended
	/// @return	'true' if the task is suspended
	//-----------------------------------------------------------------------------------
	inline bool isSuspended() const { return m_bSuspended; }

	//-----------------------------------------------------------------------------------
	/// @brief	Flag the task as 'to be killed' (it will be done the next time the task
	///			should be processed)
	//-----------------------------------------------------------------------------------
	inline void flagAsKillable() { m_bToKill = true; }

	//-----------------------------------------------------------------------------------
	/// @brief	Indicates if the task must be killed
	/// @return	'true' if the task must be killed
	//-----------------------------------------------------------------------------------
	inline bool mustBeKilled() const {	return m_bToKill; }


	//_____ Attributes __________
protected:
	bool m_bToKill;			///< Indicates that the task must be killed
	bool m_bSuspended;		///< Indicates that the task is suspended (paused)
};

}
}

#endif
