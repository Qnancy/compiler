#include <cstdio>
#include <iostream>
#include <vector>
#include "AST.hpp"
#include "IRGenerator.hpp"

/* 类型 */

llvm::Value* ToBoolType(llvm::Value* value, IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder;
	if (value->getType() == IRBuilder->getInt1Ty())
		return value;
	else if (value->getType()->isIntegerTy())
		return IRBuilder->CreateICmpNE(value, llvm::ConstantInt::get((llvm::IntegerType*)value->getType(), 0, true));
	else if (value->getType()->isFloatingPointTy())
		return IRBuilder->CreateFCmpONE(value, llvm::ConstantFP::get(value->getType(), 0.0));
	else if (value->getType()->isPointerTy())
		return IRBuilder->CreateICmpNE(IRBuilder->CreatePtrToInt(value, IRBuilder->getInt64Ty()), IRBuilder->getInt64(0));
	else {
		throw std::logic_error("Cannot cast to bool type.");
		return NULL;
	}
}

//Type casting
//Supported:
//1. Int -> Int, FP, Pointer
//2. FP -> Int, FP
//3. Pointer -> Int, Pointer
//Other types are not supported, and will return NULL.
llvm::Value* CastType(llvm::Value* value, llvm::Type* type, IRGenerator& IRContext){
	auto IRBuilder = IRContext.IRBuilder;
	if(value->getType() == type){
		std::cout << "castNo" << std::endl;
		return value;
	}else if(type == IRBuilder->getInt1Ty()){
		std::cout << "cast2Bool" << std::endl;
		return ToBoolType(value, IRContext);
	}else if(value->getType()->isIntegerTy() && type->isIntegerTy()){
		std::cout << "castInt2Int" << std::endl;
		return IRBuilder->CreateIntCast(value, type, !value->getType()->isIntegerTy(1));
	}else if(value->getType()->isIntegerTy() && type->isFloatingPointTy()) {
		std::cout << "castInt2FP" << std::endl;
		return value->getType()->isIntegerTy(1) ?
			IRBuilder->CreateUIToFP(value, type) : IRBuilder->CreateSIToFP(value, type);
	}else if (value->getType()->isIntegerTy() && type->isPointerTy()) {
		std::cout << "castInt2Ptr" << std::endl;
		return IRBuilder->CreateIntToPtr(value, type);
	}else if (value->getType()->isFloatingPointTy() && type->isIntegerTy()) {
		std::cout << "castFP2Int" << std::endl;
		return IRBuilder->CreateFPToSI(value, type);
	}
	else if (value->getType()->isFloatingPointTy() && type->isFloatingPointTy()) {
		std::cout << "castFP2FP" << std::endl;
		return IRBuilder->CreateFPCast(value, type);
	}
	else if (value->getType()->isPointerTy() && type->isIntegerTy()) {
		std::cout << "castPtr2Int" << std::endl;
		return IRBuilder->CreatePtrToInt(value, type);
	}
	else if (value->getType()->isPointerTy() && type->isPointerTy()) {
		std::cout << "castPtr2FP" << std::endl;
		return IRBuilder->CreatePointerCast(value, type);
	}
	else {
		return NULL;
	}
}

VarType::VarType(std::string name) {
	if (name == "int") type = Int; 
	else if (name == "char") type = Char; 
	else if (name == "short") type = Short;
	else if (name == "double") type = Double;
	else if (name == "bool") type = Bool;
} 


llvm::Type* VarType::ToLLVMType(IRGenerator& IRContext) {
	auto IRBuilder = IRContext.IRBuilder;
	switch(this->type) {
		case Int: return IRBuilder->getInt32Ty(); 
		case Char: return IRBuilder->getInt8Ty(); 
		case Short: return IRBuilder->getInt16Ty();
		case Double: return IRBuilder->getDoubleTy(); 
		case Bool: return IRBuilder->getInt1Ty(); 
		case Ptr: return this->baseTypePointer->ToLLVMType(IRContext);
	}
	return NULL;
}

llvm::Type* PointerType::ToLLVMType(IRGenerator& IRContext){
	std::cout << "PointerType" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Type* BaseType = this->baseType_.ToLLVMType(IRContext);
	return llvm::PointerType::get(BaseType, 0U);
}

