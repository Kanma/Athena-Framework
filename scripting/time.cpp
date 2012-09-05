#include <Athena/Engine.h>
#include <Athena/Tasks/TaskManager.h>
#include <Athena-Scripting/Utils.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <v8.h>

using namespace Athena;
using namespace Athena::Scripting;
using namespace v8;


/************************************** FUNCTIONS ***************************************/

v8::Handle<v8::Value> GetElapsedSeconds(const v8::Arguments& args)
{
    Engine* pEngine = Engine::getSingletonPtr();

    if (pEngine && pEngine->getTaskManager())
        return v8::Number::New(pEngine->getTaskManager()->getElapsedSeconds());

    return v8::Handle<v8::Value>();
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> GetElapsedMilliseconds(const v8::Arguments& args)
{
    Engine* pEngine = Engine::getSingletonPtr();

    if (pEngine && pEngine->getTaskManager())
        return v8::Uint32::New(pEngine->getTaskManager()->getElapsedMilliseconds());

    return v8::Handle<v8::Value>();
}

//-----------------------------------------------------------------------

v8::Handle<v8::Value> GetElapsedMicroseconds(const v8::Arguments& args)
{
    Engine* pEngine = Engine::getSingletonPtr();

    if (pEngine && pEngine->getTaskManager())
        return v8::Uint32::New(pEngine->getTaskManager()->getElapsedMicroseconds());

    return v8::Handle<v8::Value>();
}


/************************************ BINDING FUNCTION **********************************/

bool bind_time_functions(v8::Handle<v8::Object> parent)
{
    ScriptingManager* pManager = ScriptingManager::getSingletonPtr();

    return parent->Set(v8::String::New("elapsedSeconds"), v8::FunctionTemplate::New(GetElapsedSeconds)->GetFunction()) &&
           parent->Set(v8::String::New("elapsedMilliseconds"), v8::FunctionTemplate::New(GetElapsedMilliseconds)->GetFunction()) &&
           parent->Set(v8::String::New("elapsedMicroseconds"), v8::FunctionTemplate::New(GetElapsedMicroseconds)->GetFunction());
}
