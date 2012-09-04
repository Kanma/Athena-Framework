#include <UnitTest++.h>
#include <Athena/GameStates/GameStateManager.h>
#include <Athena/Tasks/TaskManager.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Log/XMLLogListener.h>
#include "mocks/GameState.h"

using namespace Athena;
using namespace Athena::GameStates;
using namespace Athena::Log;
using namespace Ogre;


struct GameStatesTestEnvironment
{
    GameStateManager* pGameStateManager;

	GameStatesTestEnvironment()
	{
		pGameStateManager = new GameStateManager();
	}

	~GameStatesTestEnvironment()
	{
		delete pGameStateManager;
	}
};



struct GameStatesTestEnvironmentWith3States
{
    GameStateManager* pGameStateManager;
	CMockGameState* pState1;
	CMockGameState* pState2;
	CMockGameState* pState3;


	GameStatesTestEnvironmentWith3States()
	{
		pGameStateManager = new GameStateManager();

		pState1 = new CMockGameState();
		pGameStateManager->registerState(1, pState1);

		pState2 = new CMockGameState();
		pGameStateManager->registerState(2, pState2);

		pState3 = new CMockGameState();
		pGameStateManager->registerState(3, pState3);
	}

	~GameStatesTestEnvironmentWith3States()
	{
		delete pGameStateManager;
	}
};



SUITE(GameStatesManager)
{
	TEST_FIXTURE(GameStatesTestEnvironment, Fixture)
	{
		CHECK(pGameStateManager);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, Fixture)
	{
		CHECK(pGameStateManager);
		CHECK(pState1);
		CHECK(pState2);
		CHECK(pState3);
	}


	TEST_FIXTURE(GameStatesTestEnvironment, Register)
	{
		CHECK(pGameStateManager->registerState(1, new CMockGameState()));
		CHECK(pGameStateManager->registerState(2, new CMockGameState()));
		CHECK(pGameStateManager->registerState(3, new CMockGameState()));
	}


	TEST_FIXTURE(GameStatesTestEnvironment, RegisterStatesWithSameIDFail)
	{
        // Disable error output on stderr
        Athena::Log::LogManager logManager;
        logManager.addListener(new XMLLogListener("test_log.xml"), true);

		CHECK(pGameStateManager->registerState(1, new CMockGameState()));
		CHECK(!pGameStateManager->registerState(1, new CMockGameState()));
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, PushOneState)
	{
		pGameStateManager->pushState(1);

		CHECK(pState1->bEnterCalled);
		CHECK(!pState2->bEnterCalled);
		CHECK(!pState3->bEnterCalled);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, PushTwoStates)
	{
		pGameStateManager->pushState(1);
		pGameStateManager->pushState(2);

		CHECK(pState1->bEnterCalled);
		CHECK(!pState1->bPauseCalled);
		CHECK(!pState2->bEnterCalled);

		pState1->reset();

		pGameStateManager->update();

		CHECK(pState1->bPauseCalled);
		CHECK(pState2->bEnterCalled);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, PushThreeStates)
	{
		pGameStateManager->pushState(1);
		pGameStateManager->pushState(2);

		pGameStateManager->update();

		pGameStateManager->pushState(3);

		pState1->reset();
		pState2->reset();

		pGameStateManager->update();

		CHECK(pState2->bPauseCalled);
		CHECK(pState3->bEnterCalled);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, PushThreeStatesOnSameFrame)
	{
		pGameStateManager->pushState(1);
		pGameStateManager->pushState(2);
		pGameStateManager->pushState(3);

		pState1->reset();
		pState2->reset();
		pState3->reset();

		pGameStateManager->update();

		CHECK(pState1->bPauseCalled);
		CHECK(!pState2->bEnterCalled);
		CHECK(pState3->bEnterCalled);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, Pop)
	{
		pGameStateManager->pushState(1);
		pGameStateManager->pushState(2);

		pGameStateManager->update();

		pState1->reset();
		pState2->reset();

		pGameStateManager->popState();

		CHECK(!pState1->bResumeCalled);
		CHECK(!pState2->bExitCalled);

		pGameStateManager->update();

		CHECK(pState1->bResumeCalled);
		CHECK(pState2->bExitCalled);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, PopAll)
	{
		pGameStateManager->pushState(1);
		pGameStateManager->pushState(2);

		pGameStateManager->update();

		pGameStateManager->pushState(3);

		pGameStateManager->update();

		pState1->reset();
		pState2->reset();
		pState3->reset();

		pGameStateManager->popAllStates();

		CHECK(!pState1->bExitCalled);
		CHECK(!pState2->bExitCalled);
		CHECK(!pState3->bExitCalled);

		pGameStateManager->update();

		CHECK(pState1->bExitCalled);
		CHECK(pState2->bExitCalled);
		CHECK(pState3->bExitCalled);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, Change)
	{
		pGameStateManager->pushState(1);
		pGameStateManager->pushState(2);

		pGameStateManager->update();

		pState1->reset();
		pState2->reset();

		pGameStateManager->changeState(3);

		CHECK(!pState2->bExitCalled);
		CHECK(!pState3->bEnterCalled);

		pGameStateManager->update();

		CHECK(pState2->bExitCalled);
		CHECK(pState3->bEnterCalled);
	}


	TEST_FIXTURE(GameStatesTestEnvironmentWith3States, ProcessCurrent)
	{
		pGameStateManager->pushState(1);

		CHECK(!pState1->bProcessCalled);

		pGameStateManager->processCurrentState();

		CHECK(pState1->bProcessCalled);
	}
}