/* 程序开始点 */
BaseAST* Root;

llvm::Value* Program::IRGen(IRGenerator& IRContext) {
	std::cout << "Program" << std::endl;

	for (auto compUnit : *(this->compUnit_)){
		if(compUnit){
			compUnit->IRGen(IRContext);
		}
	}

	return NULL;
}


/* comUnit -> Decl | Funcdef */
/* FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block;
   FuncType      ::= "void" | "int";
   FuncFParams   ::= FuncFParam {"," FuncFParam};
   FuncFParam    ::= BType IDENT ["[" "]" {"[" INT_CONST "]"}]; */

llvm::Value* FuncDef::IRGen(IRGenerator& IRContext) {
	//Get return type
	std::cout << "Function" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Type* ReturnType = this->type_.ToLLVMType(IRContext);

	std::vector<llvm::Type*> ArgTypes; 

	for (auto ArgType : *(this->argList_)) {
		llvm::Type* LLVMType = ArgType->type_.ToLLVMType(IRContext);
		if (!LLVMType) {
			throw std::logic_error("Defining a function " + this->funcName_ + " using unknown type(s).");
			return NULL;
		}
		ArgTypes.push_back(LLVMType);
	}
	
	//Get function type
	llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, ArgTypes, this->argList_->varArgLenth_);

	if (this->block_) {
		// define function
		if (IRContext.IsFuncDefined(this->funcName_)) {
			throw std::logic_error("Function redeclared: "+this->funcName_);
		}

		llvm::Function* Func = IRContext.FindFunction(this->funcName_);
		if (Func) {
			IRContext.SetFuncDefined(this->funcName_); 
		}
		else {
			Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcName_, IRContext.Module);
			IRContext.CreateFunc(FuncType, this->funcName_, Func, true);
		}

		int i = 0; 
		for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ArgIter++) {
			auto ArgInf = this->argList_->at(i);
			IRContext.RemainFutureVar(ArgInf->type_, ArgInf->name_, ArgIter);
			i ++; 
		}

		IRContext.SetCurFunc(Func);
		IRContext.ClearPreBrSignal();

		this->block_->IRGen(IRContext);

		IRContext.SetBasicBlock(NULL); 
		IRContext.SetCurFunc(NULL); 

	}
	else {
		// declare function
		if (IRContext.FindFunction(this->funcName_)) {
			// no need to declare again
			return NULL; 
		}
		llvm::Function* Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcName_, IRContext.Module);

		IRContext.CreateFunc(FuncType, this->funcName_, Func, false);
	}
	
	return NULL;
}

/* Decl -> VarDecl  */
/* VarDecl       ::= BType VarDef {"," VarDef} ";"; */
llvm::Value* VarDecl::IRGen(IRGenerator& IRContext) {
	std::cout << "VarDecl" << std::endl;

	if (IRContext.GetCurFunc()) {
		// local variable

		auto IRBuilder = IRContext.IRBuilder; 

		//创建变量
		auto AllocMem = IRBuilder->CreateAlloca(this->type_.ToLLVMType(IRContext), 0, this->varDef_->varName_);
		
		// llvm::Value* initVal = CastType(this->, IRContext)

		// initialize
		IRContext.SetCurVarType(&(this->type_)); 
		llvm::Value* value = this->varDef_->IRGen(IRContext);

		// store will always align to 4, even for char, which is because we need a type cast for 'value'
		IRBuilder->CreateStore(value, AllocMem);

		IRContext.CreateVar(this->type_, this->varDef_->varName_, AllocMem);
	}
	else {
		// global variable
		// initialize
		std::cout << "VarDecl -> global variable" << std::endl;

		IRContext.SetCurVarType(&(this->type_)); 
		llvm::Value* value = this->varDef_->IRGen(IRContext);

		// convert to const
		llvm::Constant* initializer = llvm::cast<llvm::Constant>(value);
		if (!initializer) {
			throw std::logic_error("The initializer is not const type: "+this->varDef_->varName_);
		}

		//Create a global variable
		auto AllocMem = new llvm::GlobalVariable(
			*(IRContext.Module),
			this->type_.ToLLVMType(IRContext),
			false,
			llvm::Function::ExternalLinkage,
			initializer, 
			this->varDef_->varName_
		);
		
		IRContext.CreateVar(this->type_, this->varDef_->varName_, AllocMem);
	}
	return NULL;
}

