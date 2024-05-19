#include "AST.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

std::string escapeString(const std::string& str) {
    std::ostringstream oss;
    for (char c : str) {
        switch (c) {
            case '\"': oss << "\\\""; break;
            case '\'': oss << "\\\'"; break;
            case '\\': oss << "\\\\"; break;
            case '\n': oss << "\\n"; break;
            case '\t': oss << "\\t"; break;
            case '\r': oss << "\\r"; break;
            default:
                if (std::isprint(static_cast<unsigned char>(c))) {
                    oss << c;
                } else {
                    oss << "\\x" << std::hex << static_cast<unsigned int>(static_cast<unsigned char>(c));
                }
        }
    }
    return oss.str();
}

std::string makeJson(const std::string& name) {
    return "{ \"name\" : \"" + escapeString(name) + "\" }";
}

//non-leaf node
std::string makeJson(const std::string& name, const std::vector<std::string>& children) {
    std::ostringstream oss;
    oss << "{ \"name\" : \"" << name << "\", \"children\" : [ ";
    for (size_t i = 0; i < children.size(); ++i) {
        oss << children[i];
        if (i != children.size() - 1)
            oss << ", ";
    }
    oss << " ] }";
    return oss.str();
}

std::string makeJson(const std::string& name, const std::string& value) {
    return makeJson(name, std::vector<std::string>{value});
}


std::string Program::getJson() {
	std::vector<std::string> compUnitJson;	//children node json
	for (auto x : *compUnit_)
		compUnitJson.push_back(x->getJson());
	// children.push_back(makeJson("Decls", declJson));
	return makeJson("Program", compUnitJson);
	//return makeJson("program",std::vector<std::string>{Decl->makeJson()});
}

std::string FuncDef::getJson() {
	std::vector<std::string> children;
	children.push_back(makeJson("Return Type", type_.getJson()));
	children.push_back(makeJson("Function Name", makeJson(funcName_)));
	std::vector<std::string> argListJson;
	for (auto& x : *argList_)
		argListJson.push_back(x->getJson());
	if (argList_->varArgLenth_ == true)
		argListJson.push_back(makeJson("...", ""));
	children.push_back(makeJson("ArgList", argListJson));
	if (funcBody_ != NULL)
		children.push_back(funcBody_->getJson());
	return makeJson("FuncDefinition", children);
}

std::string ArgList::getJson() {
    return makeJson("..",makeJson(varArgLenth_ == true ? "True": "False"));
}

std::string Block::getJson() {
	std::vector<std::string> blockJson;	//children node json
	for (auto& x : *stmts_)
		blockJson.push_back(x->getJson());
	// children.push_back(makeJson("Decls", declJson));
	return makeJson("Block", blockJson);
}

std::string VarDecl::getJson() {
	std::vector<std::string> children;
	children.push_back(type_.getJson());
	std::vector<std::string> varListJson;
	for (auto& x : *varList_)
		varListJson.push_back(x->getJson());
	children.push_back(makeJson("VarList", varListJson));
	return makeJson("VarDeclaration", children);
}

std::string VarDef::getJson() {
	std::vector<std::string> children;
	children.push_back(makeJson(varName_));
	if (initValue_!= NULL)
	{
		//children.push_back(makeJson("="));
		children.push_back(initValue_->getJson());
	}
	// if(_InitialConstant != NULL)
	// {
	// children.push_back(makeJson("="));
	// children.push_back(makeJson("Initial Constant",_InitialConstant->getJson()));
	// }
	//children.push_back(_InitialExpr->getJson());
	//children.push_back(_InitialConstant->getJson());
	return makeJson("VarDefinition", children);
}

std::string PointerType::getJson() {
	std::vector<std::string> children;
	children.push_back(baseType_.getJson());
	return makeJson("PointerType", children);
	// return "";
}


std::string ArrDef::getJson() {
	std::vector<std::string> children;
	children.push_back(makeJson("Array Name", makeJson(arrName_)));
	children.push_back(type_.getJson());
	std::vector<std::string> exprsJson;
	for (auto& x : *exprs_)
		exprsJson.push_back(x->getJson());
	children.push_back(makeJson("Exprs", exprsJson));
	return makeJson("ArrayType", children);
	// return "";
}

std::string Arg::getJson()
{
	std::vector<std::string> children;
	children.push_back(type_.getJson());
	if (name_ != "") children.push_back(makeJson(name_));
	return makeJson("Arg", children);
	// return "";
}

std::string IfStmt::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(condition_->getJson());
	children.push_back(thenStmt_->getJson());
	if (elseStmt_ != NULL)
		children.push_back(elseStmt_->getJson());
	return makeJson("IfStmt", children);
}

std::string WhileStmt::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(condExpr_->getJson());
	if (loopBody_ != NULL)
		children.push_back(loopBody_->getJson());
	return makeJson("WhileStmt", children);
}


std::string ForStmt::getJson() {
	std::vector<std::string> children;	//children node json
	if (initStmt_ != NULL)
		children.push_back(initStmt_->getJson());
	if (condExpr_ != NULL)
		children.push_back(condExpr_->getJson());
	if (iterStmt_ != NULL)
		children.push_back(iterStmt_->getJson());
	if (loopBody_ != NULL)
		children.push_back(loopBody_->getJson());
	return makeJson("ForStmt", children);
}


std::string BreakStmt::getJson() {
	return makeJson("BreakStmt");
}

std::string ContinueStmt::getJson() {
	return makeJson("ContinueStmt");
}

std::string ReturnStmt::getJson() {
	std::vector<std::string> children;	//children node json
	if (retVal_ != NULL)
		children.push_back(retVal_->getJson());
	return makeJson("ReturnStmt", children);
}


