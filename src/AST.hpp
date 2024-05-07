#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>

class IRGenerator;
class BaseAST;

/*** Root ***/
class Program;

class CompUnit;
using CompUnits = std::vector<CompUnit*>;

/*** Declarations ***/
class Decl;
using Decls = std::vector<Decl*>;
	class FunDecls;
		class Arg;
		class ArgList;
	class VarDecl;
class FuncDef;

/*** Variable Types ***/
class VarType;
class VarDef;
class PointerType;

class Block;
/*** Statements ***/
class Stmt;
using Stmts = std::vector<Stmt*>;
	class IfStmt;
	class ForStmt;
	class WhileStmt;
	class BreakStmt;
	class ContinueStmt;
	class ReturnStmt;
	

/*** Expressions ***/
class Expr;
	using ExprList = std::vector<Expr*>;
	using Exprs = std::vector<Expr*>;
	class FuncCall;
	class UnaryPlus;
	class UnaryMinus;
	class AddressOf;
	class LogicNot;
	class LogicAND;
	class LogicOR;
	class Division;
	class Multiplication;
	class Modulo;
	class Addition;
	class Subtraction;
	class LogicGT;
	class LogicGEQ;
	class LogicLT;
	class LogicLEQ;
	class LogicEQ;
	class LogicNEQ;
	class Assign;
	class Constant;
		class StringType;
	class AssignArr;

class LeftVal;
class ArrVal;


//Class definitions
enum TypeID{
	Int, 
	Char, 
	Short,
	Double,
	Bool,
	Ptr
};
class VarType {
public:
	VarType(std::string name);
	VarType(PointerType* baseType):baseTypePointer(baseType) {type=Ptr;}
	~VarType(){}
	TypeID GetType() {return type;}
	llvm::Type* ToLLVMType(IRGenerator&); 
	
private: 
	TypeID type;
	PointerType* baseTypePointer;
};

class PointerType{
public:
	VarType baseType_;

	PointerType(VarType _baseType_) : baseType_(_baseType_) {}
	~PointerType(void) {}
	llvm::Type* ToLLVMType(IRGenerator& IRContext);
};

