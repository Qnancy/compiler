#include <cstdio>
#include <iostream>
#include <vector>
#include "AST.hpp"
#include "IRGenerator.hpp"
#include "utils.hpp"

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
	std::cout << "Function" << std::endl;

	std::vector<llvm::Type*> ArgTypes; 
	for (auto ArgType : *(this->argList_)) {
		llvm::Type* LLVMType = ArgType->type_.ToLLVMType(IRContext);
		if (!LLVMType) {
			throw std::logic_error("Defining a function " + this->funcName_ + " using unknown type(s).");
			return NULL;
		}
		ArgTypes.push_back(LLVMType);
	}

	//Get return type
	llvm::Type* ReturnType = this->type_.ToLLVMType(IRContext);
	
	//Get function type
	llvm::FunctionType* FuncType = llvm::FunctionType::get(ReturnType, ArgTypes, this->argList_->varArgLenth_);
	
	// 如果是定义函数
	if (this->funcBody_) {
		//查找函数之前是否已定义或声明
		llvm::Function* Func = IRContext.FindFunction(this->funcName_);
		if (Func) {
			//是否有定义
			if (IRContext.CheckFuncDefined(this->funcName_)) {
				throw std::logic_error("Function redefined: " + this->funcName_);
			}
			IRContext.SetFuncDefined(this->funcName_); 
		}else {
			Func = llvm::Function::Create(FuncType, llvm::Function::ExternalLinkage, this->funcName_, IRContext.Module);
			IRContext.CreateFunc(FuncType, this->funcName_, Func, true);
		}

		llvm::BasicBlock* FuncBlock = llvm::BasicBlock::Create(Context, "FuncEntry", Func);
		IRBuilder.SetInsertPoint(FuncBlock);
		IRContext.PushSymbolTable();

		int i = 0; 
		for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ArgIter++, i++) {
			auto Alloc = CreateEntryBlockAlloca(Func, this->argList_->at(i)->name_, ArgTypes[i]);
			IRBuilder.CreateStore(ArgIter, Alloc);
			IRContext.CreateVar(this->argList_->at(i)->name_, Alloc);
		}

		IRContext.EnterFunc(Func);
		this->funcBody_->IRGen(IRContext);
		if (!IRBuilder.GetInsertBlock()->getTerminator()) {
			if (ReturnType->isVoidTy())
				IRBuilder.CreateRetVoid();
			else
				IRBuilder.CreateRet(llvm::Constant::getNullValue(ReturnType));
		}
		IRContext.LeaveFunc();
		IRContext.PopSymbolTable();
		
	}else {
		// 声明函数
		if (IRContext.FindFunction(this->funcName_)) {
			throw std::logic_error("Function redeclared: " + this->funcName_);
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
	
	llvm::Type* type = this->type_.ToLLVMType(IRContext);
	if (!type) {
		throw std::logic_error("Defining variables with unknown type.");
		return NULL;
	}
	if (type->isVoidTy()) {
		throw std::logic_error("Cannot define \"void\" variables.");
		return NULL;
	}
	for (auto var : *(this->varList_)) {
		//如果是函数内部的变量
		if (IRContext.GetCurFunc()) {
			// local variable
			auto Alloc = CreateEntryBlockAlloca(IRContext.GetCurFunc(), var->varName_, type);
			if (!IRContext.CreateVar(var->varName_, Alloc)){
				throw std::logic_error("Variable redefined: " + var->varName_);
				Alloc->eraseFromParent();
				return NULL;
			}
			IRContext.SetCurVarType(&(this->type_)); 
			llvm::Value* value = var->IRGen(IRContext);
			if (value == NULL) {
				throw std::logic_error("Cannot initialize variable " + var->varName_ + " with unmatched value.");
				Alloc->eraseFromParent();
				return NULL;
			}
			IRBuilder.CreateStore(value, Alloc);
		}
		else {
			// global variable
			// initialize
			std::cout << "VarDef -> global variable" << std::endl;

			IRContext.SetCurVarType(&(this->type_)); 
			llvm::Value* value = var->IRGen(IRContext);
			// convert to const
			llvm::Constant* initializer = llvm::cast<llvm::Constant>(value);
			if (!initializer) {
				throw std::logic_error("The initializer is not const type: "+ var->varName_);
			}
			if (value == NULL) {
				throw std::logic_error("Cannot initialize variable " + var->varName_ + " with unmatched value.");
				return NULL;
			}
			//Create a global variable
			auto AllocMem = new llvm::GlobalVariable(
				*(IRContext.Module),
				this->type_.ToLLVMType(IRContext),
				false,
				llvm::Function::ExternalLinkage,
				initializer, 
				var->varName_
			);
			
			if (!IRContext.CreateVar(var->varName_, AllocMem)){
				throw std::logic_error("Variable redefined: " + var->varName_);
				AllocMem->eraseFromParent();
				return NULL;
			}
		}
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
		return TypeCasting(value, v->ToLLVMType(IRContext));
	}
	else {
		// std::cout << "No init" << std::endl;
		VarType* v = IRContext.GetCurVarType();
		switch(v->GetType()) {
			case Int: return IRBuilder.getInt32(0); 
			case Char: return IRBuilder.getInt8(0);
			case Bool: return IRBuilder.getInt1(0);
			case Double: return llvm::ConstantFP::get(IRBuilder.getDoubleTy(), 0.0);
		}
	}
	return NULL;
}

llvm::Value* ArrDef::IRGen(IRGenerator& IRContext) {
	std::cout << "ArrDef" << std::endl;
	llvm::Type* elementType = this->type_.ToLLVMType(IRContext);
    if (!elementType) {
        throw std::logic_error("Unknown element type for array: " + this->arrName_);
    }

	llvm::Type* arrayType = elementType;
	for(auto expr : *(this->exprs_)){
		llvm::Value* val = expr->IRGen(IRContext);
		llvm::ConstantInt* constant = llvm::dyn_cast<llvm::ConstantInt>(val);
        if (!constant) {
            throw std::logic_error("Array dimension must be a constant integer.");
        }
		int convertedValue = constant->getSExtValue();
		arrayType = llvm::ArrayType::get(arrayType, convertedValue);
		std::cout << "convertedValue" << convertedValue << "  " << std::endl;
	}
	
	if(IRContext.GetCurFunc()){
		auto Alloc = CreateEntryBlockAlloca(IRContext.GetCurFunc(), this->arrName_, arrayType);
		arrayType->print(llvm::outs());
		if (!IRContext.CreateVar(this->arrName_, Alloc, true))
			throw std::logic_error("Variable redefined: " + this->arrName_); 
		
	}else{
		llvm::ArrayType* arrayType = llvm::ArrayType::get(elementType, 100);
		llvm::Constant* Initializer = llvm::UndefValue::get(arrayType);

		auto AllocMem = new llvm::GlobalVariable(
			*(IRContext.Module),
			arrayType,
			false,
			llvm::GlobalValue::ExternalLinkage,
			Initializer, 
			this->arrName_
		);
		
		if (!IRContext.CreateVar(this->arrName_, AllocMem, true))
			throw std::logic_error("Variable redefined: " + this->arrName_);
	}
}

llvm::Value* FuncCall::IRGen(IRGenerator& IRContext) {
	std::cout << "FuncCall" << std::endl;

	int i = 0;
	llvm::Value* Arg; 
	std::vector<llvm::Value*> ArgList;
	llvm::Function* Func = IRContext.FindFunction(this->funcName_);

	if (Func == NULL) {
		throw std::domain_error(this->funcName_ + " is not defined.");
		return NULL;
	}
	if ((Func->isVarArg() && this->argList_->size() < Func->arg_size()) || (!Func->isVarArg() && this->argList_->size() != Func->arg_size())) {
		throw std::invalid_argument("Args doesn't match the called function " + this->funcName_ + ".");
		return NULL;
	}
	
	for (auto ArgIter = Func->arg_begin(); ArgIter < Func->arg_end(); ArgIter++) {
		Arg = this->argList_->at(i)->IRGen(IRContext);
		Arg = TypeCasting(Arg, ArgIter->getType());
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
				Arg = TypeUpgrading(Arg, IRBuilder.getInt32Ty());
			else if (Arg->getType()->isFloatingPointTy())
				Arg = TypeUpgrading(Arg, IRBuilder.getDoubleTy());
			ArgList.push_back(Arg);
		}
	}

	return IRBuilder.CreateCall(Func, ArgList);
}

