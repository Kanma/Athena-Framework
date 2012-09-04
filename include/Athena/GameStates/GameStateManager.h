/** @file	GameStateManager.h
	@author	Philip Abbet

	Declaration of the class 'Athena::GameState::GameStateManager'
*/

#ifndef _ATHENA_GAMESTATES_GAMESTATEMANAGER_H_
#define _ATHENA_GAMESTATES_GAMESTATEMANAGER_H_

#include <Athena/Prerequisites.h>
#include <Athena/GameStates/IGameState.h>
#include <map>
#include <stack>


namespace Athena {
namespace GameStates {

//---------------------------------------------------------------------------------------
/// @brief	Represents the manager of the gamestates
///
/// This manager is responsible of the storing/destruction of the gamestates.
///
/// Each gamestate is identified by an ID assigned by the user. The gamestates can then be
/// retrieved and destroyed from this ID.
///
/// The active gamestates are organized in a stack. Only one of them (the one at the 'top'
/// of the stack) is active (processed). The following actions are possible:
///	  - Push a state on the stack: the previous active state is paused
///	  - Pop the active state from the stack: the state which is now at the top of the
///     stack is resumed, and become the active state
///	  - Pop all states from the stack: empty the stack
///	  - Change the active state: the active state is pop'd from the stack and the new one
///     is pushed immediatly (the state under the active state isn't resumed/paused)
///
///	Note that the Task Manager (Athena::Tasks::TaskManager) will stop the game when the
/// stack is empty!
///
/// It is also good to know that the update of the stack isn't done immediatly (when one
/// of these actions are requested), but later, at the end of the frame (see CGameStateTask2).
/// This is because a change of active gamestate at anytime can cause huge problems
/// in the other subsystems if special care isn't taken. With that delayed mecanism,
/// every subsystem has finished its processing for the current frame, and so is ready
/// to handle a change of the active gamestate.
///
/// At shutdown, the destruction of the remaining gamestates is handled by the manager.
//---------------------------------------------------------------------------------------
class ATHENA_FRAMEWORK_SYMBOL GameStateManager
{
	//_____ Construction / Destruction __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Constructor
    //-----------------------------------------------------------------------------------
	GameStateManager();

    //-----------------------------------------------------------------------------------
    /// @brief	Destructor
    //-----------------------------------------------------------------------------------
	~GameStateManager();


	//_____ Management of the states __________
public:
    //-----------------------------------------------------------------------------------
    /// @brief	Set the Task Manager that must be controlled by the Game State Manager
    /// @param	pTaskManager	The Task Manager
    //-----------------------------------------------------------------------------------
    inline void setTaskManager(Tasks::TaskManager* pTaskManager)
    {
        m_pTaskManager = pTaskManager;
    }

    //-----------------------------------------------------------------------------------
    /// @brief	Register a new game state
    /// @param	ID		The ID of the game's state
    /// @param	pState	The new game's state
    /// @return			true is successful
    //-----------------------------------------------------------------------------------
	bool registerState(Utils::tID ID, IGameState* pState);

    //-----------------------------------------------------------------------------------
    /// @brief	Change the current state
    /// @param	ID	The ID of the new game's state
    //-----------------------------------------------------------------------------------
	void changeState(Utils::tID ID);

    //-----------------------------------------------------------------------------------
    /// @brief	Change the current state without removing the previous one (it will be paused)
    /// @param	ID	The ID of the new gamestate
    //-----------------------------------------------------------------------------------
	void pushState(Utils::tID ID);

    //-----------------------------------------------------------------------------------
    /// @brief	Remove the current state and go back to the previous one (it will be resumed)
    //-----------------------------------------------------------------------------------
	void popState();

    //-----------------------------------------------------------------------------------
    /// @brief	Remove all the states
    //-----------------------------------------------------------------------------------
	void popAllStates(bool bKillAllTasks = true);

    //-----------------------------------------------------------------------------------
    /// @brief	Called by the task CGameStateTask to process the active gamestate
    //-----------------------------------------------------------------------------------
	void processCurrentState();

    //-----------------------------------------------------------------------------------
    /// @brief	Called by the task CGameStateTask2 to update the stack
    //-----------------------------------------------------------------------------------
	void update();

private:
    //-----------------------------------------------------------------------------------
    /// @brief	Change the current state, called when necessary by GameStateManager::update
    //-----------------------------------------------------------------------------------
	void doChangeCommand();

    //-----------------------------------------------------------------------------------
    /// @brief	Change the current state without removing the previous one (it will be paused),
    ///			called when necessary by GameStateManager::update
    //-----------------------------------------------------------------------------------
	void doPushCommand();

    //-----------------------------------------------------------------------------------
    /// @brief	Remove the current state and go back to the previous one (it will be resumed),
    ///			called when necessary by GameStateManager::update
    //-----------------------------------------------------------------------------------
	void doPopCommand();

    //-----------------------------------------------------------------------------------
    /// @brief	Remove all the states, called when necessary by GameStateManager::update
    //-----------------------------------------------------------------------------------
	void doPopAllCommand(bool bKillAllTasks);


	//_____ Internal types __________
private:
	//-----------------------------------------------------------------------------------
	/// @brief	Internal commands used for storing a request of change of the stack (for
	///			the delayed mecanism)
	//-----------------------------------------------------------------------------------
	enum tCommand
	{
		COMMAND_NONE,			///< No change to do
		COMMAND_CHANGE,			///< Must change the active state
		COMMAND_PUSH,			///< Must push a state on the stack
		COMMAND_POP,			///< Must pop a state from the stack
		COMMAND_POP_ALL,		///< Must pop all the states from the stack
		COMMAND_POP_ALL_KILL	///< Must pop all the states from the stack and kill all the tasks
	};


	//_____ Attributes __________
private:
	std::map<Utils::tID, IGameState*>	m_states;		///< The list of gamestates registered
	std::stack<IGameState*>				m_stack;		///< The stack of gamestates
	tCommand							m_command;		///< The command to execute at the next update
	Utils::tID							m_ID;			///< The state on which execute the command
    Tasks::TaskManager*                 m_pTaskManager; ///< The Task Manager to control
};

}
}

#endif
