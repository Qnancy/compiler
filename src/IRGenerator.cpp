#include "AST.hpp"
#include "IRGenerator.hpp"

// 全局上下文，用于创建 LLVM 模块和相关的对象。
llvm::LLVMContext Context;

// 一个辅助对象，用于简化生成 LLVM 指令的过程。
// 它会跟踪当前插入指令的位置，并提供方法来创建新的指令。
llvm::IRBuilder<> IRBuilder(Context);

IRGenerator::IRGenerator(){
    Module = new llvm::Module("main", Context);

    curFunc_ = NULL;
    curVarType_ = NULL; 
    
}

//Function
//遍历整个符号表，看是否已经定义了同名函数
bool IRGenerator::CheckFuncDefined(std::string name) {
    if (this->symbolTableStack_.empty()) {
        return false; 
    }
    for (auto symbolTable : this->symbolTableStack_) {
        auto iter = symbolTable->find(name);
        if (iter != symbolTable->end()) {
            if (iter->second.GetFunctionDefined())
                return true;
        }
    }
    return false;
}



//遍历整个符号表，看是否有该函数的声明
llvm::Function* IRGenerator::FindFunction(std::string name) {
	if (this->symbolTableStack_.empty()) 
        return NULL;
    for (auto symbolTable : this->symbolTableStack_) {
        auto iter = symbolTable->find(name);
        if (iter != symbolTable->end()) {
            return iter->second.GetFunction();
        }
    }
	return NULL;
}

//标注函数已经定义
bool IRGenerator::SetFuncDefined(std::string name) {
    if (this->symbolTableStack_.empty()) {
        return false; 
    }
    for (auto symbolTable : this->symbolTableStack_) {
        auto iter = symbolTable->find(name);
        if (iter != symbolTable->end()) {
            iter->second.SetFunctionDefined();
            return true;
        }
    }
}

//创建函数
void IRGenerator::CreateFunc(llvm::FunctionType* type, std::string name, llvm::Function* func, bool isDefined){
    if (this->symbolTableStack_.empty()) {
        throw std::logic_error("No Symbol Table Found");
    }
    auto topSymbolTable = this->symbolTableStack_.back();
    if (topSymbolTable->find(name) != topSymbolTable->end()) {
        throw std::logic_error("Function with the same name already exists: "+name);
    }
    topSymbolTable->insert({name, SymbolEntry(func, isDefined)});
}

void IRGenerator::EnterFunc(llvm::Function* curFunc) {
    this->curFunc_ = curFunc; 
}

void IRGenerator::LeaveFunc() {
    this->curFunc_ = NULL; 
}

void IRGenerator::PushSymbolTable() {
    this->symbolTableStack_.push_back(new SymbolTable);
}

void IRGenerator::PopSymbolTable() {
	if (this->symbolTableStack_.empty()) 
        return;
	delete this->symbolTableStack_.back();
	this->symbolTableStack_.pop_back();
}

//Variable
//创建变量
bool IRGenerator::CreateVar(std::string name, llvm::Value* value, bool isPtr){
    if (this->symbolTableStack_.empty()) {
        throw std::logic_error("No Symbol Table Found");
    }
    auto topSymbolTable = this->symbolTableStack_.back();
    if (topSymbolTable->find(name) != topSymbolTable->end()) {
       return false;
    }
    topSymbolTable->insert({name, SymbolEntry(value, isPtr)});
    return true;
}

llvm::Value* IRGenerator::FindVar(const std::string& name){
    if (this->symbolTableStack_.empty()) {
        return NULL;
    }
    for (auto symbolTable = this->symbolTableStack_.end() - 1; symbolTable >= this->symbolTableStack_.begin(); symbolTable--) {
        auto iter = (*symbolTable)->find(name);
        if (iter != (*symbolTable)->end()) {
            if (iter->second.GetPTR()) {
                return iter->second.GetPTR();
            }else{
                return iter->second.GetVariable();
            }
        }
    }
    return NULL;
}

bool IRGenerator::IsPtrVar(const std::string& name) {
    if (this->symbolTableStack_.empty()) {
        return false;
    }
    for (auto symbolTable = this->symbolTableStack_.end() - 1; symbolTable >= this->symbolTableStack_.begin(); symbolTable--) {
        auto iter = (*symbolTable)->find(name);
        if (iter != (*symbolTable)->end()) {
            return iter->second.GetPTR();
        }
    }
    return false;
}


llvm::Function* IRGenerator::GetCurFunc() {
    return this->curFunc_; 
}

void IRGenerator::SetCurVarType(VarType* curVarType) {
    this->curVarType_ = curVarType;
}

VarType* IRGenerator::GetCurVarType() {
    return this->curVarType_;
}