/* VarDef        ::= IDENT | IDENT "=" InitVal; | IDENT {"[" INT_CONST "]"}*/
llvm::Value* VarDef::IRGen(IRGenerator& IRContext) {
	std::cout << "VarDef" << std::endl;
	
	if (this->initValue_) {
		// std::cout << "Have init" << std::endl;
		auto value = this->initValue_->IRGen(IRContext);
		VarType* v = IRContext.GetCurVarType();
		return TypeCasting(value, v->ToLLVMType(IRContext), IRContext);
	}
	else {
		// std::cout << "No init" << std::endl;
		auto IRBuilder = IRContext.IRBuilder;
		// VarType* v = new VarType(this->varName_);
		VarType* v = IRContext.GetCurVarType();
		switch(v->GetType()) {
			case Int: return IRBuilder->getInt32(0); 
			case Char: return IRBuilder->getInt8(0);
			case Double: return llvm::ConstantFP::get(IRBuilder->getDoubleTy(), 0.0);
		}
	}
	return NULL;
}

llvm::Value* ArrDef::IRGen(IRGenerator& IRContext) {
	std::cout << "ArrDef" << std::endl;

	//获取数组元素
	this->elementType_ = this->type_.ToLLVMType(IRContext);

	llvm::Type* elementType = this->elementType_;

	//数组构造
	llvm::Type* arrayType = elementType;

	//获取数组维度
	for(auto expr : *(this->exprs_)){
		//处理expr
		llvm::Value* val = expr->IRGen(IRContext);
		//由于是从constant转换出来的，所以可以转换为constant
		llvm::ConstantInt* constant = llvm::dyn_cast<llvm::ConstantInt>(val);
		//转换完之后将int提取出来
		int convertedValue = constant->getSExtValue();
		arrayType = llvm::ArrayType::get(arrayType, convertedValue);
		std::cout << "convertedValue" << convertedValue << "  " << std::endl;
	}

	this->arrayType_ = arrayType;
	if(IRContext.GetCurFunc()){
		auto IRBuilder = IRContext.IRBuilder;
		
		// //创建变量
		auto AllocMem = IRBuilder->CreateAlloca(this->arrayType_, 0, this->arrName_);

		this->arrayType_->print(llvm::outs());
		std::cout << "" << std::endl;
		//初始化
		IRContext.CreateVar(this->type_, this->arrName_, AllocMem, true); 
	}else{
		llvm::Type* intType = this->type_.ToLLVMType(IRContext);
		llvm::ArrayType* arrayType = llvm::ArrayType::get(intType, 100);
		llvm::Constant* Initializer = NULL;
		Initializer = llvm::UndefValue::get(arrayType);

		auto AllocMem = new llvm::GlobalVariable(
			*(IRContext.Module),
			arrayType,
			false,
			llvm::Function::ExternalLinkage,
			Initializer, 
			this->arrName_
		);
		
		IRContext.CreateVar(this->type_, this->arrName_, AllocMem, true);
	}
	
}

llvm::Value* FuncCall::IRGen(IRGenerator& IRContext) {
	std::cout << "FuncCall" << std::endl;

	int i = 0;
	llvm::Value* Arg; 
	std::vector<llvm::Value*> ArgList;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Function* Func = IRContext.FindFunction(this->funcName_);

	if (Func == NULL) {
		throw std::invalid_argument(this->funcName_ + " is not defined.");
		return NULL;
	}
	if ((Func->isVarArg() && this->argList_->size() < Func->arg_size()) || (!Func->isVarArg() && this->argList_->size() != Func->arg_size())) {
		throw std::invalid_argument("Args doesn't match the called function " + this->funcName_ + ".");
		return NULL;
	}
	
	for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ArgIter++) {
		Arg = this->argList_->at(i)->IRGen(IRContext);
		Arg = TypeCasting(Arg, ArgIter->getType(), IRContext);
		if (Arg == NULL) {
			throw std::invalid_argument("Type of " + std::to_string(i) + "-th argument doesn't match the called function " + this->funcName_ + ".");
			return NULL;
		}
		ArgList.push_back(Arg);
		i += 1; 
	}
	
	if ( Func->isVarArg() ) {
		for (; i < this->argList_->size(); i++) {
			Arg = this->argList_->at(i)->IRGen(IRContext);
			if (Arg->getType()->isIntegerTy())
				Arg = TypeUpgrading(Arg, IRBuilder->getInt32Ty(), IRContext);
			else if (Arg->getType()->isFloatingPointTy())
				Arg = TypeUpgrading(Arg, IRBuilder->getDoubleTy(), IRContext);
			ArgList.push_back(Arg);
		}
	}

	return IRBuilder->CreateCall(Func, ArgList);
}

