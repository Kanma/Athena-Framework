/** @file	GraphicsTask.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::GraphicsTask'
*/

#include <Athena/Tasks/GraphicsTask.h>
#include <Athena-Entities/ScenesManager.h>
#include <Athena-Entities/Scene.h>
#include <Athena-Graphics/Visual/World.h>
#include <Ogre/OgreRoot.h>
#include <Ogre/OgreSceneManager.h>

// Windows-specific includes
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <direct.h>
#   include <windows.h>
#endif


using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Entities;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

GraphicsTask::GraphicsTask()
{
}

//---------------------------------------------------------------------

GraphicsTask::~GraphicsTask()
{
}


/******************************** MANAGEMENT OF THE TASK *******************************/

bool GraphicsTask::start()
{
	// Assertions
	assert(pOgreRoot);

	return true;
}

//---------------------------------------------------------------------

void GraphicsTask::update()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    // Pump events on Win32
    MSG msg;
	while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#endif

    ScenesManager::tScenesIterator iter = ScenesManager::getSingletonPtr()->getScenesIterator();
    while (iter.hasMoreElements())
    {
        Scene* pScene = iter.getNext();
        if (pScene->isEnabled())
        {
            World* pWorld = dynamic_cast<World*>(pScene->getMainComponent(COMP_VISUAL));
            if (pWorld && pWorld->getSceneManager())
                pWorld->getSceneManager()->_updateSceneGraph(0);
        }
    }
    
	Ogre::Root::getSingletonPtr()->_updateAllRenderTargets();
}

//---------------------------------------------------------------------

void GraphicsTask::stop()
{
}
