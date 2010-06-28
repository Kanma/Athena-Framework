/**	@file	Engine.cpp
	@author	Philip Abbet

	Implementation of the class 'Athena::Engine'
*/

#include <Athena/Engine.h>
#include <Athena-Core/Data/ConfigFile.h>

#include <Athena-Entities/ScenesManager.h>
#include <Athena-Entities/ComponentsManager.h>

#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Log/XMLLogListener.h>
#include <Athena-Core/Utils/StringConverter.h>

#include <Athena-Graphics/OgreLogListener.h>

// #include <Athena-Audio/AudioManager.h>
// #include <Athena-Scripting/ScriptingManager.h>
// #include <Athena-GUI/GUIManager.h>
// #include <Athena-GUI/GUIListener.h>

#include <Athena/Tasks/TaskManager.h>
#include <Athena/Tasks/GameStateStackTask.h>
#include <Athena/Tasks/GameStateTask.h>
#include <Athena/Tasks/GraphicsTask.h>
#include <Athena/Tasks/InputsTask.h>
#include <Athena/Tasks/PhysicsTask.h>
#include <Athena/Tasks/TaskEnd.h>
#include <Athena/Tasks/TaskStart.h>

#include <Athena/GameStates/GameStateManager.h>

#include <Athena-Inputs/InputsUnit.h>

#include <Ogre/OgreRoot.h>
#include <Ogre/OgreConfigFile.h>


using namespace Athena;
using namespace Athena::Log;
using namespace Athena::Data;
using namespace Athena::Tasks;
using namespace Athena::GameStates;
using namespace Athena::Inputs;
using namespace Athena::Entities;
// using namespace Athena::Physics;
// using namespace Athena::Audio;
// using namespace Athena::Scripting;
using namespace Athena::Graphics;
// using namespace Athena::GUI;
using namespace Athena::Utils;
using namespace std;


using Ogre::ConfigFile;
using Ogre::NameValuePairList;
using Ogre::RenderWindow;
using Ogre::ResourceGroupManager;
using Ogre::Root;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*	__CONTEXT__ = "Engine";


/********************************** STATIC ATTRIBUTES **********************************/

/// The instance of the singleton
template<> Engine* Singleton<Engine>::ms_Singleton = 0;


/************************************** FUNCTIONS **************************************/

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE

#include <CoreFoundation/CoreFoundation.h>

// This function will locate the path to our application on OS X,
// unlike windows you can not rely on the curent working directory
// for locating your configuration files and resources.
std::string macBundlePath()
{
    char path[1024];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    assert(mainBundle);
	
    CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
    assert(mainBundleURL);
	
    CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
    assert(cfStringRef);
	
    CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);
	
    CFRelease(mainBundleURL);
    CFRelease(cfStringRef);
	
    return std::string(path);
}

#endif


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

Engine::Engine()
: m_pTaskManager(0), m_pGameStateManager(0), m_pScenesManager(0), m_pComponentsManager(0),
  m_pInputsUnit(0), m_pOgreLogListener(0), m_bOwnOgreLogManager(true), m_pMainWindow(0)
{
}

//---------------------------------------------------------------------

Engine::~Engine()
{
	destroy();
}

//---------------------------------------------------------------------

Engine& Engine::getSingleton()
{
	return Singleton<Engine>::getSingleton();
}

//---------------------------------------------------------------------

Engine* Engine::getSingletonPtr()
{
	return Singleton<Engine>::getSingletonPtr();
}


/******************************* MANAGEMENT OF THE ENGINE ******************************/

void Engine::setup(const std::string& strConfigFile)
{
	// Assertions
	assert(!strConfigFile.empty() && "No configuration file supplied");

	// Open the configuration file
	m_configuration.load(strConfigFile);

	setup();
}

//---------------------------------------------------------------------

void Engine::setup(const Configuration& configuration)
{
	// Copy the configuration
	m_configuration = configuration;

	setup();
}

//---------------------------------------------------------------------

