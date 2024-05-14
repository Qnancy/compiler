#include "AST.hpp"
#include "IRGenerator.hpp"

// 全局上下文，用于创建 LLVM 模块和相关的对象。
llvm::LLVMContext Context;

// 一个辅助对象，用于简化生成 LLVM 指令的过程。
// 它会跟踪当前插入指令的位置，并提供方法来创建新的指令。
llvm::IRBuilder<> IRBuilder(Context);

IRGenerator::IRGenerator(){
    Module = new llvm::Module("main", Context);

    bbCreatePreBrSignal_ = true; 
    curBasicBlock_ = NULL; 
    curFunc_ = NULL;
    curVarType_ = NULL; 
}

void IRGenerator::CreateVar(VarType type, const std::string& name, llvm::Value* value, bool isPtr){
    // Check for name conflicts within the current scope
    int varCnt = this->varList_.size(); 
    int activeCnt = (this->curBasicBlock_ != nullptr) ? this->curBasicBlock_->varCnt_ : varCnt;
    
    // Iterate through the variables in reverse order to check for name conflicts
    for (int i = 0; i < activeCnt; ++i) {
        IRVarAttr* var = this->varList_[varCnt - 1 - i];
        if (var->name_ == name) {
            // A variable with the same name already exists in the current scope
            throw std::logic_error("A variable with name '" + name + "' already exists.");
        }
    }
    // Create the new variable attribute and add it to the list
    IRVarAttr* newVar = new IRVarAttr(type, name, value, isPtr);
    this->varList_.push_back(newVar);

    // Update the count of variables in the current basic block if one exists
    if (this->curBasicBlock_) {
        this->curBasicBlock_->varCnt_ += 1;
    }
}

void IRGenerator::ClearVar() {
    if (this->curBasicBlock_)
        for (int i = 0; i < this->curBasicBlock_->varCnt_; i++) {
            auto var = this->varList_[this->varList_.size()-1];
            this->varList_.pop_back();
            delete var; 
        }
}

llvm::Value* IRGenerator::FindVar(const std::string& name){
    // If there are no variables, return NULL immediately.
	if(this->varList_.empty()){
		return NULL;
	}
    // Iterate through the list of variables in reverse order.
	for(auto symbol = this->varList_.end() - 1; symbol >= this->varList_.begin(); symbol--){
		if((*symbol)->name_ == name){
			return (*symbol)->value_;
		}
	}
    // If no match is found, return NULL.
	return NULL;
}

bool IRGenerator::IsPtrVar(const std::string& name) {
    if(this->varList_.empty()){
		return false;
	}
	for(auto symbol = this->varList_.end() - 1; symbol >= this->varList_.begin(); symbol--){
		if((*symbol)->name_ == name){
			return (*symbol)->isPtr_; 
		}
	}
	return false;
}

void IRGenerator::RemainFutureVar(VarType type, const std::string& name, llvm::Value* value, bool isPtr) {
    // Check if a variable with the same name already exists in the future variables list
    int varCnt = this->varListForFuture_.size(); 
    for (const auto& var : this->varListForFuture_) {
        if (var->name_ == name) {
            // If a variable with the same name already exists, throw an exception
            throw std::logic_error("Already Created a Variable with Name: " + name);
        }
    }
    this->varListForFuture_.push_back(new IRVarAttr(type, name, value, isPtr));
}

void IRGenerator::CreateFutureVars() {
    int argCnt = this->varListForFuture_.size();
    for (int i = 1; i <= argCnt; i++) {
        auto arg = this->varListForFuture_[argCnt-i];
        auto AllocMem = IRBuilder.CreateAlloca(arg->type_.ToLLVMType(*this), 0, arg->name_);
        IRBuilder.CreateStore(arg->value_, AllocMem);
        this->CreateVar(arg->type_, arg->name_, AllocMem, arg->isPtr_); 
        this->varListForFuture_.pop_back();
        delete arg; 
    }
}

