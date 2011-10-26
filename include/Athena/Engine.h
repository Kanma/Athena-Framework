/**	@file	Engine.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Engine'
*/

#ifndef _ATHENA_ENGINE_H_
#define _ATHENA_ENGINE_H_

#include <Athena/Prerequisites.h>
#include <Athena/Configuration.h>


namespace Athena {


//---------------------------------------------------------------------------------------
/// @brief	Main class, represents the engine itself
///
/// The engine is responsible of the creation/destruction of all the subsystems.
///
/// The configuration of the engine is loaded from a file. By default, all the subsystems
/// are created, but the configuration file can disable the ones that aren't used.
///
/// The engine can also create additional render windows, and setup an existing window to
/// be used by the renderer.
///
/// At shutdown, the destruction of the subsystems is handled by the engine.
///
/// This class is a singleton.
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL Engine: public Utils::Singleton<Engine>
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    //-----------------------------------------------------------------------------------
	Engine();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	virtual ~Engine();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Returns a reference to the instance of the engine
    /// @return	A reference to the engine
    //-----------------------------------------------------------------------------------
	static Engine& getSingleton();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Returns a pointer to the instance of the engine
    /// @return	A pointer to the engine
    //-----------------------------------------------------------------------------------
	static Engine* getSingletonPtr();


	//_____ Management of the engine __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Setup the engine, and initialise the subsystems
    /// @param	strConfigFile	The name of the configuration file
    //-----------------------------------------------------------------------------------
	void setup(const std::string& strConfigFile);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Setup the engine, and initialise the subsystems
    /// @param	configuration	The configuration
    //-----------------------------------------------------------------------------------
	void setup(const Configuration& configuration);

    //-----------------------------------------------------------------------------------
    /// @brief	Returns the configuration of the engine
    /// @return	The configuration
    //-----------------------------------------------------------------------------------
	const Configuration* getConfiguration() const;
	
    //-----------------------------------------------------------------------------------
    /// @brief	Use an existing window as a render window
    /// @param	existingwindowhandle	Handle of the existing window
    /// @param	strName					Name of the window
    /// @param	width					Width of the window
    /// @param	height					Height of the window
    /// @param	fullscreen				Indicates if the rendering must be done on the full
    ///									screen
    /// @return							The render window, 0 if failed
    //-----------------------------------------------------------------------------------
	Ogre::RenderWindow* createRenderWindow(size_t existingwindowhandle,
	                                       const std::string& strName,
										   int width, int height,
										   bool fullscreen);
										   
    //-----------------------------------------------------------------------------------
    /// @brief	Create a render window
    /// @param	strName					Name of the window
    /// @param	strTitle				Title of the window
    /// @param	width					Width of the window
    /// @param	height					Height of the window
    /// @param	fullscreen				Indicates if the rendering must be done on the full
    ///									screen
    /// @return							The render window, 0 if failed
    //-----------------------------------------------------------------------------------
	Ogre::RenderWindow* createRenderWindow(const std::string& strName,
	                                       const std::string& strTitle,
										   int width, int height,
										   bool fullscreen);

    //-----------------------------------------------------------------------------------
    /// @brief	Retrieves the main window of the application
    //-----------------------------------------------------------------------------------
    inline Ogre::RenderWindow* getMainWindow()
    {
        return m_pMainWindow;
	}
										   
    //-----------------------------------------------------------------------------------
    /// @brief	Retrieves the Task Manager
    //-----------------------------------------------------------------------------------
	inline Tasks::TaskManager* getTaskManager()
	{
        return m_pTaskManager;
	}

    //-----------------------------------------------------------------------------------
    /// @brief	Retrieves the Game State Manager
    //-----------------------------------------------------------------------------------
	inline GameStates::GameStateManager* getGameStateManager()
	{
        return m_pGameStateManager;
	}

    //-----------------------------------------------------------------------------------
    /// @brief	Retrieves the Scenes Manager
    //-----------------------------------------------------------------------------------
	inline Entities::ScenesManager* getScenesManager()
	{
        return m_pScenesManager;
	}

    //-----------------------------------------------------------------------------------
    /// @brief	Retrieves the Components Manager
    //-----------------------------------------------------------------------------------
	inline Entities::ComponentsManager* getComponentsManager()
	{
        return m_pComponentsManager;
	}

    //-----------------------------------------------------------------------------------
    /// @brief	Retrieves the Inputs Unit
    //-----------------------------------------------------------------------------------
	inline Inputs::InputsUnit* getInputsUnit()
	{
        return m_pInputsUnit;
	}


private:
    //-----------------------------------------------------------------------------------
    /// @brief	Setup the engine, and initialise the subsystems
    //-----------------------------------------------------------------------------------
	void setup();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Setup the resources used by the game
    /// @param	strFileName		Name of the file containing the paths to the resources
    //-----------------------------------------------------------------------------------
	void setupResources(const std::string& strFileName);
	
    //-----------------------------------------------------------------------------------
    /// @brief	Destroy the subsystems
    //-----------------------------------------------------------------------------------
	void destroy();
	
    //-----------------------------------------------------------------------------------
    /// @brief	Create the Inputs Unit
    //-----------------------------------------------------------------------------------
	void createInputsUnit();


	//_____ Attributes __________
private:
	Configuration	                m_configuration;		///< The configuration of the engine
    Tasks::TaskManager*             m_pTaskManager;         ///< The Task Manager
    GameStates::GameStateManager*   m_pGameStateManager;    ///< The Game State Manager
    Entities::ScenesManager*        m_pScenesManager;       ///< The Scenes Manager
	Entities::ComponentsManager*    m_pComponentsManager;   ///< The Components Manager
    Inputs::InputsUnit*             m_pInputsUnit;          ///< The Inputs Unit
    Graphics::OgreLogListener*      m_pOgreLogListener;     ///< The Ogre Log Listener
	bool			                m_bOwnOgreLogManager;	///< Indicates if the engine is responsible to delete
											                ///  the Log manager of Ogre
    Ogre::RenderWindow*             m_pMainWindow;          ///< Main window of the application
};

}

#endif