void Engine::setup()
{
    LogManager* pLogManager = LogManager::getSingletonPtr();
    
	// Create the log manager if it isn't already done
	if (!pLogManager)
	{
		pLogManager = new LogManager();
		
		if (!m_configuration.log.strAthenaLogFile.empty())
		{
			// TODO: Create the right kind of listener, depending of the value of (m_configuration.log.strAthenaLogKind

			XMLLogListener* pLogListener = new XMLLogListener(m_configuration.log.strAthenaLogFile);

			if (pLogListener->isFileOpen())
				pLogManager->addListener(pLogListener, true);
			else
				delete pLogListener;
		}
	}

	ATHENA_LOG_EVENT("Creation of the engine");

	try
	{
		// If the ogre log isn't already created, use the configuration
		if (!Ogre::LogManager::getSingletonPtr())
		{
			// Create the Ogre's log manager
			Ogre::LogManager* pOgreLogManager = new Ogre::LogManager();
			m_bOwnOgreLogManager = true;

			// Test if we must create a real file, or a pure redirection to the Athena's log system
			Ogre::Log* pLog = 0;
			if (!m_configuration.log.strOgreLogFile.empty())
				pLog = pOgreLogManager->createLog(m_configuration.log.strOgreLogFile, true, true);
			else if (m_configuration.log.bRedirectOgreLog)
				pLog = pOgreLogManager->createLog("Ogre.log", true, true, true);

			// Test if we must create a redirection to the Athena's log system
			if (pLog && m_configuration.log.bRedirectOgreLog)
			{
                m_pOgreLogListener = new OgreLogListener();
				pLog->addListener(m_pOgreLogListener);
		    }
		}
		else
		{
			m_bOwnOgreLogManager = false;
		}

		// Create the Task Manager
		m_pTaskManager = new TaskManager();

		// Create the Game State Manager
		m_pGameStateManager = new GameStateManager();
        m_pGameStateManager->setTaskManager(m_pTaskManager);

		// Create the Scenes Manager
		m_pScenesManager = new ScenesManager();

		// Create the Components Manager
		m_pComponentsManager = new ComponentsManager();

		// Initializes the Graphics module & Ogre
		assert(!m_configuration.athena.strPluginsFile.empty());
		assert(!m_configuration.athena.strOgreConfigFile.empty());
		Root* pOgreRoot = Graphics::initialize(m_configuration.athena.strPluginsFile,
		                                       m_configuration.athena.strOgreConfigFile,
							                   (m_configuration.log.strOgreLogFile.empty() ? "Ogre.log" : m_configuration.log.strOgreLogFile));

		// Load config settings from ogre.cfg
		if (!pOgreRoot->restoreConfig())
		{
			// If there is no config file, show the configuration dialog
			if (!pOgreRoot->showConfigDialog())
			{
				OGRE_EXCEPT(0,
							"Failed to process '" + m_configuration.athena.strOgreConfigFile + "'",
							__FUNCTION__);
			}
		}

		// Setup the resources if a file was supplied
		if (!m_configuration.athena.strResourcesFile.empty())
			setupResources(m_configuration.athena.strResourcesFile);

		// Initialise and create a default rendering window (if necessary)
		if (m_configuration.defaultWindow.bEnable)
		{
			if (m_configuration.defaultWindow.strTitle.empty())
				m_pMainWindow = pOgreRoot->initialise(true);
			else
				m_pMainWindow = pOgreRoot->initialise(true, m_configuration.defaultWindow.strTitle);

			// Initialise the resources, parse scripts, etc
			ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		}
		else
		{
			pOgreRoot->initialise(false);
		}

        // Initialize the Physics module
        if (m_configuration.physics.bEnable)
            Physics::initialize();

		// Create the standard tasks
		m_pTaskManager->addTask(TASK_START,             new TaskStart());
		m_pTaskManager->addTask(TASK_GRAPHICS,          new GraphicsTask());
		m_pTaskManager->addTask(TASK_GAMESTATE,         new GameStateTask(m_pGameStateManager));
		m_pTaskManager->addTask(TASK_GAMESTATESTACK,    new GameStateStackTask(m_pGameStateManager));
		m_pTaskManager->addTask(TASK_END,               new TaskEnd());

        if (m_configuration.physics.bEnable)
		    m_pTaskManager->addTask(TASK_PHYSICS, new PhysicsTask());
		
		// Create the inputs unit
		if (m_pMainWindow && m_configuration.inputs.bEnable)
			createInputsUnit();

		// Create the GUI manager
        // if (pMainWindow && m_configuration.gui.bEnable && m_configuration.inputs.bEnable)
        //  new CGUIManager();

		// Create the audio manager
        // if (m_configuration.audio.bEnable)
        //  new CAudioManager();
        
		// Create the network manager
        // if (m_configuration.network.bEnable)
        // {
        //  new CNetworkManager();
        //  pTasksManager->addTask(TASK_NETWORK, new CNetworkTask());
        // }

		// Create the scripting manager
        // if (m_configuration.scripting.bEnable)
        // {
        //  new CScriptingManager();
        // 
        //  // Execute the startup script if any
        //  if (!m_configuration.scripting.strStartupScript.empty())
        //      pScriptingManager->executeFile(m_configuration.scripting.strStartupScript);
        // }
	}
	catch (Ogre::Exception& ex)
	{
		destroy();

		throw(Ogre::Exception(ex));
	}
	catch (...)
	{
		destroy();

		OGRE_EXCEPT(0, "Failed to create the engine, unknown exception", __FUNCTION__);
	}
}

//---------------------------------------------------------------------

