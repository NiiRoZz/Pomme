#include "Object.h"

namespace Pomme
{
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
        auto it = klass->nativeMethodsIndices.find(name);
        if (it == klass->nativeMethodsIndices.end()) return false;

        AS_METHOD_NATIVE(nativeMethods[it->second]) = function;

        return true;
    }
}