/* Block         ::= "{" {BlockItem} "}"; */
llvm::Value* Block::IRGen(IRGenerator& IRContext) {
	std::cout << "Block" << std::endl;
	IRContext.PushSymbolTable();
	
	for (auto stmt : *(this->stmts_)){
		if (IRBuilder.GetInsertBlock()->getTerminator())
			break;
		else if(stmt){
			stmt->IRGen(IRContext);
		}
	}

	IRContext.PopSymbolTable();
	return NULL;
}

llvm::Value* IfStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "IfStmt" << std::endl;

	auto condition = this->condition_->IRGen(IRContext);
	if (!(condition = ToBoolType(condition))) {
		throw std::logic_error("Condition expression must be boolean.");
		return NULL;
	}
	llvm::Function* CurFunc = IRContext.GetCurFunc();
	llvm::BasicBlock* ThenBlock = llvm::BasicBlock::Create(Context, "Then", CurFunc);
	llvm::BasicBlock* ElseBlock = llvm::BasicBlock::Create(Context, "Else", CurFunc);
	llvm::BasicBlock* MergeBlock = llvm::BasicBlock::Create(Context, "Merge", CurFunc);
	//Create a branch instruction corresponding to this if statement
	IRBuilder.CreateCondBr(condition, ThenBlock, ElseBlock);
	//Generate code in the "Then" block
	IRBuilder.SetInsertPoint(ThenBlock);
	if (this->thenStmt_) {
		IRContext.PushSymbolTable();
		this->thenStmt_->IRGen(IRContext);
		IRContext.PopSymbolTable();
	}
	TerminateBlockByBr(MergeBlock);
	//Generate code in the "Else" block
	IRBuilder.SetInsertPoint(ElseBlock);
	if (this->elseStmt_) {
		IRContext.PushSymbolTable();
		this->elseStmt_->IRGen(IRContext);
		IRContext.PopSymbolTable();
	}
	TerminateBlockByBr(MergeBlock);
	//Finish "Merge" block
	if (MergeBlock->hasNPredecessorsOrMore(1)) {
		IRBuilder.SetInsertPoint(MergeBlock);
	}
	return NULL;
}

