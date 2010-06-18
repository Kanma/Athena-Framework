/** @file	Configuration.h
	@author	Philip Abbet

	Declaration of the class 'Athena::Configuration'
*/

#ifndef _ATHENA_CONFIGURATION_H_
#define _ATHENA_CONFIGURATION_H_

#include <Athena/Prerequisites.h>

namespace Athena {

//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of Athena
//-----------------------------------------------------------------------------------
struct tAthenaConf
{
	std::string	    strOgreConfigFile;	///< Name of the Ogre configuration file
	std::string	    strPluginsFile;		///< Name of the file containing the list of plugins to load
	std::string	    strResourcesFile;	///< Name of the file containing the list of paths to the resources
};


//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the logging
//-----------------------------------------------------------------------------------
struct tLogConf
{
	std::string	    strAthenaLogFile;	///< Name of the log file of Athena
	std::string	    strAthenaLogKind;	///< Kind of the log file of Athena
	std::string	    strOgreLogFile;		///< Name of the log file of Ogre
	bool			bRedirectOgreLog;	///< Indicates if the Ogre log must be redirected into the Athena's one
};


//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the GUI subsystem
//-----------------------------------------------------------------------------------
// struct tGUIConf
// {
//  bool            bEnable;                    ///< Indicates if the GUI subsystem is enabled
//  std::string     strRuntimeDir;              ///< Runtime directory
//  std::string     strProfileDir;              ///< Profile directory
//  std::string     strLocalDir;                ///< Local directory
//  std::string     strDefaultCursor;           ///< Default cursor
// };

//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the Inputs subsystem
//-----------------------------------------------------------------------------------
struct tInputsConf
{
	bool			bEnable;					///< Indicates if the Inputs subsystem is enabled
//	std::string	    strVirtualControllersFile;	///< Name of the file containing the virtual controllers
};

//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the default window
//-----------------------------------------------------------------------------------
struct tDefaultWindowConf
{
	bool			bEnable;					///< Indicates if a default window must be created
	std::string	    strTitle;					///< Title of the window
};

//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the Audio subsystem
//-----------------------------------------------------------------------------------
// struct tAudioConf
// {
//  bool            bEnable;                    ///< Indicates if the Audio subsystem is enabled
// };

//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the Physics subsystem
//-----------------------------------------------------------------------------------
struct tPhysicsConf
{
    bool            bEnable;                    ///< Indicates if the Physics subsystem is enabled
    unsigned int    nbMaxSubSteps;              ///< Maximum number of substeps during a simulation
    float           fixedTimeStep;              ///< Fixed timesteps used for the simulations
};

//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the Scripting subsystem
//-----------------------------------------------------------------------------------
// struct tScriptingConf
// {
//  bool            bEnable;                    ///< Indicates if the Scripting subsystem is enabled
//  std::string     strStartupScript;           ///< Name of the script to execute at startup
//  bool            bEmbedded;                  ///< Indicates if the Scripting subsystem is embedded
// };

//-----------------------------------------------------------------------------------
/// @brief	Contains the configuration of the Network subsystem
//-----------------------------------------------------------------------------------
// struct tNetworkConf
// {
//  bool            bEnable;                    ///< Indicates if the Network subsystem is enabled
// };


//---------------------------------------------------------------------------------------
/// @brief	Contains the configuration of the engine
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL Configuration
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    //-----------------------------------------------------------------------------------
	Configuration();

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	~Configuration();


	//_____ Methods __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Load a configuration file
    /// @param	strConfigFile	The name of the configuration file to use
    //-----------------------------------------------------------------------------------
	void load(const std::string& strConfigFile);


	//_____ Attributes __________
public:
	tAthenaConf			athena;			///< Athena configuration
	tLogConf			log;			///< Log configuration
    // tGUIConf         gui;            ///< GUI configuration
	tInputsConf			inputs;			///< Inputs configuration
	tDefaultWindowConf	defaultWindow;	///< Default window configuration
    // tAudioConf          audio;          ///< Audio configuration
    tPhysicsConf        physics;        ///< Physics configuration
    // tScriptingConf      scripting;      ///< Scripting configuration
    // tNetworkConf        network;        ///< Network configuration
};

}

#endif
