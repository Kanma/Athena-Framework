/** @file	TaskEnd.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::TaskEnd'
*/

#include <Athena/Tasks/TaskEnd.h>
#include <Ogre/OgreRoot.h>

using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Graphics;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

TaskEnd::TaskEnd()
{
}

//---------------------------------------------------------------------

TaskEnd::~TaskEnd()
{
}


/******************************** MANAGEMENT OF THE TASK *******************************/

bool TaskEnd::start()
{
	// Assertions
	assert(pOgreRoot);

	return true;
}

//---------------------------------------------------------------------

void TaskEnd::update()
{
	pOgreRoot->_fireFrameEnded();
}

//---------------------------------------------------------------------

void TaskEnd::stop()
{
}
