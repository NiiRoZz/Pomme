#pragma once

namespace Pomme
{
    typedef struct Obj Obj;
    typedef struct ObjString ObjString;

    enum class ValueType: uint8_t
    {
        VAL_BOOL,
        VAL_NIL, 
        VAL_NULL,
        VAL_NUMBER,
        VAL_OBJ,
    };

    struct Value
    {
        ValueType type;

        union 
        {
            bool boolean;
            double number;
            Obj* obj;
        } as; 
    };

    #define IS_BOOL(value)    ((value).type == ValueType::VAL_BOOL)
    #define IS_NIL(value)     ((value).type == ValueType::VAL_NIL)
    #define IS_NULL(value)     ((value).type == ValueType::VAL_NULL)
    #define IS_NUMBER(value)  ((value).type == ValueType::VAL_NUMBER)
    #define IS_OBJ(value)     ((value).type == ValueType::VAL_OBJ)

    #define AS_BOOL(value)    ((value).as.boolean)
    #define AS_NUMBER(value)  ((value).as.number)
    #define AS_OBJ(value)     ((value).as.obj)

    #define BOOL_VAL(value)   ((Value){ValueType::VAL_BOOL, {.boolean = value}})
    #define NIL_VAL           ((Value){ValueType::VAL_NIL, {.number = 0}})
    #define NULL_VAL          ((Value){ValueType::VAL_NULL, {.number = 0}})
    #define NUMBER_VAL(value) ((Value){ValueType::VAL_NUMBER, {.number = value}})
    #define OBJ_VAL(object)   ((Value){ValueType::VAL_OBJ, {.obj = (Obj*)object}})
}