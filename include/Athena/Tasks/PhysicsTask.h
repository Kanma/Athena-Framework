/** @file   PhysicsTask.h
    @author Philip Abbet

    Declaration of the class 'Athena::Tasks::PhysicsTask'
*/

#ifndef _ATHENA_TASKS_PHYSICSTASK_H
#define _ATHENA_TASKS_PHYSICSTASK_H

#include <Athena/Prerequisites.h>
#include <Athena/Tasks/Task.h>


namespace Athena {
namespace Tasks {

//-----------------------------------------------------------------------------------
/// @brief  Task that updates the physical simulations each frame
//-----------------------------------------------------------------------------------
class ATHENA_FRAMEWORK_SYMBOL PhysicsTask: public Tasks::Task
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    ///
    /// @param  nbMaxSubSteps   Maximum number of substeps during a simulation
    /// @param  fixedTimeStep   Fixed timesteps used for the simulations
    //-----------------------------------------------------------------------------------
    PhysicsTask(unsigned int nbMaxSubSteps = 1, float fixedTimeStep = 1.0f / 60.0f);

    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    virtual ~PhysicsTask();


    //_____ Management of the task __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Start the task
    /// @return 'true' if successful
    //-----------------------------------------------------------------------------------
    virtual bool start();

    //-----------------------------------------------------------------------------------
    /// @brief  Called each time the task must perform its job
    //-----------------------------------------------------------------------------------
    virtual void update();

    //-----------------------------------------------------------------------------------
    /// @brief  Stop the task
    //-----------------------------------------------------------------------------------
    virtual void stop();


    //_____ Attributes __________
protected:
    unsigned int m_nbMaxSubSteps;   ///< Maximum number of substeps during a simulation
    float        m_fixedTimeStep;   ///< Fixed timesteps used for the simulations
};

}
}

#endif
