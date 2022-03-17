#pragma once

#define Q_DECLARE_INSTANCE(ClassName)\
public:\
static ClassName&instance()\
{\
    static ClassName*static_##ClassName=nullptr;\
    if(static_##ClassName==nullptr)\
    static_##ClassName=new ClassName(nullptr);\
    return*static_##ClassName;\
}\
static ClassName&i()\
{\
    return instance();\
}
