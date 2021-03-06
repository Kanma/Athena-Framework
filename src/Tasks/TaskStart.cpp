/** @file   TaskStart.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Tasks::TaskStart'
*/

#include <Athena/Tasks/TaskStart.h>
#include <Ogre/OgreRoot.h>

using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Graphics;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

TaskStart::TaskStart()
{
}

//---------------------------------------------------------------------

TaskStart::~TaskStart()
{
}


/******************************** MANAGEMENT OF THE TASK *******************************/

bool TaskStart::start()
{
    // Assertions
    assert(Ogre::Root::getSingletonPtr());

    return true;
}

//---------------------------------------------------------------------

void TaskStart::update()
{
    Ogre::Root::getSingletonPtr()->_fireFrameStarted();
}

//---------------------------------------------------------------------

void TaskStart::stop()
{
}
