/** @file	GraphicsTask.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Tasks::GraphicsTask'
*/

#include <Athena/Tasks/GraphicsTask.h>
#include <Ogre/OgreRoot.h>

// Windows-specific includes
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#   define WIN32_LEAN_AND_MEAN
#   include <direct.h>
#   include <windows.h>
#endif


using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Graphics;


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

	pSceneManager->_updateSceneGraph(0);
	pOgreRoot->_updateAllRenderTargets();
}

//---------------------------------------------------------------------

void GraphicsTask::stop()
{
}
