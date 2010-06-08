/** @file   Prerequisites.h
    @author Philip Abbet
    
    Declaration of the types of the Athena Game Framework
*/

#ifndef _ATHENA_PREREQUISITES_H_
#define _ATHENA_PREREQUISITES_H_

#include <Athena-Graphics/Prerequisites.h>
#include <Athena-Inputs/Prerequisites.h>
#include <Athena/Config.h>


//----------------------------------------------------------------------------------------
/// @brief	Main namespace. All the components of the Athena engine belongs to this
///			namespace
//----------------------------------------------------------------------------------------
namespace Athena
{
	//------------------------------------------------------------------------------------
	/// @brief	Contains all the tasks-related classes
	//------------------------------------------------------------------------------------
    namespace Tasks
    {
        class Task;
        class TaskManager;
        
        class GraphicsTask;
        class InputsTask;
        class TaskEnd;
        class TaskStart;
        
        /// Represents the priority of a task
		typedef unsigned int tPriority;
	}


	//-----------------------------------------------------------------------------------
	// Constants and macros related to the standard tasks (see Tasks::TasksManager)
	//-----------------------------------------------------------------------------------
	/// Interval of priorities reserved before and after each standard task for internal use
	const Tasks::tPriority TASK_RESERVED_INTERVAL	= 10;
	/// Interval between each standard task to which the user can add custom tasks
	const Tasks::tPriority TASK_INTERVAL			= 100 + 2 * TASK_RESERVED_INTERVAL;

	/// Priority of the Start task (see Tasks::StartTask)
	const Tasks::tPriority TASK_START				= 0;
	/// Priority of the Inputs task (see Inputs::InputsTask)
	const Tasks::tPriority TASK_INPUTS				= TASK_START + TASK_INTERVAL;
	/// Priority of the Network task (see Network::NetworkTask)
	const Tasks::tPriority TASK_NETWORK				= TASK_INPUTS + TASK_INTERVAL;
	/// Priority of the Physics task (see Physics::PhysicsTask)
	const Tasks::tPriority TASK_PHYSICS				= TASK_NETWORK + TASK_INTERVAL;
	/// Priority of the Audio task (see Audio::AudioTask)
	const Tasks::tPriority TASK_AUDIO				= TASK_PHYSICS + TASK_INTERVAL;
	/// Priority of the Behaviors task (see Behaviors::BehaviorsTask)
	const Tasks::tPriority TASK_BEHAVIORS			= TASK_AUDIO + TASK_INTERVAL;
	/// Priority of the GUI task (see GUI::GUITask)
	const Tasks::tPriority TASK_GUI					= TASK_BEHAVIORS + TASK_INTERVAL;
	/// Priority of the Gamestate task (see GameState::GameStateTask)
	const Tasks::tPriority TASK_GAMESTATE			= TASK_GUI + TASK_INTERVAL;
	/// Priority of the Graphics task (see Graphics::GraphicsTask)
	const Tasks::tPriority TASK_GRAPHICS			= TASK_GAMESTATE + TASK_INTERVAL;
	/// Priority of the Gamestate2 task (see GameState::GameStateTask2)
	const Tasks::tPriority TASK_GAMESTATE2			= TASK_GRAPHICS + TASK_INTERVAL;
	/// Priority of the End task (see Tasks::EndTask)
	const Tasks::tPriority TASK_END					= TASK_GAMESTATE2 + TASK_INTERVAL;

	/// Macro used to create a priority after a standard one
#	define ATHENA_PRIORITY_AFTER(standard, offset)	(standard + TASK_RESERVED_INTERVAL + offset)
}

#endif
