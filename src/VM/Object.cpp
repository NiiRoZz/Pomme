#include "Object.h"
#include "VirtualMachine.h"

#include <cassert>

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

    PommeString::PommeString(VirtualMachine& vm, ObjInstance* instance)
    {
        instance->linkMethodNative(vm.getFunctionName("operator+", "int"), [&] (VirtualMachine& vm, int argcount, ObjInstance* instance, Value* args) {
            return pommeOperatorPlus(vm, argcount, instance, args);
        });
    }

    Value PommeString::pommeOperatorPlus(VirtualMachine& vm, int argcount, ObjInstance* instance, Value* args)
    {
        assert(argcount == 1);
        //assert(IS_INSTANCE(args[0]) && AS_INSTANCE(args[0])->klass-> == ClassType::STRING);

        return OBJ_VAL(instance);
    }
}