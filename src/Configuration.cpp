/** @file   Configuration.cpp
    @author Philip Abbet

    Implementation of the class 'Athena::Configuration'
*/

#include <Athena/Configuration.h>
#include <Athena-Core/Data/ConfigFile.h>
#include <Ogre/OgreException.h>

using namespace Athena;
using namespace Athena::Data;
using namespace std;


/****************************** CONSTRUCTION / DESTRUCTION *****************************/

Configuration::Configuration()
{
    // Athena configuration defaults
    athena.strOgreConfigFile            = "";
    athena.strPluginsFile               = "plugins.cfg";
    athena.strResourcesFile             = "";

    // Log configuration defaults
    log.strAthenaLogFile                = "";
    log.strAthenaLogKind                = "XML";
    log.strOgreLogFile                  = "";
    log.bRedirectOgreLog                = true;

    // GUI configuration defaults
    // gui.bEnable                         = true;
    // gui.strRuntimeDir                   = "Runtime";
    // gui.strProfileDir                   = "Profile";
    // gui.strLocalDir                     = "";
    // gui.strDefaultCursor                = "";

    // Physics configuration defaults
    physics.nbMaxSubSteps               = 1;
    physics.fixedTimeStep               = Math::Real(1.0 / 60.0);
}

//---------------------------------------------------------------------

Configuration::~Configuration()
{
}


/*************************************** METHODS ***************************************/

void Configuration::load(const std::string& strConfigFile)
{
    // Assertions
    assert(!strConfigFile.empty() && "No configuration file supplied");

    // Declarations
    ConfigFile cfgFile;

    // Open the configuration file
    if (!cfgFile.load(strConfigFile))
        OGRE_EXCEPT(0, "Failed to load the configuration file '" + strConfigFile + "'", __FUNCTION__);

    // Athena section
    if (cfgFile.selectSection("Athena"))
    {
        // Required parameters
        if (!cfgFile.getParameterValue("Config", athena.strOgreConfigFile))
            OGRE_EXCEPT(0, "Missing parameter: Ogre's configuration file", __FUNCTION__);

        // Optional parameters
        cfgFile.getParameterValue("Plugins",    athena.strPluginsFile);
        cfgFile.getParameterValue("Resources",  athena.strResourcesFile);
    }
    else
    {
        OGRE_EXCEPT(0, "Missing section: Athena", __FUNCTION__);
    }


    // Log section
    if (cfgFile.selectSection("Log"))
    {
        // Optional parameters
        cfgFile.getParameterValue("Athena",             log.strAthenaLogFile);
        cfgFile.getParameterValue("Kind",               log.strAthenaLogKind);
        cfgFile.getParameterValue("Ogre",               log.strOgreLogFile);
        cfgFile.getParameterValue("RedirectOgreLog",    log.bRedirectOgreLog);
    }


    // GUI section
    // if (cfgFile.selectSection("GUI"))
    // {
    //  // Optional parameters
    //  cfgFile.getParameterValue("Enable", gui.bEnable);
    //  cfgFile.getParameterValue("RuntimeDir", gui.strRuntimeDir);
    //  cfgFile.getParameterValue("ProfileDir", gui.strProfileDir);
    //
    //  // Required parameters if enabled
    //  if (gui.bEnable)
    //  {
    //      if (!cfgFile.getParameterValue("LocalDir", gui.strLocalDir))
    //      {
    //          OGRE_EXCEPT(0, "Missing parameter: GUI's local directory", __FUNCTION__);
    //      }
    //
    //      if (!cfgFile.getParameterValue("DefaultCursor", gui.strDefaultCursor))
    //      {
    //          OGRE_EXCEPT(0, "Missing parameter: GUI's default cursor", __FUNCTION__);
    //      }
    //  }
    // }


    // Physics section
    if (cfgFile.selectSection("Physics"))
    {
        // Optional parameters
        cfgFile.getParameterValue("NbMaxSubSteps",  physics.nbMaxSubSteps);
        cfgFile.getParameterValue("FixedTimeStep",  physics.fixedTimeStep);
    }
}