llvm::Value* ForStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "ForStmt" << std::endl;
	llvm::Function* CurFunc = IRContext.GetCurFunc();

	llvm::BasicBlock* ForCondBlock = llvm::BasicBlock::Create(Context, "ForCond", CurFunc);
	llvm::BasicBlock* ForBodyBlock = llvm::BasicBlock::Create(Context, "ForBody", CurFunc);
	llvm::BasicBlock* ForIterBlock = llvm::BasicBlock::Create(Context, "ForIter", CurFunc);
	llvm::BasicBlock* ForExitBlock = llvm::BasicBlock::Create(Context, "ForExit", CurFunc);
	
	if (this->initStmt_) {
		IRContext.PushSymbolTable();
		this->initStmt_->IRGen(IRContext);
	}
	TerminateBlockByBr(ForCondBlock);
	//Generate code in the "ForCond" block
	IRBuilder.SetInsertPoint(ForCondBlock);
	if (this->condExpr_) {
		auto condition = this->condExpr_->IRGen(IRContext);
		if (!(condition = ToBoolType(condition))) {
			throw std::logic_error("Condition expression must be boolean.");
			return NULL;
		}
		IRBuilder.CreateCondBr(condition, ForBodyBlock, ForExitBlock);
	}else {
		IRBuilder.CreateBr(ForBodyBlock);
	}
	//Generate code in the "ForBody" block
	IRBuilder.SetInsertPoint(ForBodyBlock);
	if (this->loopBody_) {
		IRContext.EnterLoop(ForCondBlock, ForIterBlock, ForExitBlock);
		IRContext.PushSymbolTable();
		this->loopBody_->IRGen(IRContext);
		IRContext.PopSymbolTable();
		IRContext.LeaveLoop();
	}
	TerminateBlockByBr(ForIterBlock);
	//Generate code in the "ForInc" block
	IRBuilder.SetInsertPoint(ForIterBlock);
	if (this->iterStmt_) {
		this->iterStmt_->IRGen(IRContext);
	}
	IRBuilder.CreateBr(ForCondBlock);
	//Finish "ForExit" block
	IRBuilder.SetInsertPoint(ForExitBlock);
	if (this->initStmt_){
		IRContext.PopSymbolTable();
	}
	return NULL;
}


