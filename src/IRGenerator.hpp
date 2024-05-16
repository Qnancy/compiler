#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <exception>
#include <llvm/IR/Value.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/MC/TargetRegistry.h>


#include "AST.hpp"

// 全局上下文，用于创建 LLVM 模块和相关的对象。
extern llvm::LLVMContext Context;

// 一个辅助对象，用于简化生成 LLVM 指令的过程。
// 它会跟踪当前插入指令的位置，并提供方法来创建新的指令。
extern llvm::IRBuilder<> IRBuilder;

class IRLoopAttr {
public: 
    llvm::BasicBlock* condBlock_;
    llvm::BasicBlock* iterBlock_;
    llvm::BasicBlock* exitBlock_; 

    IRLoopAttr(llvm::BasicBlock* _condBlock_, llvm::BasicBlock* _iterBlock_, llvm::BasicBlock* _exitBlock_): 
        condBlock_(_condBlock_), iterBlock_(_iterBlock_), exitBlock_(_exitBlock_){}
};

//Symbol table
class SymbolEntry {
public:
    SymbolEntry(llvm::Function* Func, bool isDefined) : Content(Func), Type(FUNCTION), isFunctionDefined(isDefined){}
    SymbolEntry(llvm::Type* Ty) : Content(Ty), Type(TYPE) {}
    SymbolEntry(llvm::Value* Value, bool isPtr) : Content(Value), Type(isPtr ? PTR : VARIABLE) {}
    llvm::Function* GetFunction(void) { return this->Type == FUNCTION ? (llvm::Function*)Content : NULL; }
    void SetFunctionDefined() { this->isFunctionDefined = true;}
    bool GetFunctionDefined() { return this->isFunctionDefined;}
    llvm::Type* GetType(void) { return this->Type == TYPE ? (llvm::Type*)Content : NULL; }
    llvm::Value* GetVariable(void) { return this->Type == VARIABLE ? (llvm::Value*)Content : NULL; }
    llvm::Value* GetPTR(void) { return this->Type == PTR ? (llvm::Value*)Content : NULL; }
private:
    void* Content;
    enum {
        FUNCTION,
        TYPE,
        VARIABLE,
        PTR,
    } Type;

    bool isFunctionDefined = false;
};
using SymbolTable = std::map<std::string, SymbolEntry>;

class IRGenerator {
public:
    llvm::Module* Module;
    llvm::Function* curFunc_;
    std::vector<SymbolTable*> symbolTableStack_;	
    VarType* curVarType_; 
    std::vector<IRLoopAttr*> loopLevel_; 

public: 
    //Constructor
    IRGenerator(void);
    
    void GenerateCode(BaseAST*);
    void GenObjectCode(std::string);
    void DumpIRCode(std::string name);

    //Function
    void CreateFunc(llvm::FunctionType*, std::string name, llvm::Function* func, bool isDefined);
    bool CheckFuncDefined(std::string name);
    llvm::Function* FindFunction(std::string name);
    void EnterFunc(llvm::Function* curFunc);
    void LeaveFunc();
    llvm::Function* GetCurFunc();

    void PushSymbolTable(void);
    void PopSymbolTable(void);

    // Var
    bool CreateVar(std::string name, llvm::Value* value, bool isPtr=false);
	llvm::Value* FindVar(const std::string&);
    bool IsPtrVar(const std::string&);

    void SetCurVarType(VarType* curVarType);
    VarType* GetCurVarType();

    // Loop
    void EnterLoop(llvm::BasicBlock* condBlock, llvm::BasicBlock* iterBlock, llvm::BasicBlock* exitBlock); 
    void LeaveLoop(); 
    llvm::BasicBlock* BreakCurrentLoop(); 
    llvm::BasicBlock* ContinueCurrentLoop();
    
    bool SetFuncDefined(std::string name); 
};