/* Block         ::= "{" {BlockItem} "}"; */
llvm::Value* Block::IRGen(IRGenerator& IRContext) {
	std::cout << "Block" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 

	llvm::Function* Func = IRContext.GetCurFunc();
	llvm::BasicBlock* newBlock = llvm::BasicBlock::Create(*(IRContext.Context), "BBEntry", Func);
	auto prevBB = IRContext.GetBasicBlock(); 

	bool isConn = IRContext.ClearPreBrSignal(); 
	if (isConn) {
		// maybe go into a function, thus not insert Br
		IRBuilder->CreateBr(newBlock);
	}
	IRContext.SetPreBrSignal();

	IRContext.SetBasicBlock(this); 
	IRBuilder->SetInsertPoint(newBlock);

	// at the beginning of a function, we need to create variables for params
	IRContext.CreateFutureVars(); 

	for (auto stmt : *(this->stmts_)){
		if(stmt){
			stmt->IRGen(IRContext);
		}
	}

	IRContext.DiscardVar();

	IRContext.SetBasicBlock(prevBB); 
	if (isConn) {
		llvm::BasicBlock* outBlock = llvm::BasicBlock::Create(*(IRContext.Context), "BBExit", Func);
		IRBuilder->CreateBr(outBlock);
		IRBuilder->SetInsertPoint(outBlock);
	}

	return newBlock; 
}

llvm::Value* IfStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "IfStmt" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 

	auto CondExpr = this->condition_->IRGen(IRContext);
	llvm::BasicBlock* CondBlock = IRBuilder->GetInsertBlock();

	IRContext.ClearPreBrSignal();
	llvm::BasicBlock* IfBlock = (llvm::BasicBlock*)this->thenStmt_->IRGen(IRContext);
	llvm::BasicBlock* IfOutBlock = IRBuilder->GetInsertBlock(); 
	llvm::BasicBlock* ElseBlock, *ElseOutBlock; 
	if (this->elseStmt_) {
		IRContext.ClearPreBrSignal();
		ElseBlock = (llvm::BasicBlock*)this->elseStmt_->IRGen(IRContext);
		ElseOutBlock = IRBuilder->GetInsertBlock(); 
	}

	// set exit 
	llvm::Function* Func = IRContext.GetCurFunc();
	llvm::BasicBlock* OutBlock = llvm::BasicBlock::Create(*(IRContext.Context), "BBExit", Func);
	IRBuilder->SetInsertPoint(IfOutBlock);
	IRBuilder->CreateBr(OutBlock);
	if (this->elseStmt_) {
		IRBuilder->SetInsertPoint(ElseOutBlock);
		IRBuilder->CreateBr(OutBlock);
	}

	// set conditional branch
	IRBuilder->SetInsertPoint(CondBlock);
	IRBuilder->CreateCondBr(CondExpr, IfBlock, this->elseStmt_?ElseBlock:OutBlock);

	IRBuilder->SetInsertPoint(OutBlock);

	return NULL;
}

