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

    Value* ObjClass::getMethod(const VirtualMachine& vm, uint16_t slot) const
    {
        return vm.getObject<Value>(methods + (sizeof(Value) * slot));
    }

    Value* ObjClass::getMethod(const VirtualMachine& vm, const std::string& name) const
    {
        auto it = methodsIndices.find(name);
        if (it == methodsIndices.end()) return nullptr;

        return getMethod(vm, it->second);
    }

    Value* ObjClass::getNativeMethod(const VirtualMachine& vm, uint16_t slot) const
    {
        return vm.getObject<Value>(nativeMethods + (sizeof(Value) * slot));
    }

    Value* ObjClass::getNativeMethod(const VirtualMachine& vm, const std::string& name) const
    {
        auto it = nativeMethodsIndices.find(name);
        if (it == nativeMethodsIndices.end()) return nullptr;

        return getNativeMethod(vm, it->second);
    }

    Value* ObjClass::getStaticField(const VirtualMachine& vm, uint16_t slot) const
    {
        return vm.getObject<Value>(staticFields + (sizeof(Value) * slot));
    }

    Value* ObjClass::getStaticField(const VirtualMachine& vm, const std::string& name) const
    {
        auto it = staticFieldsIndices.find(name);
        if (it == staticFieldsIndices.end()) return nullptr;

        std::cout << "slot : " << it->second << std::endl;

        return getStaticField(vm, it->second);
    }

    Value* ObjInstance::getNativeMethod(const VirtualMachine& vm, uint16_t slot) const
    {
        return vm.getObject<Value>(nativeMethods + (sizeof(Value) * slot));
    }

    Value* ObjInstance::getNativeMethod(const VirtualMachine& vm, const std::string& name) const
    {
        auto it = klass->nativeMethodsIndices.find(name);
        if (it == klass->nativeMethodsIndices.end()) return nullptr;

        return getNativeMethod(vm, it->second);
    }

    Value* ObjInstance::getField(const VirtualMachine& vm, uint16_t slot) const
    {
        return vm.getObject<Value>(fields + (sizeof(Value) * slot));
    }

    Value* ObjInstance::getField(const VirtualMachine& vm, const std::string& name) const
    {
        auto it = klass->fieldsIndices.find(name);
        if (it == klass->fieldsIndices.end()) return nullptr;

        return getField(vm, it->second);
    }

    bool ObjInstance::linkMethodNative(VirtualMachine& vm, const std::string& name, MethodNativeFn function)
    {
        auto it = klass->nativeMethodsIndices.find(name);
        if (it == klass->nativeMethodsIndices.end()) return false;

        AS_METHOD_NATIVE(vm, *getNativeMethod(vm, it->second)) = function;

        return true;
    }

    bool isObjType(const VirtualMachine& vm, const Value& value, ObjType type)
    {
        return IS_OBJ_PTR(value) && AS_OBJ(vm, value)->isType(type);
    }
}