/** @file   Configuration.h
    @author Philip Abbet

    Declaration of the class 'Athena::Configuration'
*/

#ifndef _ATHENA_CONFIGURATION_H_
#define _ATHENA_CONFIGURATION_H_

#include <Athena/Prerequisites.h>

namespace Athena {

//-----------------------------------------------------------------------------------
/// @brief  Contains the configuration of Athena
//-----------------------------------------------------------------------------------
struct tAthenaConf
{
    std::string     strOgreConfigFile;  ///< Name of the Ogre configuration file
    std::string     strPluginsFile;     ///< Name of the file containing the list of plugins to load
    std::string     strResourcesFile;   ///< Name of the file containing the list of paths to the resources
};


//-----------------------------------------------------------------------------------
/// @brief  Contains the configuration of the logging
//-----------------------------------------------------------------------------------
struct tLogConf
{
    std::string     strAthenaLogFile;   ///< Name of the log file of Athena
    std::string     strAthenaLogKind;   ///< Kind of the log file of Athena
    std::string     strOgreLogFile;     ///< Name of the log file of Ogre
    bool            bRedirectOgreLog;   ///< Indicates if the Ogre log must be redirected into the Athena's one
};


//-----------------------------------------------------------------------------------
/// @brief  Contains the configuration of the GUI subsystem
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
/// @brief  Contains the configuration of the Physics subsystem
//-----------------------------------------------------------------------------------
struct tPhysicsConf
{
    unsigned int    nbMaxSubSteps;              ///< Maximum number of substeps during a simulation
    float           fixedTimeStep;              ///< Fixed timesteps used for the simulations
};



//---------------------------------------------------------------------------------------
/// @brief  Contains the configuration of the engine
//---------------------------------------------------------------------------------------
class ATHENA_FRAMEWORK_SYMBOL Configuration
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    //-----------------------------------------------------------------------------------
    Configuration();

    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    ~Configuration();


    //_____ Methods __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Load a configuration file
    /// @param  strConfigFile   The name of the configuration file to use
    //-----------------------------------------------------------------------------------
    void load(const std::string& strConfigFile);


    //_____ Attributes __________
public:
    tAthenaConf         athena;         ///< Athena configuration
    tLogConf            log;            ///< Log configuration
    // tGUIConf         gui;            ///< GUI configuration
    tPhysicsConf        physics;        ///< Physics configuration
};

}

#endif
