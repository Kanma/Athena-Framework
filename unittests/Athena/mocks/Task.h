/** @file	CMockTask.h
	@author	Philip Abbet

	Definition of the class 'CMockTask'
*/

#ifndef _CMOCKTASK_H_
#define _CMOCKTASK_H_

#include <Athena/Prerequisites.h>
#include <Athena/Tasks/Task.h>


//---------------------------------------------------------------------------------------
/// @brief	Mock implementation of a task
//---------------------------------------------------------------------------------------
class CMockTask: public Athena::Tasks::Task
{
	//_____ Construction / Destruction __________
public:
	CMockTask()
	: uiStep(0), bCanStart(true), bSuspendCalled(false), bResumeCalled(false)
	{
		++uiTasksCount;
	}
	
	virtual ~CMockTask()
	{
		--uiTasksCount;
	}


	//_____ Methods to implement __________
public:
	virtual bool start()
	{
		return bCanStart;
	}


	virtual void onSuspend()
	{
		bSuspendCalled = true;
	}


	virtual void update()
	{
		++uiGlobalStep;
		uiStep = uiGlobalStep;
	}


	virtual void onResume()
	{
		bResumeCalled = true;
	}


	virtual void stop()
	{
	}


	//_____ Attributes __________
public:
	unsigned int	uiStep;
	bool			bCanStart;
	bool			bSuspendCalled;
	bool			bResumeCalled;

	static unsigned int uiGlobalStep;
	static unsigned int uiTasksCount;
};

#endif