llvm::Value* ForStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "ForStmt" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Function* Func = IRContext.GetCurFunc();

	// init generate
	if (this->initStmt_)
		this->initStmt_->IRGen(IRContext); 
	llvm::BasicBlock* cmpBlock = llvm::BasicBlock::Create(*(IRContext.Context), "ForCmp", Func);
	llvm::BasicBlock* iterBlock = llvm::BasicBlock::Create(*(IRContext.Context), "ForIter", Func);
	llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*(IRContext.Context), "ForExit", Func);
	IRBuilder->CreateBr(cmpBlock);
	// enter the Loop
	IRContext.EnterLoop(cmpBlock, iterBlock, exitBlock); 

	// condition generate
	IRBuilder->SetInsertPoint(cmpBlock);
	auto cmpRes = (this->condExpr_)?this->condExpr_->IRGen(IRContext):IRBuilder->getInt1(true); 

	// body generate
	IRContext.ClearPreBrSignal();
	llvm::BasicBlock* bodyBlock = (llvm::BasicBlock*)this->loopBody_->IRGen(IRContext);
	llvm::BasicBlock* bodyOutBlock = IRBuilder->GetInsertBlock();

	// iteration generate
	IRBuilder->CreateBr(iterBlock);
	IRBuilder->SetInsertPoint(iterBlock);
	if (this->iterStmt_) this->iterStmt_->IRGen(IRContext);
	IRBuilder->CreateBr(cmpBlock);

	// set conditional branch
	IRBuilder->SetInsertPoint(cmpBlock);
	IRBuilder->CreateCondBr(cmpRes, bodyBlock, exitBlock);

	// leave the Loop
	IRContext.LeaveCurrentLoop(); 
	IRBuilder->SetInsertPoint(exitBlock);

	return NULL;
}


llvm::Value* WhileStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "WhileStmt" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Function* Func = IRContext.GetCurFunc();

	// init
	llvm::BasicBlock* cmpBlock = llvm::BasicBlock::Create(*(IRContext.Context), "WhileCmp", Func);
	llvm::BasicBlock* exitBlock = llvm::BasicBlock::Create(*(IRContext.Context), "WhileExit", Func);
	IRBuilder->CreateBr(cmpBlock);
	// enter the Loop
	IRContext.EnterLoop(cmpBlock, NULL, exitBlock); 

	// condition generate
	IRBuilder->SetInsertPoint(cmpBlock);
	auto cmpRes = (this->condExpr_)?this->condExpr_->IRGen(IRContext):IRBuilder->getInt1(true); 

	// body generate
	IRContext.ClearPreBrSignal();
	llvm::BasicBlock* bodyBlock = (llvm::BasicBlock*)this->loopBody_->IRGen(IRContext);
	llvm::BasicBlock* bodyOutBlock = IRBuilder->GetInsertBlock();
	IRBuilder->CreateBr(cmpBlock);

	// set conditional branch
	IRBuilder->SetInsertPoint(cmpBlock);
	IRBuilder->CreateCondBr(cmpRes, bodyBlock, exitBlock);

	// leave the Loop
	IRContext.LeaveCurrentLoop(); 
	IRBuilder->SetInsertPoint(exitBlock);

	return NULL;
}

llvm::Value* BreakStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "BreakStmt" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::BasicBlock* targetBlock = IRContext.BreakCurrentLoop();
	IRBuilder->CreateBr(targetBlock);

	return NULL; 
}

llvm::Value* ContinueStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "ContinueStmt" << std::endl;

	auto IRBuilder = IRContext.IRBuilder; 
	llvm::BasicBlock* targetBlock = IRContext.ContinueCurrentLoop();
	IRBuilder->CreateBr(targetBlock);

	return NULL; 
}

llvm::Value* ReturnStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "ReturnStmt" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	if (this->retVal_)
		IRBuilder->CreateRet(this->retVal_->IRGen(IRContext));
	else
		IRBuilder->CreateRetVoid();
}

/**
 * @brief 算术运算
 * 
 */
//Unary plus, e.g. +i, +j, +123
llvm::Value* UnaryPlus::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr +i" << std::endl;
	llvm::Value* val = this->operand_->IRGen(IRContext);
	if (!(
		val->getType()->isIntegerTy() ||
		val->getType()->isFloatingPointTy())
		)
		throw std::logic_error("Unary plus must be applied to integers or floating-point numbers.");
	return val;

}

