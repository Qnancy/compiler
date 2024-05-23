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
		class VarDef;
		class ArrDef;
		using VarList = std::vector<VarDef*>;

class FuncDef;

/*** Variable Types ***/
class VarType;
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
	class ArrAssign;

class LeftVal;
class ArrVal;


//Class definitions
enum TypeID{
	Int, 
	Char, 
	Short,
	Double,
	Bool,
	Void,
	Ptr
};
class VarType {
public:
	VarType(std::string name);
	VarType(PointerType* _baseType_):baseTypePointer(_baseType_) {type=Ptr;}
	~VarType(){}
	TypeID GetType() {return type;}
	llvm::Type* ToLLVMType(IRGenerator&); 
	std::string getJson();
	
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
	std::string getJson();
};

//Pure virtual class for AST node
class BaseAST {
public:
	BaseAST() {}
	~BaseAST() {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
	virtual std::string getJson() = 0;
};

class Program : public BaseAST {
public:
	CompUnits* compUnit_;
	
	Program(CompUnits* _compUnit_):compUnit_(_compUnit_){}
	~Program(){};

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class CompUnit : public BaseAST {
public:
	CompUnit(){}
	~CompUnit(){}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
	virtual std::string getJson() = 0;
};

class FuncDef : public CompUnit {
public:
	std::string funcName_; 
	VarType type_; 
	ArgList* argList_;
	Block* funcBody_;

	FuncDef(std::string _typeName_, std::string _funcName_, ArgList* _argList_, Block* funcBody_ = NULL):
		type_(_typeName_), funcName_(_funcName_), argList_(_argList_),  funcBody_(funcBody_) {}
	~FuncDef(){};
	
	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};


class Decl : public CompUnit {
public:
	Decl() {}
	~Decl() {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
	virtual std::string getJson() = 0;
};

class VarDecl : public Decl {
public:
	VarType type_; 
	VarList* varList_;