const Configuration* Engine::getConfiguration() const
{
	return &m_configuration;
}

//---------------------------------------------------------------------

void Engine::destroy()
{
	ATHENA_LOG_EVENT("Destruction of the engine");

    // delete pNetworkManager;
    // pNetworkManager = 0;

    // delete pAudioManager;
    // pAudioManager = 0;

    // delete pGUIManager;
    // pGUIManager = 0;

    // delete pScriptingManager;
    // pScriptingManager = 0;

	delete m_pInputsUnit;
	m_pInputsUnit = 0;

	delete m_pTaskManager;
	m_pTaskManager = 0;

	delete m_pGameStateManager;
	m_pGameStateManager = 0;

    // delete pBehaviorsManager;
    // pBehaviorsManager = 0;

	delete m_pScenesManager;
	m_pScenesManager = 0;

	delete m_pComponentsManager;
	m_pComponentsManager = 0;

	if (Root::getSingletonPtr())
	{
		Root::getSingletonPtr()->shutdown();
		delete Root::getSingletonPtr();
		m_pMainWindow	= 0;
	}

	if (m_bOwnOgreLogManager)
	{
		delete LogManager::getSingletonPtr();
        delete m_pOgreLogListener;
        m_pOgreLogListener = 0;
	}
	
	delete LogManager::getSingletonPtr();
}

//---------------------------------------------------------------------

void Engine::setupResources(const std::string& strFileName)
{
	// Declarations
	Ogre::ConfigFile	cfgFile;
    string		        strSecName, strTypeName, strArchName;

	// Load resource paths from config file
	cfgFile.load(strFileName);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator sectionIter = cfgFile.getSectionIterator();
	while (sectionIter.hasMoreElements())
	{
		strSecName = sectionIter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = sectionIter.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			strTypeName = i->first;
			strArchName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
			// OS X does not set the working directory relative to the app,
			// In order to make things portable on OS X we need to provide
			// the loading with it's own bundle path location
			ResourceGroupManager::getSingleton().addResourceLocation(string(macBundlePath() + "/" + strArchName),
																	 strTypeName, strSecName);
#else
			ResourceGroupManager::getSingleton().addResourceLocation(strArchName, strTypeName, strSecName);
#endif
		}
	}
}

//---------------------------------------------------------------------

RenderWindow* Engine::createRenderWindow(int existingwindowhandle, const std::string& strName,
										 int width, int height, bool fullscreen)
{
	// Declarations
	NameValuePairList miscParams;
	RenderWindow*	  theWindow;

	miscParams["externalWindowHandle"] = StringConverter::toString((size_t) existingwindowhandle);
		
	theWindow = Root::getSingletonPtr()->createRenderWindow(strName, width, height, fullscreen, &miscParams);

	if (!m_pMainWindow)
	{
		m_pMainWindow = theWindow;

		// Initialise the resources, parse scripts, etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		if (m_configuration.inputs.bEnable)
			createInputsUnit();

        // if (m_configuration.gui.bEnable && m_configuration.inputs.bEnable)
        //  new CGUIManager();
	}

	return theWindow;
}

//---------------------------------------------------------------------

RenderWindow* Engine::createRenderWindow(const std::string& strName,
										 const std::string& strTitle,
										 int width, int height, bool fullscreen)
{
	// Declarations
	NameValuePairList miscParams;
	RenderWindow*	  theWindow;

	miscParams["title"] = strTitle;
		
	theWindow = Root::getSingletonPtr()->createRenderWindow(strName, width, height, fullscreen, &miscParams);

	if (!m_pMainWindow)
	{
		m_pMainWindow = theWindow;

		// Initialise the resources, parse scripts, etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		if (m_configuration.inputs.bEnable)
			createInputsUnit();

        // if (m_configuration.gui.bEnable && m_configuration.inputs.bEnable)
        //  new CGUIManager();
	}

	return theWindow;
}

//---------------------------------------------------------------------

void Engine::createInputsUnit()
{
	assert(!m_pInputsUnit);
	assert(m_pMainWindow);

	m_pInputsUnit = new InputsUnit();

	if (m_pInputsUnit->init(m_pMainWindow))
	{
        // // Load the virtual controllers if necessary
        // if (!m_configuration.inputs.strVirtualControllersFile.empty() &&
        //  !pInputsUnit->loadVirtualControllers(m_configuration.inputs.strVirtualControllersFile))
        // {
        //  ATHENA_LOG_ERROR("Failed to load the virtual controllers");
        // }

		m_pTaskManager->addTask(TASK_INPUTS, new InputsTask());
	}
	else
	{
		delete m_pInputsUnit;
		m_pInputsUnit = 0;

		ATHENA_LOG_ERROR("Failed to create the Inputs Unit");
	}
}