std::string FuncCall::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(makeJson("Function Name", makeJson(funcName_)));
	std::vector<std::string> argListJson;
	for (auto x : *argList_)
		argListJson.push_back(x->getJson());
	children.push_back(makeJson("ArgList", argListJson));
	return makeJson("FunctionCall", children);
}

std::string UnaryPlus::getJson() {
	std::vector<std::string> children;	//children node json
	//children.push_back(makeJson("+"));
	children.push_back(operand_->getJson());
	return makeJson("UnaryPlus", children);
}

std::string UnaryMinus::getJson() {
	std::vector<std::string> children;	//children node json
	//children.push_back(makeJson("-"));
	children.push_back(operand_->getJson());
	return makeJson("UnaryMinus", children);
}


std::string AddressOf::getJson() {
	std::vector<std::string> children;	//children node json
	//children.push_back(makeJson("&"));
	children.push_back(oprand_->getJson());
	return makeJson("Addressof", children);
}

std::string LogicNot::getJson() {
	std::vector<std::string> children;	//children node json
	//children.push_back(makeJson("!"));
	children.push_back(RHS_->getJson());
	return makeJson("LogicNot", children);
}


std::string Division::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("/"));
	children.push_back(RHS_->getJson());
	return makeJson("Division", children);
}


std::string Multiplication::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("*"));
	children.push_back(RHS_->getJson());
	return makeJson("Multiplication", children);
}

std::string Modulo::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("%"));
	children.push_back(RHS_->getJson());
	return makeJson("Modulo", children);
}

std::string Addition::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("+"));
	children.push_back(RHS_->getJson());
	return makeJson("Addition", children);
}

std::string Subtraction::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("-"));
	children.push_back(RHS_->getJson());
	return makeJson("Subtraction", children);
}


std::string LogicGT::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson(">"));
	children.push_back(RHS_->getJson());
	return makeJson("LogicGT", children);
}

std::string LogicGEQ::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson(">="));
	children.push_back(RHS_->getJson());
	return makeJson("LogicGEQ", children);
}

std::string LogicLT::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("<"));
	children.push_back(RHS_->getJson());
	return makeJson("LogicLT", children);
}

std::string LogicLEQ::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("<="));
	children.push_back(RHS_->getJson());
	return makeJson("LogicLEQ", children);
}

std::string LogicEQ::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("=="));
	children.push_back(RHS_->getJson());
	return makeJson("LogicEQ", children);
}

std::string LogicNEQ::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("!="));
	children.push_back(RHS_->getJson());
	return makeJson("LogicNEQ", children);
}


std::string LogicAND::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("&&"));
	children.push_back(RHS_->getJson());
	return makeJson("LogicAND", children);
}

std::string LogicOR::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("||"));
	children.push_back(RHS_->getJson());
	return makeJson("LogicOR", children);
}

std::string BitwiseAND::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("||"));
	children.push_back(RHS_->getJson());
	return makeJson("BitwiseAND", children);
}
std::string BitwiseXOR::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("||"));
	children.push_back(RHS_->getJson());
	return makeJson("BitwiseXOR", children);
}

std::string BitwiseOR::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("||"));
	children.push_back(RHS_->getJson());
	return makeJson("BitwiseOR", children);
}

std::string Assign::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(LHS_->getJson());
	//children.push_back(makeJson("="));
	children.push_back(RHS_->getJson());
	return makeJson("DirectAssign", children);
}
std::string StringType::getJson() {
	std::vector<std::string> children;	//children node json
	children.push_back(makeJson("\"" + escapeString(content_) + "\""));
	return makeJson("Global std::string", children);
}


std::string Constant::getJson() {
	std::vector<std::string> children;	//children node json
	switch (type_.GetType())
	{
	case TypeID::Bool:
		return (bool_ == true) ? makeJson("Constant", makeJson("True")) : makeJson("Constant", makeJson("False"));
		break;
	case TypeID::Short:
	case TypeID::Int:
		return makeJson("Constant", makeJson(std::to_string(int_)));
		break;
	case TypeID::Char:
		return makeJson("Constant", makeJson("\'" + escapeString(std::string(1, character_)) + "\'"));
		break;
	case TypeID::Double:
		return makeJson("Constant", makeJson(std::to_string(double_)));
		break;
	default:
		break;
	}
}
std::string VarType::getJson() {
	std::string typeStr;
	switch (GetType()) {
        case Int: typeStr = "Int";break;
        case Char: typeStr = "Char";break;
        case Short: typeStr = "Short";break;
        case Double: typeStr = "Double";break;
        case Bool: typeStr = "Bool";break;
        case Ptr: typeStr = "Ptr";break;
        default: typeStr = "Unknown";break;
	}
	std::vector<std::string> children;	//children node json
	children.push_back(makeJson(typeStr));
	return makeJson("VarType", children);
}

std::string ArrAssign::getJson() {
	std::vector<std::string> children;
	children.push_back(LHS_->getJson());
	children.push_back(RHS_->getJson());
	return makeJson("ArrayType", children);
	// return "";
}

std::string ArrVal::getJson() {
	std::vector<std::string> children;
	children.push_back(makeJson("Array Name", makeJson(name_)));
	std::vector<std::string> exprsJson;
	for (auto x : *exprs_)
		exprsJson.push_back(x->getJson());
	children.push_back(makeJson("Exprs", exprsJson));
	return makeJson("ArrayVal", children);
}

std::string LeftVal::getJson() {
	std::vector<std::string> children;
	children.push_back(makeJson(name_));
	return makeJson("LeftVal",children);
}