llvm::Value* WhileStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "WhileStmt" << std::endl;
	llvm::Function* CurFunc = IRContext.GetCurFunc();

	llvm::BasicBlock* WhileCondBlock = llvm::BasicBlock::Create(Context, "WhileCond", CurFunc);
	llvm::BasicBlock* WhileBodyBlock = llvm::BasicBlock::Create(Context, "WhileBody", CurFunc);
	llvm::BasicBlock* WhileExitBlock = llvm::BasicBlock::Create(Context, "WhileExit", CurFunc);
	IRBuilder.CreateBr(WhileCondBlock);
	IRBuilder.SetInsertPoint(WhileCondBlock);
	auto condition = this->condExpr_->IRGen(IRContext);
	if (!(condition = ToBoolType(condition))) {
		throw std::logic_error("Condition expression must be boolean.");
		return NULL;
	}
	IRBuilder.CreateCondBr(condition, WhileBodyBlock, WhileExitBlock);
	//Generate code in the "WhileBody" block
	IRBuilder.SetInsertPoint(WhileBodyBlock);
	if (this->loopBody_) {
		IRContext.EnterLoop(WhileCondBlock, WhileBodyBlock, WhileExitBlock);
		IRContext.PushSymbolTable();
		this->loopBody_->IRGen(IRContext);
		IRContext.PopSymbolTable();
		IRContext.LeaveLoop();
	}
	TerminateBlockByBr(WhileCondBlock);
	//Finish "WhileExit" block
	IRBuilder.SetInsertPoint(WhileExitBlock);
	return NULL;
}

llvm::Value* BreakStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "BreakStmt" << std::endl;

	llvm::BasicBlock* BreakTarget = IRContext.BreakCurrentLoop();
	if (BreakTarget)
		IRBuilder.CreateBr(BreakTarget);
	else
		throw std::logic_error("Break statement not in a loop.");

	return NULL; 
}

llvm::Value* ContinueStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "ContinueStmt" << std::endl;

	llvm::BasicBlock* ContinueTarget = IRContext.ContinueCurrentLoop();
	if (ContinueTarget)
		IRBuilder.CreateBr(ContinueTarget);
	else
		throw std::logic_error("Continue statement not in a loop.");
	return NULL; 
}

llvm::Value* ReturnStmt::IRGen(IRGenerator& IRContext) {
	std::cout << "ReturnStmt" << std::endl;

	llvm::Function* CurFunc = IRContext.GetCurFunc();
	if (!CurFunc) {
		throw std::logic_error("Return statement not in a function.");
		return NULL;
	}
	if (this->retVal_){
		llvm::Value* RetVal = TypeCasting(this->retVal_->IRGen(IRContext), CurFunc->getReturnType());
		if (!RetVal) {
			throw std::logic_error("The type of return value doesn't match and cannot be cast to the return type.");
			return NULL;
		}
		IRBuilder.CreateRet(RetVal);
	}else{
		if (CurFunc->getReturnType()->isVoidTy())
			IRBuilder.CreateRetVoid();
		else
			throw std::logic_error("Return type mismatch.");
	}
}

/**
 * @brief 算术运算
 * 
 */
//Unary plus, e.g. +i, +j, +123
llvm::Value* UnaryPlus::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr +i" << std::endl;
	llvm::Value* operand = this->operand_->IRGen(IRContext);
	if (!(
		operand->getType()->isIntegerTy() ||
		operand->getType()->isFloatingPointTy())
		)
		throw std::logic_error("Unary plus must be applied to integers or floating-point numbers.");
	return operand;

}

//Unary minus, e.g. -i, -j, -123
llvm::Value* UnaryMinus::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr -i" << std::endl;
	llvm::Value* operand = this->operand_->IRGen(IRContext);
	if (!(
		operand->getType()->isIntegerTy() ||
		operand->getType()->isFloatingPointTy())
		)
		throw std::logic_error("Unary plus must be applied to integers or floating-point numbers.");
	if (operand->getType()->isIntegerTy())
		return IRBuilder.CreateNeg(operand);
	else
		return IRBuilder.CreateFNeg(operand); 
	
}

//Fetch address, e.g. &i
llvm::Value* AddressOf::IRGen(IRGenerator& IRContext) {
	std::cout << "AddressOf" << std::endl;
	llvm::Value* VarPtr = IRContext.FindVar(this->oprand_->name_);
	return VarPtr;
}

//Addition, e.g. x+y
llvm::Value* Addition::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr +" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if (LHS->getType()->isIntegerTy())
		return IRBuilder.CreateAdd(LHS, RHS);
	else
		return IRBuilder.CreateFAdd(LHS, RHS);
}

//Subtraction, e.g. x-y
llvm::Value* Subtraction::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr -" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if (LHS->getType()->isIntegerTy())
		return IRBuilder.CreateSub(LHS, RHS);
	else
		return IRBuilder.CreateFSub(LHS, RHS);
}

