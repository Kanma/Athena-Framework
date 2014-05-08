/** @file   Engine.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Engine'
*/

#include <Athena/Engine.h>

#include <Athena-Entities/ScenesManager.h>
#include <Athena-Entities/ComponentsManager.h>

#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Log/ConsoleLogListener.h>
#include <Athena-Core/Log/XMLLogListener.h>
#include <Athena-Core/Data/LocationManager.h>
#include <Athena-Core/Data/Serialization.h>
#include <Athena-Core/Utils/StringConverter.h>

#include <Athena-Graphics/OgreLogListener.h>

// #include <Athena-Audio/AudioManager.h>

#if ATHENA_FRAMEWORK_SCRIPTING
    #include <Athena-Scripting/ScriptingManager.h>
#endif

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
#include <Ogre/OgreRenderWindow.h>


using namespace Athena;
using namespace Athena::Log;
using namespace Athena::Data;
using namespace Athena::Tasks;
using namespace Athena::GameStates;
using namespace Athena::Inputs;
using namespace Athena::Entities;
using namespace Athena::Physics;
// using namespace Athena::Audio;
using namespace Athena::Graphics;
// using namespace Athena::GUI;
using namespace Athena::Utils;
using namespace std;

#if ATHENA_FRAMEWORK_SCRIPTING
    using namespace Athena::Scripting;
#endif


using Ogre::ConfigFile;
using Ogre::NameValuePairList;
using Ogre::RenderWindow;
using Ogre::ResourceGroupManager;
using Ogre::Root;


/************************************** CONSTANTS **************************************/

/// Context used for logging
static const char*  __CONTEXT__ = "Engine";


/********************************** STATIC ATTRIBUTES **********************************/

namespace Athena {
    namespace Utils {
        /// The instance of the singleton
        template<> Engine* Singleton<Engine>::ms_Singleton = 0;
    }
}


/************************************** FUNCTIONS **************************************/

#if ATHENA_PLATFORM == ATHENA_PLATFORM_APPLE

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
: m_pLocationManager(0), m_pTaskManager(0), m_pGameStateManager(0), m_pScenesManager(0),
  m_pComponentsManager(0), m_pInputsUnit(0),
#if ATHENA_FRAMEWORK_SCRIPTING
  m_pScriptingManager(0),
#endif
  m_pOgreLogListener(0), m_bOwnOgreLogManager(true), m_pMainWindow(0)
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

    // Load the configuration file
    rapidjson::Document document;
    loadJSONFile(strConfigFile, document);

    setup(document);
}

//---------------------------------------------------------------------