llvm::Value* UnaryMinus::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr -i" << std::endl;
	llvm::Value* val = this->operand_->IRGen(IRContext);
	if (!(
		val->getType()->isIntegerTy() ||
		val->getType()->isFloatingPointTy())
		)
		throw std::logic_error("Unary plus must be applied to integers or floating-point numbers.");
	auto IRBuilder = IRContext.IRBuilder;
	if (val->getType()->isIntegerTy())
		return IRBuilder->CreateNeg(val);
	else
		return IRBuilder->CreateFNeg(val); 
	
}

llvm::Value* AddressOf::IRGen(IRGenerator& IRContext) {
	std::cout << "AddressOf" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* VarPtr = IRContext.FindVar(this->oprand_->name_);
	return VarPtr;
}

llvm::Value* Addition::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr +" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if (LHS->getType()->isIntegerTy())
		return IRBuilder->CreateAdd(LHS, RHS);
	else
		return IRBuilder->CreateFAdd(LHS, RHS);
}

llvm::Value* Subtraction::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr -" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if (LHS->getType()->isIntegerTy())
		return IRBuilder->CreateSub(LHS, RHS);
	else
		return IRBuilder->CreateFSub(LHS, RHS);
}

llvm::Value* Multiplication::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr *" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if (LHS->getType()->isIntegerTy())
		return IRBuilder->CreateMul(LHS, RHS);
	else
		RHS = CastType(RHS, 
	LHS->getType(), IRContext);
		return IRBuilder->CreateFMul(LHS, RHS);
}

llvm::Value* Division::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr /" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if(LHS->getType()->isIntegerTy()){
		return IRBuilder->CreateSDiv(LHS, RHS);
	}else{
		RHS = CastType(RHS, LHS->getType(), IRContext);
		return IRBuilder->CreateFDiv(LHS, RHS);
	}
	
}

llvm::Value* Modulo::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr %" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateSRem(LHS, RHS);
}

/**
 * @brief 逻辑运算
 * 
 */
llvm::Value* LogicNot::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr !" << std::endl;
	llvm::Value* val = this->RHS_->IRGen(IRContext);
	auto IRBuilder = IRContext.IRBuilder;
	return IRBuilder->CreateICmpEQ(ToBoolType(val, IRContext), IRBuilder->getInt1(false));
}

llvm::Value* LogicAND::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr &&" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = ToBoolType(this->LHS_->IRGen(IRContext), IRContext);
	llvm::Value* RHS = ToBoolType(this->RHS_->IRGen(IRContext), IRContext);
	return IRBuilder->CreateLogicalAnd(LHS, RHS);
}

llvm::Value* LogicOR::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr ||" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = ToBoolType(this->LHS_->IRGen(IRContext), IRContext);
	llvm::Value* RHS = ToBoolType(this->RHS_->IRGen(IRContext), IRContext);
	return IRBuilder->CreateLogicalOr(LHS, RHS);
}

llvm::Value* LogicEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr ==" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpEQ(LHS, RHS);
}

llvm::Value* LogicNEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr !=" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpNE(LHS, RHS);
}

llvm::Value* LogicGT::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr >" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSGT(LHS, RHS);
}

llvm::Value* LogicGEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr >=" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSGE(LHS, RHS);
}

llvm::Value* LogicLT::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr <" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSLT(LHS, RHS);
}

llvm::Value* LogicLEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr <=" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSLE(LHS, RHS);
}

/* 位运算 */
llvm::Value* BitwiseAND::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr &" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSGE(LHS, RHS);
}

llvm::Value* BitwiseXOR::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr ^" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSLT(LHS, RHS);
}

llvm::Value* BitwiseOR::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr |" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder->CreateICmpSLE(LHS, RHS);
}

llvm::Value* Assign::IRGen(IRGenerator& IRContext){
	std::cout << "Assign" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	llvm::Value* LHSPtr = this->LHS_->IRGenPtr(IRContext);

	//对右值进行一个类型转换
	RHS = CastType(RHS, LHSPtr->getType()->getNonOpaquePointerElementType(), IRContext);
	//赋值
	IRBuilder->CreateStore(RHS, LHSPtr);
	return RHS; 

}