//Multiplication, e.g. x*y
llvm::Value* Multiplication::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr *" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if (LHS->getType()->isIntegerTy())
		return IRBuilder.CreateMul(LHS, RHS);
	else
		RHS = CastType(RHS, LHS->getType());
		return IRBuilder.CreateFMul(LHS, RHS);
}

//Division, e.g. x/y
llvm::Value* Division::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr /" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if(LHS->getType()->isIntegerTy()){
		return IRBuilder.CreateSDiv(LHS, RHS);
	}else{
		RHS = CastType(RHS, LHS->getType());
		return IRBuilder.CreateFDiv(LHS, RHS);
	}
	
}

//Modulo, e.g. x%y
llvm::Value* Modulo::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr %" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateSRem(LHS, RHS);
}

/**
 * @brief 逻辑运算
 * 
 */
//Logical NOT, e.g. !x
llvm::Value* LogicNot::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr !" << std::endl;
	llvm::Value* val = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpEQ(ToBoolType(val), IRBuilder.getInt1(false));
}

//Logical AND, e.g. x&&y
llvm::Value* LogicAND::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr &&" << std::endl;
	llvm::Value* LHS = ToBoolType(this->LHS_->IRGen(IRContext));
	llvm::Value* RHS = ToBoolType(this->RHS_->IRGen(IRContext));
	return IRBuilder.CreateLogicalAnd(LHS, RHS);
}

//Logical OR, e.g. x||y
llvm::Value* LogicOR::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr ||" << std::endl;
	llvm::Value* LHS = ToBoolType(this->LHS_->IRGen(IRContext));
	llvm::Value* RHS = ToBoolType(this->RHS_->IRGen(IRContext));
	return IRBuilder.CreateLogicalOr(LHS, RHS);
}

//Logical EQ, e.g. x==y
llvm::Value* LogicEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr ==" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpEQ(LHS, RHS);
}

//Logical NEQ, e.g. x!=y
llvm::Value* LogicNEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr !=" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpNE(LHS, RHS);
}

//Logical GT, e.g. x>y
llvm::Value* LogicGT::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr >" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpSGT(LHS, RHS);
}

//Logical GEQ, e.g. x>=y
llvm::Value* LogicGEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr >=" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpSGE(LHS, RHS);
}

//Logical LT, e.g. x<y
llvm::Value* LogicLT::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr <" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpSLT(LHS, RHS);
}

//Logical LEQ, e.g. x<=y
llvm::Value* LogicLEQ::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr <=" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpSLE(LHS, RHS);
}

/* 位运算 */
//Bitwise NOT, e.g. ~x
llvm::Value* BitwiseAND::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr &" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpSGE(LHS, RHS);
}


//Bitwise XOR, e.g. x^y
llvm::Value* BitwiseXOR::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr ^" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpSLT(LHS, RHS);
}

//Bitwise OR, e.g. x|y
llvm::Value* BitwiseOR::IRGen(IRGenerator& IRContext) {
	std::cout << "Expr |" << std::endl;
	llvm::Value* LHS = this->LHS_->IRGen(IRContext);
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	return IRBuilder.CreateICmpSLE(LHS, RHS);
}

llvm::Value* Assign::IRGen(IRGenerator& IRContext){
	llvm::Value* RHS = this->RHS_->IRGen(IRContext);
	if (dynamic_cast<ArrVal*>(this->LHS_) != nullptr) {
		std::cout << "ArrAssign" << std::endl;
		ArrVal* arrValPtr = dynamic_cast<ArrVal*>(this->LHS_);
		llvm::Value* LHSPtr = arrValPtr->IRGenPtr(IRContext);
		IRBuilder.CreateStore(RHS, LHSPtr);
		return RHS; 
	}else{
		std::cout << "Assign" << std::endl;
		llvm::Value* LHSPtr = this->LHS_->IRGenPtr(IRContext);
		RHS = CastType(RHS, LHSPtr->getType()->getNonOpaquePointerElementType());
		IRBuilder.CreateStore(RHS, LHSPtr);
		return RHS; 
	}
}

llvm::Value* Constant::IRGen(IRGenerator& IRContext) {
	std::cout << "Constant" << std::endl;
	VarType v(this->type_);

	switch(v.GetType()) {
		case Int: return IRBuilder.getInt32(this->int_); 
		case Char: return IRBuilder.getInt8(this->character_); 
		case Double:return llvm::ConstantFP::get(IRBuilder.getDoubleTy(), this->double_);
		case Bool:return IRBuilder.getInt1(this->bool_ ? 1 : 0);
	}
	return NULL;
}

