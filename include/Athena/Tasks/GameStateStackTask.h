/** @file   GameStateStackTask.h
    @author Philip Abbet

    Declaration of the class 'Athena::Tasks::GameStateStackTask'
*/

#ifndef _ATHENA_TASKS_GAMESTATESTACKTASK_H
#define _ATHENA_TASKS_GAMESTATESTACKTASK_H

#include <Athena/Prerequisites.h>
#include <Athena/Tasks/Task.h>


namespace Athena {
namespace Tasks {

//-----------------------------------------------------------------------------------
/// @brief  Task that manages the stack of game states
//-----------------------------------------------------------------------------------
class ATHENA_FRAMEWORK_SYMBOL GameStateStackTask: public Tasks::Task
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    ///
    /// @param  pGameStateManager   The Game State Manager to control
    //-----------------------------------------------------------------------------------
    GameStateStackTask(GameStates::GameStateManager* pGameStateManager);

    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    virtual ~GameStateStackTask();


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
private:
    GameStates::GameStateManager* m_pGameStateManager;
};

}
}

#endif
