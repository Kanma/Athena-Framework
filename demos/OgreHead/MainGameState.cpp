#import <MainGameState.h>
#import <Athena-Entities/ScenesManager.h>
#import <Athena-Entities/Scene.h>
#import <Athena-Entities/Entity.h>
#import <Athena-Entities/Transforms.h>
#import <Athena-Graphics/Visual/World.h>
#import <Athena-Graphics/Visual/Camera.h>
#import <Athena-Graphics/Visual/PointLight.h>
#import <Athena-Graphics/Visual/Object.h>
#import <Athena-Graphics/Debug/Axes.h>
#import <Athena-Math/Color.h>
#import <Athena/Engine.h>
#import <Athena/Tasks/TaskManager.h>
#import <Ogre/OgreRenderWindow.h>


using namespace Athena;
using namespace Athena::Entities;
using namespace Athena::Graphics;
using namespace Athena::Graphics::Visual;
using namespace Athena::Math;


static const char* __CONTEXT__ = "Main Game State";


/***************************** CONSTRUCTION / DESTRUCTION ******************************/

MainGameState::MainGameState()
: m_pScene(0), m_pCameraEntity(0), m_pEntity(0)
{
}


MainGameState::~MainGameState()
{
}


/************************ METHODS TO BE OVERRIDEN BY EACH STATE ************************/

void MainGameState::enter()
{
    // Create the scene
    m_pScene = new Scene("main");

    Visual::World* pVisualWorld = new Visual::World("", m_pScene->getComponentsList());

    Ogre::SceneManager* pSceneManager = pVisualWorld->createSceneManager(Ogre::ST_GENERIC);
    pSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    pSceneManager->setShadowFarDistance(20.0f);

    pVisualWorld->setAmbientLight(Color(0.5f, 0.5f, 0.5f));

    m_pCameraEntity = m_pScene->create("Camera");
    Visual::Camera* pCamera = new Visual::Camera("Camera", m_pCameraEntity->getComponentsList());
    pCamera->createViewport(Engine::getSingletonPtr()->getMainWindow());
    pCamera->setAutoAspectRatio(true);
    pCamera->setNearClipDistance(1.0f);
    m_pCameraEntity->getTransforms()->setPosition(0.0f, 0.0f, 300.0f);

    m_pEntity = m_pScene->create("Head");
    Visual::Object* pObject = new Visual::Object("Mesh", m_pEntity->getComponentsList());
    pObject->loadMesh("ogrehead.mesh");

    Entity* pLightEntity = m_pScene->create("Light");
    pLightEntity->getTransforms()->setPosition(200.0f, 100.0f, 200.0f);
    Visual::PointLight* pLight = new Visual::PointLight("Light", pLightEntity->getComponentsList());
    pLight->setDiffuseColor(Color(0.8f, 0.8f, 0.8f));

    m_pScene->show();
}


void MainGameState::exit()
{
    if (m_pCameraEntity)
    {
        m_pScene->destroy(m_pCameraEntity);
        m_pCameraEntity = 0;
    }

    if (m_pEntity)
    {
        m_pScene->destroy(m_pEntity);
        m_pEntity = 0;
    }

    if (m_pScene)
    {
        ScenesManager::getSingletonPtr()->destroy(m_pScene);
        m_pScene = 0;
    }
}


void MainGameState::pause()
{
}


void MainGameState::resume()
{
}


void MainGameState::process()
{
    float elapsed = Engine::getSingletonPtr()->getTaskManager()->getElapsedSeconds();

    m_pEntity->getTransforms()->rotate(Vector3::UNIT_Y, Degree(50.0f) * elapsed);
}