	VarDecl(std::string _type_, VarList* _varList_) : 
		varList_(_varList_), type_(_type_) {}
	~VarDecl() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class VarDef: public BaseAST {
public:
	std::string varName_; 
	Expr* initValue_; 

	VarDef(std::string _varName_, Expr* _initValue_ = NULL) : 
		varName_(_varName_), initValue_(_initValue_) {}
	~VarDef() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class ArrDef : public BaseAST {
public:
	std::string arrName_;
	VarType type_;
	Exprs* exprs_;

	ArrDef(VarType _type_, std::string _arrName_, Exprs* _exprs_) : type_(_type_),arrName_(_arrName_), exprs_(_exprs_) {}
	~ArrDef() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();

};

class Stmt: public BaseAST {
public: 
	Stmt() {}
	~Stmt() {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
	virtual std::string getJson() = 0;
};

class Block : public Stmt {
public:
	Stmts* stmts_;
	int varCnt_;

	Block(Stmts* _stmts_): stmts_(_stmts_), varCnt_(0){}
	~Block(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class IfStmt : public Stmt {
public: 
	Expr* condition_; 
	Stmt* thenStmt_; 
	Stmt* elseStmt_; 

	IfStmt(Expr* _condition_, Stmt* _thenStmt_, Stmt* _elseStmt_  = NULL ):condition_(_condition_), thenStmt_(_thenStmt_), elseStmt_(_elseStmt_){}
	~IfStmt(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
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
	std::string getJson();
};

class WhileStmt : public Stmt {
public: 
	Expr* condExpr_; 
	Stmt* loopBody_; 

	WhileStmt(Expr* _condExpr_, Stmt* _loopBody_): 
		condExpr_(_condExpr_), loopBody_(_loopBody_) {}
	~WhileStmt(){}; 

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class ReturnStmt : public Stmt {
public:
	Expr* retVal_;

	ReturnStmt(Expr* _retVal_ = NULL) : retVal_(_retVal_) {}
	~ReturnStmt () {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class BreakStmt : public Stmt {
public: 
	BreakStmt(){}
	~BreakStmt(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
}; 

class ContinueStmt : public Stmt {
public: 
	ContinueStmt(){}
	~ContinueStmt(){}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
}; 

class Expr : public BaseAST {
public:
	Expr(void) {}
	~Expr(void) {}

	virtual llvm::Value* IRGen(IRGenerator& IRContext) = 0;
	virtual std::string getJson() = 0;
};

class UnaryPlus : public Expr {
public:
	Expr* operand_;

	UnaryPlus(Expr* _operand_) : operand_(_operand_) {}
	~UnaryPlus() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class UnaryMinus : public Expr {
public:
	Expr* operand_;

	UnaryMinus(Expr* _operand_) : operand_(_operand_) {}
	~UnaryMinus() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class AddressOf : public Expr {
public:
	LeftVal* oprand_;
	AddressOf(LeftVal* _oprand_) : oprand_(_oprand_) {}
	~AddressOf(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class Addition : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Addition(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Addition() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class Subtraction : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Subtraction(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Subtraction() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class Multiplication : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Multiplication(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Multiplication() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class Division : public Expr{
public:
	Expr* LHS_;
	Expr* RHS_;

	Division(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Division() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class Modulo : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	Modulo(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~Modulo() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
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
	std::string getJson();

};

class LogicEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class LogicNEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicNEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicNEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class LogicGEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicGEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicGEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class LogicGT : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicGT(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicGT() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class LogicLEQ : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicLEQ(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicLEQ() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class LogicLT : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicLT(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicLT() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class LogicAND : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicAND(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicAND() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class LogicOR : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	LogicOR(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~LogicOR() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class BitwiseAND : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	BitwiseAND(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~BitwiseAND() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class BitwiseXOR : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	BitwiseXOR(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~BitwiseXOR() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class BitwiseOR : public Expr {
public:
	Expr* LHS_;
	Expr* RHS_;

	BitwiseOR(Expr* _LHS_, Expr* _RHS_): LHS_(_LHS_), RHS_(_RHS_) {}
	~BitwiseOR() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};


class Assign : public Stmt {
public:
	LeftVal* LHS_;
	Expr* RHS_;

	Assign(LeftVal* _LHS_, Expr* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~Assign() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};


class LeftVal : public Expr {
public:
	std::string name_;

	LeftVal(std::string& _name_) : name_(_name_) {}
	~LeftVal() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	llvm::Value* IRGenPtr(IRGenerator& IRContext);
	std::string getJson();
};

class ArrVal : public LeftVal {
public:
	std::string name_;
	Exprs* exprs_;

	ArrVal(std::string _name_, Exprs* _exprs_) : LeftVal(_name_), name_(_name_), exprs_(_exprs_) {}
	~ArrVal() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	llvm::Value* IRGenPtr(IRGenerator& IRContext);
	std::string getJson();
};

class Constant : public Expr {
public:
	VarType type_; 
	int int_;
	char character_;
	double double_;
	bool bool_;
	
	Constant(int _int_) : type_("int"), int_(_int_) {}
	Constant(char _character_) : type_("char"), character_(_character_) {}
	Constant(double _double_) : type_("double"), double_(_double_) {}
	Constant(bool _bool_) : type_("bool"), bool_(_bool_) {}
	~Constant() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

class StringType : public Constant {
public:
	std::string content_;
	StringType(const std::string& _content_) : Constant(0), content_(_content_) {}
	~StringType(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
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
	std::string getJson();
};

class ArgList: public std::vector<Arg*>, public BaseAST {
public:
	//Set true if the argument list contains "..."
	bool varArgLenth_;
	void SetVarArg(void) { this->varArgLenth_ = true; }

	ArgList(void) : varArgLenth_(false) {}
	~ArgList(void) {}
	llvm::Value* IRGen(IRGenerator& IRContext) { return NULL; }
	std::string getJson();
};

class FuncCall : public Expr {
public:
	std::string funcName_;
	Exprs* argList_;

	FuncCall(const std::string& _funcName_, Exprs* _argList_) : funcName_(_funcName_), argList_(_argList_) {}
	~FuncCall(void) {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};



class ArrAssign : public Stmt {
public:
	ArrVal* LHS_;
	Expr* RHS_;

	ArrAssign(ArrVal* _LHS_, Expr* _RHS_) : LHS_(_LHS_), RHS_(_RHS_) {}
	~ArrAssign() {}

	llvm::Value* IRGen(IRGenerator& IRContext);
	std::string getJson();
};

extern BaseAST* Root;