/** @file   module.cpp
    @author Philip Abbet

    Entry point of the Javascript module of Athena::Entities
*/

#include <v8.h>
#include <Athena-Scripting/ScriptingManager.h>
#include <Athena/Prerequisites.h>
#include <string>

using namespace v8;
using namespace Athena::Scripting;
using namespace Athena;


/*********************************** EXTERNAL FUNCTIONS *********************************/

extern bool bind_time_functions(v8::Handle<v8::Object> parent);


/****************************** INITIALISATION OF THE MODULE ****************************/

extern "C" {

    bool MODULE_INITIALISATION_FUNCTION init_module(v8::Handle<v8::Object> parent, const std::string& modulePath)
    {
        v8::HandleScope handle_scope;

        v8::Handle<v8::Context> context = parent->CreationContext();
        v8::Handle<v8::Object> ns = context->Global()->Get(v8::String::New("Athena"))->ToObject();

        parent->Set(v8::String::New("VERSION"), v8::String::New(Athena::VERSION));

        return bind_time_functions(parent);
    }
}
