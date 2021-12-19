#include "Object.h"
#include "VirtualMachine.h"

#include <cassert>

namespace Pomme
{
    const char* ObjTypeToCStr(ObjType type)
    {
        switch (type)
        {
            case ObjType::OBJ_BOUND_METHOD: return "OBJ_BOUND_METHOD";
            case ObjType::OBJ_CLASS: return "OBJ_CLASS";
            case ObjType::OBJ_FUNCTION: return "OBJ_FUNCTION";
            case ObjType::OBJ_INSTANCE: return "OBJ_INSTANCE";
            case ObjType::OBJ_GLOBAL_NATIVE: return "OBJ_GLOBAL_NATIVE";
            case ObjType::OBJ_METHOD_NATIVE: return "OBJ_METHOD_NATIVE";
            case ObjType::OBJ_METHOD_PRIMITIVE_NATIVE: return "OBJ_METHOD_PRIMITIVE_NATIVE";
            case ObjType::OBJ_STRING: return "OBJ_STRING";
        }

        assert(false);
        return "";
    }

    Value* ObjClass::getStaticField(const std::string& name)
    {
        auto it = staticFieldsIndices.find(name);
        if (it == staticFieldsIndices.end()) return nullptr;

        return &staticFields[it->second];
    }

    Value* ObjInstance::getField(const std::string& name)
    {
        auto it = klass->fieldsIndices.find(name);
        if (it == klass->fieldsIndices.end()) return nullptr;

        return &fields[it->second];
    }

    Value* ObjInstance::getStaticField(const std::string& name)
    {
        return klass->getStaticField(name);
    }

    bool ObjInstance::linkMethodNative(const std::string& name, MethodNativeFn function)
    {
        /*auto it = klass->nativeMethodsIndices.find(name);
        if (it == klass->nativeMethodsIndices.end()) return false;

        AS_METHOD_NATIVE(nativeMethods[it->second]) = function;*/

        return false;
    }

    bool isObjType(const VirtualMachine& vm, const Value& value, ObjType type)
    {
        return IS_OBJ_PTR(value) && AS_OBJ(vm, value)->isType(type);
    }
}