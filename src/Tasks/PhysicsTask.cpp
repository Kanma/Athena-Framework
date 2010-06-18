/** @file	PhysicsTask.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::PhysicsTask'
*/

#include <Athena/Tasks/PhysicsTask.h>
#include <Athena/Tasks/TaskManager.h>
#include <Athena/Engine.h>
#include <Athena-Entities/ScenesManager.h>
#include <Athena-Physics/World.h>

using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Entities;
using namespace Athena::Physics;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

PhysicsTask::PhysicsTask()
{
}

//---------------------------------------------------------------------

PhysicsTask::~PhysicsTask()
{
}


/******************************** MANAGEMENT OF THE TASK *******************************/

bool PhysicsTask::start()
{
	return true;
}

//---------------------------------------------------------------------

void PhysicsTask::update()
{
    assert(Engine::getSingletonPtr());
    assert(ScenesManager::getSingletonPtr());
    
    float elapsed = Engine::getSingletonPtr()->getTaskManager()->getElapsedSeconds();
    const Configuration* pConfig = Engine::getSingletonPtr()->getConfiguration();
    
    ScenesManager::tScenesIterator iter =
        ScenesManager::getSingletonPtr()->getScenesIterator();
    while (iter.hasMoreElements())
    {
        Scene* pScene = iter.getNext();
        if (pScene->isEnabled())
        {
            World* pWorld = dynamic_cast<World*>(pScene->getComponent(
                        Entities::tComponentID(Entities::COMP_PHYSICAL, World::DEFAULT_NAME)));
            
            pWorld->stepSimulation(elapsed, pConfig->physics.nbMaxSubSteps,
                                   pConfig->physics.fixedTimeStep);
        }
    }
}

//---------------------------------------------------------------------

void PhysicsTask::stop()
{
}
