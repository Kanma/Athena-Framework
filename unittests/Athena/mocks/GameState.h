/** @file   MockGameState.h
    @author Philip Abbet

    Definition of the class 'MockGameState'
*/

#ifndef _MOCKGAMESTATE_H_
#define _MOCKGAMESTATE_H_

#include <Athena/Prerequisites.h>
#include <Athena/GameStates/IGameState.h>


//---------------------------------------------------------------------------------------
/// @brief  Mock implementation of a game state
//---------------------------------------------------------------------------------------
class MockGameState: public Athena::GameStates::IGameState
{
    //_____ Construction / Destruction __________
public:
    MockGameState()
    : bEnterCalled(false), bExitCalled(true), bPauseCalled(false), bResumeCalled(false),
      bProcessCalled(false)
    {
    }

    virtual ~MockGameState()
    {
    }


    //_____ Methods to implement __________
public:
    virtual void enter()
    {
        bEnterCalled = true;
    }

    virtual void exit()
    {
        bExitCalled = true;
    }

    virtual void pause()
    {
        bPauseCalled = true;
    }

    virtual void resume()
    {
        bResumeCalled = true;
    }

    virtual void process()
    {
        bProcessCalled = true;
    }

    void reset()
    {
        bEnterCalled    = false;
        bExitCalled     = false;
        bPauseCalled    = false;
        bResumeCalled   = false;
        bProcessCalled  = false;
    }


    //_____ Attributes __________
public:
    bool bEnterCalled;
    bool bExitCalled;
    bool bPauseCalled;
    bool bResumeCalled;
    bool bProcessCalled;
};

#endif