//Pure virtual class for AST node
class BaseAST {
public:
	BaseAST() {}
	~BaseAST() {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class Program : public BaseAST {
public:
	CompUnits* compUnit_;
	
	Program(CompUnits* _compUnit_):compUnit_(_compUnit_){}
	~Program(){};

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class CompUnit : public BaseAST {
public:
	CompUnit(){}
	~CompUnit(){}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class FuncDef : public CompUnit {
public:
	std::string funcName_; 
	VarType type_; 
	ArgList* argList_;
	Block* block_;

	FuncDef(std::string _typeName_, std::string _funcName_, ArgList* _argList_, Block* _block_ = NULL):
		type_(_typeName_), funcName_(_funcName_), argList_(_argList_),  block_(_block_) {}
	~FuncDef(){};
	
	llvm::Value* IRGen(IRGenerator& IRContext);
};


class Decl : public CompUnit {
public:
	Decl() {}
	~Decl() {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class VarDecl : public Decl {
public:
	VarDef* varDef_;
	VarType type_; 

	VarDecl(std::string _typeName_, VarDef* _varDef_) : 
		varDef_(_varDef_), type_(_typeName_) {}
	~VarDecl() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class VarDef: public BaseAST {
public:
	std::string varName_; 
	Expr* initValue_; 

	VarDef(std::string _varName_, Expr* _initValue_ = NULL) : 
		varName_(_varName_), initValue_(_initValue_) {}
	~VarDef() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class ArrDef : public BaseAST {
public:
	llvm::Type* elementType_;
	llvm::Type* arrayType_;
	std::string arrName_;
	VarType type_;
	Exprs* exprs_;

	ArrDef(std::string _typeName_, std::string _arrName_, Exprs* _exprs_) :
	type_(_typeName_), arrName_(_arrName_), exprs_(_exprs_) {}
	~ArrDef() {}

	llvm::Value* IRGen(IRGenerator& IRContext);

};

class Block : public BaseAST {
public:
	Stmts* stmts_;
	int varCnt_;

	Block(Stmts* _stmts_): stmts_(_stmts_), varCnt_(0){}
	~Block(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Stmt: public BaseAST {
public: 
	Stmt() {}
	~Stmt() {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class IfStmt : public Stmt {
public: 
	Expr* condition_; 
	Stmt* thenStmt_; 
	Stmt* elseStmt_; 

	IfStmt(Expr* _condition_, Stmt* _thenStmt_, Stmt* _elseStmt_  = NULL ):condition_(_condition_), thenStmt_(_thenStmt_), elseStmt_(_elseStmt_){}
	~IfStmt(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class ForStmt : public Stmt {
public: 
	Stmt* initStmt_; 
	Expr* condExpr_; 
	Stmt* iterStmt_; 
	Stmt* loopBody_; 

	ForStmt(Stmt* _initStmt_, Expr* _condExpr_, Stmt* _iterStmt_, Stmt* _loopBody_):
		initStmt_(_initStmt_), condExpr_(_condExpr_), iterStmt_(_iterStmt_), loopBody_(_loopBody_){}
	~ForStmt(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class WhileStmt : public Stmt {
public: 
	Expr* condExpr_; 
	Stmt* loopBody_; 

	WhileStmt(Expr* _condExpr_, Stmt* _loopBody_): 
		condExpr_(_condExpr_), loopBody_(_loopBody_) {}
	~WhileStmt(){}; 

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class ReturnStmt : public Stmt {
public:
	Expr* retVal_;

	ReturnStmt(Expr* _retVal_ = NULL) : retVal_(_retVal_) {}
	~ReturnStmt () {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class BreakStmt : public Stmt {
public: 
	BreakStmt(){}
	~BreakStmt(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
}; 

class ContinueStmt : public Stmt {
public: 
	ContinueStmt(){}
	~ContinueStmt(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
}; 

class Expr : public BaseAST {
public:
	Expr(void) {}
	~Expr(void) {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
};

class UnaryPlus : public Expr {
public:
	Expr* operand_;

	UnaryPlus(Expr* _operand_) : operand_(_operand_) {}
	~UnaryPlus() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class UnaryMinus : public Expr {
public:
	Expr* operand_;

	UnaryMinus(Expr* _operand_) : operand_(_operand_) {}
	~UnaryMinus() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class AddressOf : public Expr {
public:
	LeftVal* oprand_;
	AddressOf(LeftVal* _oprand_) : oprand_(_oprand_) {}
	~AddressOf(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Addition : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Addition(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Addition() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Subtraction : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Subtraction(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Subtraction() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Multiplication : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Multiplication(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Multiplication() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Division : public Expr{
public:
	Expr* LHS_;
	Expr* RHS_;

	Division(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Division() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class Modulo : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Modulo(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Modulo() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

/**
 * @brief 逻辑运算
 * 
 */
class LogicNot : public Expr {
public:
	Expr* RHS_;

	LogicNot(Expr* _RHS_) : RHS_(_RHS_) {}
	~LogicNot() {}

	llvm::Value* IRGen(IRGenerator& IRContext);

};

class LogicEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LogicNEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicNEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicNEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LogicGEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicGEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicGEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LogicGT : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicGT(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicGT() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LogicLEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicLEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicLEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LogicLT : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicLT(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicLT() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LogicAND : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicAND(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicAND() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LogicOR : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicOR(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicOR() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class BitwiseAND : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	BitwiseAND(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~BitwiseAND() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class BitwiseXOR : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	BitwiseXOR(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~BitwiseXOR() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class BitwiseOR : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	BitwiseOR(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~BitwiseOR() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};


class Assign : public Stmt {
public:
	LeftVal* LHS_;
	Expr* RHS_;

	Assign(LeftVal* _LHS_, Expr* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~Assign() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class LeftVal : public Expr {
public:
	std::string name_;

	LeftVal(std::string& _name_) : name_(_name_) {}
	~LeftVal() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	llvm::Value* IRGenPtr(IRGenerator& IRContext);
};

class Constant : public Expr {
public:
	VarType type_; 
	int int_;
	char character_;
	double double_;
	
	Constant(int _int_) : type_("int"), int_(_int_) {}
	Constant(char _character_) : type_("char"), character_(_character_) {}
	Constant(double _double_) : type_("double"), double_(_double_) {}
	~Constant() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class StringType : public Constant {
public:
	std::string content_;
	StringType(const std::string& _content_) : Constant(0), content_(_content_) {}
	~StringType(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext);
};

//Function argument
class Arg : public BaseAST {
public:
	//Its type
	VarType type_;
	//Its name (if any)
	std::string name_;

	Arg(std::string& _typeName_, const std::string& _name_ = "") :
		type_(_typeName_), name_(_name_) {}
	Arg(PointerType* _typeName_, const std::string& _name_ = "") :
		type_(_typeName_), name_(_name_) {}
	~Arg(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext) { return NULL; }
};

class ArgList: public std::vector<Arg*>, public BaseAST {
public:
	//Set true if the argument list contains "..."
	bool varArgLenth_;
	void SetVarArg(void) { this->varArgLenth_ = true; }

	ArgList(void) : varArgLenth_(false) {}
	~ArgList(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext) { return NULL; }
};

class FuncCall : public Expr {
public:
	std::string funcName_;
	ExprList* argList_;

	FuncCall(const std::string& _funcName_, ExprList* _argList_) : funcName_(_funcName_), argList_(_argList_) {}
	~FuncCall(void) {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

class ArrVal : public Expr {
public:
	std::string name_;
	Exprs* exprs_;

	ArrVal(std::string _name_, Exprs* _exprs_) : name_(_name_), exprs_(_exprs_) {}
	~ArrVal() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	llvm::Value* IRGenPtr(IRGenerator& IRContext);
};

class AssignArr : public Stmt {
public:
	ArrVal* LHS_;
	Expr* RHS_;

	AssignArr(ArrVal* _LHS_, Expr* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~AssignArr() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
};

extern BaseAST* Root;