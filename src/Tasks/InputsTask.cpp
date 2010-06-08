/** @file	InputsTask.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::InputsTask'
*/

#include <Athena/Tasks/InputsTask.h>
#include <Athena-Inputs/InputsUnit.h>

using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Inputs;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

InputsTask::InputsTask()
{
}

//---------------------------------------------------------------------

InputsTask::~InputsTask()
{
}


/******************************** MANAGEMENT OF THE TASK *******************************/

bool InputsTask::start()
{
	// Assertions
	assert(InputsUnit::getSingletonPtr());

	return true;
}

//---------------------------------------------------------------------

void InputsTask::update()
{
	InputsUnit::getSingletonPtr()->process();
}

//---------------------------------------------------------------------

void InputsTask::stop()
{
}
