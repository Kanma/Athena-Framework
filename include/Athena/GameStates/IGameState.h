/** @file	IGameState.h
	@author	Philip Abbet

	Declaration of the interface 'Athena::GameStates::IGameState'
*/

#ifndef _ATHENA_GAMESTATES_IGAMESTATE_H_
#define _ATHENA_GAMESTATES_IGAMESTATE_H_

#include <Athena/Prerequisites.h>

namespace Athena {
namespace GameStates {

//---------------------------------------------------------------------------------------
/// @brief	Interface for the gamestates
//---------------------------------------------------------------------------------------
class ATHENA_SYMBOL IGameState
{
	//_____ Construction / Destruction __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Destructor
	//-----------------------------------------------------------------------------------
	virtual ~IGameState() {};

	
	//_____ Methods to be overriden by each state __________
public:
	//-----------------------------------------------------------------------------------
	/// @brief	Called when the game enters the state
	//-----------------------------------------------------------------------------------
	virtual void enter() = 0;

	//-----------------------------------------------------------------------------------
	/// @brief	Called when the game quits the state
	//-----------------------------------------------------------------------------------
	virtual void exit() = 0;

	//-----------------------------------------------------------------------------------
	/// @brief	Called to pause the state
	//-----------------------------------------------------------------------------------
	virtual void pause() = 0;

	//-----------------------------------------------------------------------------------
	/// @brief	Called to resume a paused state
	//-----------------------------------------------------------------------------------
	virtual void resume() = 0;

	//-----------------------------------------------------------------------------------
	/// @brief	Called when the state must be processed, once per frame
	//-----------------------------------------------------------------------------------
	virtual void process() = 0;
};

}
}

#endif
