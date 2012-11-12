# Retrieve the version of each dynamic library needed by the demos
get_target_property(ATHENA_MATH_VERSION Athena-Math SOVERSION)
get_target_property(ATHENA_CORE_VERSION Athena-Core SOVERSION)
get_target_property(ATHENA_ENTITIES_VERSION Athena-Entities SOVERSION)
get_target_property(ATHENA_GRAPHICS_VERSION Athena-Graphics SOVERSION)
get_target_property(ATHENA_PHYSICS_VERSION Athena-Physics SOVERSION)
get_target_property(ATHENA_INPUTS_VERSION Athena-Inputs SOVERSION)
get_target_property(ATHENA_SCRIPTING_VERSION Athena-Scripting SOVERSION)
get_target_property(ATHENA_FRAMEWORK_VERSION Athena-Framework SOVERSION)
get_target_property(V8_VERSION v8 SOVERSION)


add_subdirectory(created_window)
add_subdirectory(external_window)