void IRGenerator::EnterLoop(llvm::BasicBlock* condBlock, llvm::BasicBlock* iterBlock, llvm::BasicBlock* exitBlock) {
    this->loopLevel_.push_back(new IRLoopAttr(condBlock, iterBlock, exitBlock));
}

void IRGenerator::LeaveLoop() {
    if (this->loopLevel_.empty()) {
        throw std::logic_error("No Loop Found");
    }
    delete this->loopLevel_.back();
    this->loopLevel_.pop_back();
}

llvm::BasicBlock* IRGenerator::BreakCurrentLoop() {
    auto currentLoop = this->loopLevel_[this->loopLevel_.size()-1];
    return currentLoop->exitBlock_; 
}

llvm::BasicBlock* IRGenerator::ContinueCurrentLoop() {
    auto currentLoop = this->loopLevel_[this->loopLevel_.size()-1];
    return currentLoop->iterBlock_?currentLoop->iterBlock_:currentLoop->condBlock_; 
}

// llvm::Function* IRGenerator::CallFunction(std::string Name) {
//     if (this->funcList_.size() == 0) {
//         throw std::logic_error("Cannot find the function: "+Name);
//         return NULL;
//     }
//     for (auto iter = this->funcList_[this->funcList_.size()-1]; iter >= this->funcList_[0]; iter--) {
//         if (iter->getName() == Name){
//             if (iter->getDefined()) 
//                 return iter->getFunc();
//             else {
//                 throw std::logic_error("Function declared but not defined: "+Name);
//                 return NULL;
//             }
//         }
//     }
//     throw std::logic_error("Cannot find the function: "+Name);
//     return NULL;
// }


void IRGenerator::GenerateCode(BaseAST* root) {
    this->PushSymbolTable();
    root->IRGen(*this);
	this->Module->print(llvm::outs(), NULL);
    this->PopSymbolTable();
}
void IRGenerator::GenObjectCode(std::string FileName) {
	auto TargetTriple = llvm::sys::getDefaultTargetTriple();
	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmParsers();
	llvm::InitializeAllAsmPrinters();
	std::string Error;
	auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);
	if (!Target) {
		throw std::runtime_error(Error);
		return;
	}
	auto CPU = "generic";
	auto Features = "";
	llvm::TargetOptions opt;
	auto RM = llvm::Optional<llvm::Reloc::Model>();
	auto TargetMachine = Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);
	Module->setDataLayout(TargetMachine->createDataLayout());
	Module->setTargetTriple(TargetTriple);
	std::error_code EC;
	llvm::raw_fd_ostream Dest(FileName, EC, llvm::sys::fs::OF_None);
	if (EC) {
		throw std::runtime_error("Could not open file: " + EC.message());
		return;
	}
	auto FileType = llvm::CGFT_ObjectFile;
	llvm::legacy::PassManager PM;
	if (TargetMachine->addPassesToEmitFile(PM, Dest, nullptr, FileType)) {
		throw std::runtime_error("TargetMachine can't emit a file of this type");
		return;
	}
	PM.run(*Module);
	Dest.flush();
}

// void IRGenerator::GenObjectCode(std::string outputfile) {
// 	//获取描述编译器的目标平台、操作系统和环境等信息
// 	auto TargetTriple = llvm::sys::getDefaultTargetTriple();
// 	//根据llvm文档提供的初始化
//     llvm::InitializeAllTargetInfos();
//     llvm::InitializeAllTargets();
//     llvm::InitializeAllTargetMCs();
//     llvm::InitializeAllAsmParsers();
//     llvm::InitializeAllAsmPrinters();

// 	//根据TargetTriple查找目标平台
//     std::string Error;
//     auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

//     llvm::TargetOptions opt;
//     auto RM = llvm::Optional<llvm::Reloc::Model>();
//     auto TargetMachine = Target->createTargetMachine(TargetTriple, "", "", opt, RM);
// 	//设置数据布局
//     Module->setDataLayout(TargetMachine->createDataLayout());
//     Module->setTargetTriple(TargetTriple);

// 	//将数据写入文件
// 	std::error_code errCode;
//     llvm::raw_fd_ostream OPFile(outputfile, errCode, llvm::sys::fs::OF_None);
//     llvm::legacy::PassManager PM;
//     TargetMachine->addPassesToEmitFile(PM, OPFile, nullptr, llvm::CGFT_ObjectFile);
//     PM.run(*Module);

//     OPFile.flush();
// }

void IRGenerator::DumpIRCode(std::string FileName) {
	if (FileName == "") FileName = "-";
	std::error_code EC;
	llvm::raw_fd_ostream Out(FileName, EC);
	this->Module->print(Out, NULL);
}