void Engine::setup(const rapidjson::Value& configuration)
{
    LogManager* pLogManager = LogManager::getSingletonPtr();

    // Create the log manager if it isn't already done
    if (!pLogManager)
        pLogManager = new LogManager();

    // Create the log listener if necessary
    if (configuration.HasMember("log") && configuration["log"].IsObject())
    {
        const rapidjson::Value& logConfig = configuration["log"];

        ILogListener* pLogListener = 0;

        std::string logKind = "console";
        if (logConfig.HasMember("kind") && logConfig["kind"].IsString())
            logKind = logConfig["kind"].GetString();

        if (logConfig.HasMember("file") && logConfig["file"].IsString())
        {
            if (logKind == "xml")
            {
                pLogListener = new XMLLogListener(logConfig["file"].GetString());
                if (!static_cast<XMLLogListener*>(pLogListener)->isFileOpen())
                {
                    delete pLogListener;
                    pLogListener = 0;
                }
            }
        }
        else if (logKind == "console")
        {
            pLogListener = new ConsoleLogListener();
        }

        if (pLogListener)
            pLogManager->addListener(pLogListener, true);
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

            // Redirect the Ogre log to the Athena's log system
            Ogre::Log* pLog = pOgreLogManager->createLog("Ogre.log", true, false, true);
            m_pOgreLogListener = new OgreLogListener();
            pLog->addListener(m_pOgreLogListener);
        }
        else
        {
            m_bOwnOgreLogManager = false;
        }

        // Create the Location Manager
        m_pLocationManager = new LocationManager();

        if (configuration.HasMember("locations") && configuration["locations"].IsObject())
            m_pLocationManager->addLocations(configuration["locations"]);

        // Create the Task Manager
        m_pTaskManager = new TaskManager();

        // Create the Game State Manager
        m_pGameStateManager = new GameStateManager();
        m_pGameStateManager->setTaskManager(m_pTaskManager);

        // Create the Scenes Manager
        m_pScenesManager = new ScenesManager();

        // Create the Components Manager
        m_pComponentsManager = new ComponentsManager();

#if ATHENA_FRAMEWORK_SCRIPTING
        // Create the Scripting Manager
        m_pScriptingManager = new ScriptingManager();
#endif

        // Create the Audio Manager (not implemented yet)
        // m_pAudioManager = new AudioManager();

        // Create the Network Manager (not implemented yet)
        // m_pNetworkManager = new NetworkManager();

        // Initializes the Graphics module & Ogre
        Root* pOgreRoot = Graphics::initialize(configuration["graphics"]);
        pOgreRoot->initialise(false);

        // Initialize the Physics module
        Physics::initialize();

        // Create the standard tasks
        m_pTaskManager->addTask(TASK_START,             new TaskStart());
        m_pTaskManager->addTask(TASK_PHYSICS,           new PhysicsTask());
        m_pTaskManager->addTask(TASK_GRAPHICS,          new GraphicsTask());
        m_pTaskManager->addTask(TASK_GAMESTATE,         new GameStateTask(m_pGameStateManager));
        m_pTaskManager->addTask(TASK_GAMESTATESTACK,    new GameStateStackTask(m_pGameStateManager));
        // m_pTasksManager->addTask(TASK_AUDIO,           new AudioTask());
        // m_pTasksManager->addTask(TASK_NETWORK,         new NetworkTask());
        m_pTaskManager->addTask(TASK_END,               new TaskEnd());
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

void Engine::destroy()
{
    ATHENA_LOG_EVENT("Destruction of the engine");

    delete m_pGameStateManager;
    m_pGameStateManager = 0;

    delete m_pTaskManager;
    m_pTaskManager = 0;

    // delete m_pNetworkManager;
    // m_pNetworkManager = 0;

    // delete m_pAudioManager;
    // m_pAudioManager = 0;

    // delete m_pGUIManager;
    // m_pGUIManager = 0;

#if ATHENA_FRAMEWORK_SCRIPTING
    delete m_pScriptingManager;
    m_pScriptingManager = 0;
#endif

    delete m_pInputsUnit;
    m_pInputsUnit = 0;

    delete m_pScenesManager;
    m_pScenesManager = 0;

    delete m_pComponentsManager;
    m_pComponentsManager = 0;

    if (Root::getSingletonPtr())
    {
        Root::getSingletonPtr()->shutdown();
        delete Root::getSingletonPtr();
        m_pMainWindow   = 0;
    }

    delete m_pLocationManager;
    m_pLocationManager = 0;

    if (m_bOwnOgreLogManager)
    {
        delete LogManager::getSingletonPtr();
        delete m_pOgreLogListener;
        m_pOgreLogListener = 0;
    }

    delete LogManager::getSingletonPtr();
}

//---------------------------------------------------------------------

RenderWindow* Engine::createRenderWindow(size_t existingwindowhandle, const std::string& strName,
                                         int width, int height, bool fullscreen)
{
    RenderWindow* pWindow = Graphics::createRenderWindow(existingwindowhandle, strName,
                                                         width, height, fullscreen);

    if (!m_pMainWindow && pWindow)
    {
        m_pMainWindow = pWindow;
        createInputsUnit();
    }

    return pWindow;
}

//---------------------------------------------------------------------

RenderWindow* Engine::createRenderWindow(const std::string& strName,
                                         const std::string& strTitle,
                                         int width, int height, bool fullscreen)
{
    RenderWindow* pWindow = Graphics::createRenderWindow(strName, strTitle, width, height,
                                                         fullscreen);

    if (!m_pMainWindow && pWindow)
    {
        m_pMainWindow = pWindow;
        createInputsUnit();
    }

    return pWindow;
}

//---------------------------------------------------------------------

void Engine::createInputsUnit()
{
    assert(!m_pInputsUnit);
    assert(m_pMainWindow);

    m_pInputsUnit = new InputsUnit();

    size_t hWnd = 0;
    m_pMainWindow->getCustomAttribute("WINDOW", &hWnd);

    if (m_pInputsUnit->init((void*) hWnd))
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