llvm::Value* Constant::IRGen(IRGenerator& IRContext) {
	std::cout << "Constant" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	VarType v(this->type_);
	// VarType* v = IRContext.GetCurVarType();
	switch(v.GetType()) {
		case Int: return IRBuilder->getInt32(this->int_); 
		case Char: return IRBuilder->getInt8(this->character_); 
		case Double:return llvm::ConstantFP::get(IRBuilder->getDoubleTy(), this->double_);
	}
	return NULL;
}

llvm::Value* LeftVal::IRGen(IRGenerator& IRContext) {
	std::cout << "LeftVal" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* VarPtr = IRContext.FindVar(this->name_);
	if (IRContext.IsPtrVar(this->name_)) {
		return VarPtr; 
	}
	else {
		llvm::Type* type = VarPtr->getType()->getNonOpaquePointerElementType();
		llvm::Value* val = IRBuilder->CreateLoad(type,VarPtr);
		return val;
	}
}

llvm::Value* LeftVal::IRGenPtr(IRGenerator& IRContext) {
	std::cout << "LeftValPtr" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* VarPtr = IRContext.FindVar(this->name_);
	return VarPtr;
}

llvm::Value* StringType::IRGen(IRGenerator& IRContext) {
	std::cout << "StringType" << std::endl;
	auto IRBuilder = IRContext.IRBuilder; 
	return IRBuilder->CreateGlobalStringPtr(this->content_.c_str());
}

llvm::Value* ArrVal::IRGen(IRGenerator& IRContext) {
	std::cout << "ArrVal" << std::endl;

	auto IRBuilder = IRContext.IRBuilder;

	//搜索数组的指针
	llvm::Value* arrayPtr = IRContext.FindVar(this->name_);
	// auto* arrayPtr = IRContext.Module->getGlobalVariable(this->name_);
	std::cout << "Array Ptr " << arrayPtr << std::endl; 
	
	//this->exprs_ index索引

	std::vector<llvm::Value*> indices;

	//生成每个维度的索引

	for(auto expr : *(this->exprs_)){
		indices.push_back(expr->IRGen(IRContext));

	}

	llvm::Value* v1, *v2;

	for(auto indice: indices){
		if(arrayPtr->getType()->getNonOpaquePointerElementType()->isArrayTy()){
			v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());	
		}
		else if(arrayPtr->getType()->isPointerTy()){
			v1 = IRBuilder->CreateLoad(arrayPtr->getType()->getNonOpaquePointerElementType(), arrayPtr);
		}
		else{
			throw std::logic_error("The sunsciption operation received neither array type nor pointer type");
		}
		// v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());

		v2 = IRBuilder->CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indice);

	}
	
	return IRBuilder->CreateLoad(v1->getType()->getNonOpaquePointerElementType(), v2);

}

llvm::Value* ArrVal::IRGenPtr(IRGenerator& IRContext) {
	std::cout << "ArrValPtr" << std::endl;

	auto IRBuilder = IRContext.IRBuilder;

	//搜索数组的指针
	llvm::Value* arrayPtr = IRContext.FindVar(this->name_);
	arrayPtr->print(llvm::outs());
	
	//this->exprs_ index索引

	std::vector<llvm::Value*> indices;

	//生成每个维度的索引

	for(auto expr : *(this->exprs_)){
		indices.push_back(expr->IRGen(IRContext));

	}
	
	llvm::Value* v1, *v2;

	for(auto indice: indices){
		if(arrayPtr->getType()->getNonOpaquePointerElementType()->isArrayTy()){
			v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());	
		}
		else if(arrayPtr->getType()->isPointerTy()){
			v1 = IRBuilder->CreateLoad(arrayPtr->getType()->getNonOpaquePointerElementType(), arrayPtr);
		}
		else{
			throw std::logic_error("The sunsciption operation received neither array type nor pointer type");
		}
		// v1 = IRBuilder->CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());

		v2 = IRBuilder->CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indice);
	}
	return v2;
}

llvm::Value* AssignArr::IRGen(IRGenerator& IRContext){
	std::cout << "AssignArr" << std::endl;
	auto IRBuilder = IRContext.IRBuilder;
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);	
	llvm::Value* LHSPtr = this->LHS_->IRGenPtr(IRContext);

	//赋值
	IRBuilder->CreateStore(RHS, LHSPtr);
	return RHS; 
}


	

