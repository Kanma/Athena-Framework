#include <UnitTest++.h>
#include <Athena/Tasks/TaskManager.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Log/LogManager.h>
#include <Athena-Core/Log/XMLLogListener.h>
#include "mocks/Task.h"

using namespace Athena;
using namespace Athena::Tasks;
using namespace Athena::Log;
using namespace Ogre;


struct TestEnvironment
{
	TestEnvironment()
	{
		pTaskManager = new TaskManager();

		CMockTask::uiGlobalStep = 0;
		CMockTask::uiTasksCount	= 0;
	}

	~TestEnvironment()
	{
		delete pTaskManager;
	}

    TaskManager* pTaskManager;
};


struct TestEnvironmentWith3Tasks
{
    TaskManager* pTaskManager;
	CMockTask* pTask1;
	CMockTask* pTask2;
	CMockTask* pTask3;

	TestEnvironmentWith3Tasks()
	{
		pTaskManager = new TaskManager();

		CMockTask::uiGlobalStep = 0;
		CMockTask::uiTasksCount	= 0;

		pTask1 = new CMockTask();
		pTaskManager->addTask(100, pTask1);

		pTask2 = new CMockTask();
		pTaskManager->addTask(200, pTask2);

		pTask3 = new CMockTask();
		pTaskManager->addTask(300, pTask3);
	}

	~TestEnvironmentWith3Tasks()
	{
		delete pTaskManager;
	}
};


SUITE(TaskManager)
{
	TEST_FIXTURE(TestEnvironment, AddTasks)
	{
		CHECK(pTaskManager->addTask(100, new CMockTask()));
		CHECK(pTaskManager->addTask(200, new CMockTask()));
		CHECK(pTaskManager->addTask(50, new CMockTask()));
	}


	TEST_FIXTURE(TestEnvironment, AddTasksWithSamePriorityFail)
	{
        // Disable error output on stderr
        Athena::Log::LogManager logManager;
        logManager.addListener(new XMLLogListener("test_log.xml"), true);

		CHECK(pTaskManager->addTask(100, new CMockTask()));
		CHECK(!pTaskManager->addTask(100, new CMockTask()));
	}


	TEST_FIXTURE(TestEnvironment, AddTasksWhichFailToStartFail)
	{
        // Disable error output on stderr
        Athena::Log::LogManager logManager;
        logManager.addListener(new XMLLogListener("test_log.xml"), true);

		CHECK(pTaskManager->addTask(100, new CMockTask()));

		CMockTask* pTask = new CMockTask();
		pTask->bCanStart = false;
		CHECK(!pTaskManager->addTask(200, pTask));
	}


	TEST_FIXTURE(TestEnvironmentWith3Tasks, Step)
	{
		CHECK_EQUAL(0, pTask1->uiStep);
		CHECK_EQUAL(0, pTask2->uiStep);
		CHECK_EQUAL(0, pTask3->uiStep);

		pTaskManager->step();

		CHECK_EQUAL(1, pTask1->uiStep);
		CHECK_EQUAL(2, pTask2->uiStep);
		CHECK_EQUAL(3, pTask3->uiStep);

		pTaskManager->step();

		CHECK_EQUAL(4, pTask1->uiStep);
		CHECK_EQUAL(5, pTask2->uiStep);
		CHECK_EQUAL(6, pTask3->uiStep);
	}


	TEST_FIXTURE(TestEnvironmentWith3Tasks, SuspendTask)
	{
		CHECK_EQUAL(0, pTask1->uiStep);
		CHECK_EQUAL(0, pTask2->uiStep);
		CHECK_EQUAL(0, pTask3->uiStep);

		pTaskManager->step();

		CHECK_EQUAL(1, pTask1->uiStep);
		CHECK_EQUAL(2, pTask2->uiStep);
		CHECK_EQUAL(3, pTask3->uiStep);

		CHECK(!pTask2->bSuspendCalled);
		CHECK(!pTask2->isSuspended());

		pTaskManager->suspendTask(200);

		CHECK(pTask2->bSuspendCalled);
		CHECK(pTask2->isSuspended());

		pTaskManager->step();

		CHECK_EQUAL(4, pTask1->uiStep);
		CHECK_EQUAL(2, pTask2->uiStep);
		CHECK_EQUAL(5, pTask3->uiStep);
	}


	TEST_FIXTURE(TestEnvironmentWith3Tasks, ResumeTask)
	{
		CHECK_EQUAL(0, pTask1->uiStep);
		CHECK_EQUAL(0, pTask2->uiStep);
		CHECK_EQUAL(0, pTask3->uiStep);

		pTaskManager->suspendTask(200);

		pTaskManager->step();

		CHECK_EQUAL(1, pTask1->uiStep);
		CHECK_EQUAL(0, pTask2->uiStep);
		CHECK_EQUAL(2, pTask3->uiStep);

		CHECK(pTask2->isSuspended());
		CHECK(!pTask2->bResumeCalled);

		pTaskManager->resumeTask(200);

		CHECK(!pTask2->isSuspended());
		CHECK(pTask2->bResumeCalled);

		pTaskManager->step();

		CHECK_EQUAL(3, pTask1->uiStep);
		CHECK_EQUAL(4, pTask2->uiStep);
		CHECK_EQUAL(5, pTask3->uiStep);
	}


	TEST_FIXTURE(TestEnvironmentWith3Tasks, RemoveTask)
	{
		CHECK_EQUAL(0, pTask1->uiStep);
		CHECK_EQUAL(0, pTask2->uiStep);
		CHECK_EQUAL(0, pTask3->uiStep);

		CHECK_EQUAL(3, CMockTask::uiTasksCount);

		CHECK(!pTask2->mustBeKilled());

		pTaskManager->removeTask(200);

		CHECK(pTask2->mustBeKilled());

		CHECK_EQUAL(3, CMockTask::uiTasksCount);

		pTaskManager->step();

		CHECK_EQUAL(2, CMockTask::uiTasksCount);

		CHECK_EQUAL(1, pTask1->uiStep);
		CHECK_EQUAL(2, pTask3->uiStep);
	}


	TEST_FIXTURE(TestEnvironmentWith3Tasks, KillAllTasks)
	{
		CHECK_EQUAL(3, CMockTask::uiTasksCount);

		pTaskManager->killAllTasks();

		CHECK_EQUAL(3, CMockTask::uiTasksCount);

		pTaskManager->step();

		CHECK_EQUAL(0, CMockTask::uiTasksCount);
	}
}

