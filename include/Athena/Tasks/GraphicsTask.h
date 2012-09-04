/** @file   GraphicsTask.h
    @author Philip Abbet

    Declaration of the class 'Athena::Tasks::GraphicsTask'
*/

#ifndef _ATHENA_TASKS_GRAPHICSTASK_H
#define _ATHENA_TASKS_GRAPHICSTASK_H

#include <Athena/Prerequisites.h>
#include <Athena/Tasks/Task.h>


namespace Athena {
namespace Tasks {

//-----------------------------------------------------------------------------------
/// @brief  Task that updates the rendering each frame
//-----------------------------------------------------------------------------------
class ATHENA_FRAMEWORK_SYMBOL GraphicsTask: public Tasks::Task
{
    //_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief  Constructor
    //-----------------------------------------------------------------------------------
    GraphicsTask();

    //-----------------------------------------------------------------------------------
    /// @brief  Destructor
    //-----------------------------------------------------------------------------------
    virtual ~GraphicsTask();


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
};

}
}

#endif