void IRGenerator::SetCurFunc(llvm::Function* curFunc) {
    this->curFunc_ = curFunc; 
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

void IRGenerator::SetPreBrSignal() {
    this->bbCreatePreBrSignal_ = true; 
}

bool IRGenerator::GetPreBrSignal() {
    return this->bbCreatePreBrSignal_; 
}

bool IRGenerator::ClearPreBrSignal() {
    bool bbCreatePreBrSignal = this->bbCreatePreBrSignal_; 
    this->bbCreatePreBrSignal_ = false;
    return bbCreatePreBrSignal;
}


Block* IRGenerator::GetBasicBlock() {
    return this->curBasicBlock_; 
}

void IRGenerator::SetBasicBlock(Block* newBasicBlock){
    this->curBasicBlock_ = newBasicBlock; 
}

void IRGenerator::EnterLoop(llvm::BasicBlock* condBlock, llvm::BasicBlock* iterBlock, llvm::BasicBlock* exitBlock) {
    this->loopLevel_.push_back(new IRLoopAttr(condBlock, iterBlock, exitBlock));
}

void IRGenerator::LeaveCurrentLoop() {
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

void IRGenerator::CreateFunc(llvm::FunctionType* type, std::string name, llvm::Function* func, bool isDefined){
    if(this->FindFunction(name)){
        return;
    }
    this->funcList_.push_back(new IRFuncAttr(type, name, func, isDefined));
}

void IRGenerator::DiscardFunc(int cnt) {
    for (int i = 0; i < cnt; i++) {
        auto func = this->funcList_[this->funcList_.size()-1];
		this->funcList_.pop_back();
        delete func; 
    }
}

llvm::Function* IRGenerator::FindFunction(std::string name) {
	if (this->funcList_.empty()) 
        return NULL;
    for (auto iter = this->funcList_.end()-1; iter >= this->funcList_.begin(); iter--) {
        if ((*iter)->getName() == name){
            return (*iter)->getFunc();
        }
    }
	return NULL;
}

bool IRGenerator::IsFuncDefined(std::string name) {
	if (this->funcList_.empty()) 
        return false;
    for (auto iter = this->funcList_.end()-1; iter >= this->funcList_.begin(); iter--) {
        if ((*iter)->getName() == name){
            if ((*iter)->getDefined()) return true; 
                else return false; 
        }
    }
	return false;
}

bool IRGenerator::SetFuncDefined(std::string name) {
    if (this->funcList_.empty()) 
        return false;
    for (auto iter = this->funcList_.end()-1; iter >= this->funcList_.begin(); iter--) {
        if ((*iter)->getName() == name){
            (*iter)->setDefined(); 
            return true; 
        }
    }
	return false;
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
    root->IRGen(*this);
	this->Module->print(llvm::outs(), NULL);
}

void IRGenerator::GenObjectCode(std::string outputfile) {
	//获取描述编译器的目标平台、操作系统和环境等信息
	auto TargetTriple = llvm::sys::getDefaultTargetTriple();
	//根据llvm文档提供的初始化
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

	//根据TargetTriple查找目标平台
    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

    llvm::TargetOptions opt;
    auto RM = llvm::Optional<llvm::Reloc::Model>();
    auto TargetMachine = Target->createTargetMachine(TargetTriple, "", "", opt, RM);
	//设置数据布局
    Module->setDataLayout(TargetMachine->createDataLayout());
    Module->setTargetTriple(TargetTriple);

	//将数据写入文件
	std::error_code errCode;
    llvm::raw_fd_ostream OPFile(outputfile, errCode, llvm::sys::fs::OF_None);
    llvm::legacy::PassManager PM;
    TargetMachine->addPassesToEmitFile(PM, OPFile, nullptr, llvm::CGFT_ObjectFile);
    PM.run(*Module);

    OPFile.flush();
}

void IRGenerator::DumpIRCode(std::string FileName) {
	if (FileName == "") FileName = "-";
	std::error_code EC;
	llvm::raw_fd_ostream Out(FileName, EC);
	this->Module->print(Out, NULL);
}