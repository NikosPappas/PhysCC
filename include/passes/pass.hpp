#pragma once


// 🟢 ADDED: Forward Declaration
struct CompilerContext;

class Pass {
public:
    virtual ~Pass() = default;
    
    // 🟢 CHANGED: Returns bool (true = success)
    virtual bool run(CompilerContext& ctx) = 0;
};