llvm::Value* LeftVal::IRGen(IRGenerator& IRContext) {
	std::cout << "LeftVal" << std::endl;
	llvm::Value* VarPtr = IRContext.FindVar(this->name_);
	if (IRContext.IsPtrVar(this->name_)) {
		return VarPtr; 
	}else {
		llvm::Type* type = VarPtr->getType()->getNonOpaquePointerElementType();
		llvm::Value* val = IRBuilder.CreateLoad(type,VarPtr);
		return val;
	}
}

llvm::Value* LeftVal::IRGenPtr(IRGenerator& IRContext) {
	std::cout << "LeftValPtr" << std::endl;
	llvm::Value* VarPtr = IRContext.FindVar(this->name_);
	return VarPtr;
}

llvm::Value* StringType::IRGen(IRGenerator& IRContext) {
	std::cout << "StringType" << std::endl;
	return IRBuilder.CreateGlobalStringPtr(this->content_.c_str());
}


llvm::Value* ArrVal::IRGen(IRGenerator& IRContext) {
	std::cout << "ArrVal" << std::endl;
	llvm::Value* arrayPtr = IRContext.FindVar(this->name_);
	std::cout << "Array Ptr " << arrayPtr << std::endl; 
	std::vector<llvm::Value*> indices;
	for(auto expr : *(this->exprs_)){
		indices.push_back(expr->IRGen(IRContext));
	}
	llvm::Value* v1, *v2;
	for(auto indice: indices){
		if(arrayPtr->getType()->getNonOpaquePointerElementType()->isArrayTy()){
			v1 = IRBuilder.CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());	
		}else if(arrayPtr->getType()->isPointerTy()){
			v1 = IRBuilder.CreateLoad(arrayPtr->getType()->getNonOpaquePointerElementType(), arrayPtr);
		}else{
			throw std::logic_error("The sunsciption operation received neither array type nor pointer type");
		}
		v2 = IRBuilder.CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indice);
	}
	return IRBuilder.CreateLoad(v1->getType()->getNonOpaquePointerElementType(), v2);
}


llvm::Value* ArrVal::IRGenPtr(IRGenerator& IRContext) {
	std::cout << "ArrValPtr" << std::endl;
	llvm::Value* arrayPtr = IRContext.FindVar(this->name_);
	arrayPtr->print(llvm::outs());
	std::vector<llvm::Value*> indices;
	for(auto expr : *(this->exprs_)){
		indices.push_back(expr->IRGen(IRContext));
	}
	llvm::Value* v1, *v2;
	for(auto indice: indices){
		if(arrayPtr->getType()->getNonOpaquePointerElementType()->isArrayTy()){
			v1 = IRBuilder.CreatePointerCast(arrayPtr, arrayPtr->getType()->getNonOpaquePointerElementType()->getArrayElementType()->getPointerTo());	
		}else if(arrayPtr->getType()->isPointerTy()){
			v1 = IRBuilder.CreateLoad(arrayPtr->getType()->getNonOpaquePointerElementType(), arrayPtr);
		}else{
			throw std::logic_error("The sunsciption operation received neither array type nor pointer type");
		}
		v2 = IRBuilder.CreateGEP(v1->getType()->getNonOpaquePointerElementType(), v1, indice);
	}
	return v2;
}


VarType::VarType(std::string name) {
	if (name == "int") type = Int; 
	else if (name == "char") type = Char; 
	else if (name == "short") type = Short;
	else if (name == "double") type = Double;
	else if (name == "bool") type = Bool;
} 


llvm::Type* VarType::ToLLVMType(IRGenerator& IRContext) {
	switch(this->type) {
		case Int: return IRBuilder.getInt32Ty(); 
		case Char: return IRBuilder.getInt8Ty(); 
		case Short: return IRBuilder.getInt16Ty();
		case Double: return IRBuilder.getDoubleTy(); 
		case Bool: return IRBuilder.getInt1Ty(); 
		case Ptr: return this->baseTypePointer->ToLLVMType(IRContext);
	}
	return NULL;
}

llvm::Type* PointerType::ToLLVMType(IRGenerator& IRContext){
	std::cout << "PointerType" << std::endl;
	llvm::Type* BaseType = this->baseType_.ToLLVMType(IRContext);
	return llvm::PointerType::get(BaseType, 0U);
}

	

