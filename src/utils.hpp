#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include "IRGenerator.hpp"

// 将给定的 LLVM 值转换为布尔类型。
// 如果输入值已经是布尔类型，则直接返回。
// 如果输入值是整数类型，则创建比较指令，以判断是否不等于零，从而得到布尔值。
// 如果输入值是浮点数类型，则创建浮点数比较指令，以判断是否不等于零，从而得到布尔值。
// 如果输入值是指针类型，则先将指针转换为整数类型，再进行比较。
// 如果输入值不属于上述任何一种类型，则抛出逻辑错误异常并返回空指针。
// 参数：
//   value: 要转换的 LLVM 值。
//   IRContext: IR 生成器对象，用于创建指令。
// 返回值：
//   如果成功转换，则返回布尔类型的 LLVM 值；如果无法转换，则抛出异常并返回空指针。
llvm::Value* ToBoolType(llvm::Value* value) {
	if (value->getType() == IRBuilder.getInt1Ty())
		return value;
	else if (value->getType()->isIntegerTy())
		return IRBuilder.CreateICmpNE(value, llvm::ConstantInt::get((llvm::IntegerType*)value->getType(), 0, true));
	else if (value->getType()->isFloatingPointTy())
		return IRBuilder.CreateFCmpONE(value, llvm::ConstantFP::get(value->getType(), 0.0));
	else if (value->getType()->isPointerTy())
		return IRBuilder.CreateICmpNE(IRBuilder.CreatePtrToInt(value, IRBuilder.getInt64Ty()), IRBuilder.getInt64(0));
	else {
		throw std::logic_error("Cannot cast to bool type.");
		return NULL;
	}
}

//类型转换
//支持以下转换：
//1. Int -> Int, FP, Pointer
//2. FP -> Int, FP
//3. Pointer -> Int, Pointer
//其他形式转换会返回NULL
llvm::Value* CastType(llvm::Value* value, llvm::Type* type){
	if(value->getType() == type){
		std::cout << "castNo" << std::endl;
		return value;
	}else if(type == IRBuilder.getInt1Ty()){
		std::cout << "cast2Bool" << std::endl;
		return ToBoolType(value);
	}else if(value->getType()->isIntegerTy() && type->isIntegerTy()){
		std::cout << "castInt2Int" << std::endl;
		return IRBuilder.CreateIntCast(value, type, !value->getType()->isIntegerTy(1));
	}else if(value->getType()->isIntegerTy() && type->isFloatingPointTy()) {
		std::cout << "castInt2FP" << std::endl;
		return value->getType()->isIntegerTy(1) ?
			IRBuilder.CreateUIToFP(value, type) : IRBuilder.CreateSIToFP(value, type);
	}else if (value->getType()->isIntegerTy() && type->isPointerTy()) {
		std::cout << "castInt2Ptr" << std::endl;
		return IRBuilder.CreateIntToPtr(value, type);
	}else if (value->getType()->isFloatingPointTy() && type->isIntegerTy()) {
		std::cout << "castFP2Int" << std::endl;
		return IRBuilder.CreateFPToSI(value, type);
	}
	else if (value->getType()->isFloatingPointTy() && type->isFloatingPointTy()) {
		std::cout << "castFP2FP" << std::endl;
		return IRBuilder.CreateFPCast(value, type);
	}
	else if (value->getType()->isPointerTy() && type->isIntegerTy()) {
		std::cout << "castPtr2Int" << std::endl;
		return IRBuilder.CreatePtrToInt(value, type);
	}
	else if (value->getType()->isPointerTy() && type->isPointerTy()) {
		std::cout << "castPtr2FP" << std::endl;
		return IRBuilder.CreatePointerCast(value, type);
	}
	else {
		return NULL;
	}
}

llvm::Value* TypeCasting(llvm::Value* Value, llvm::Type* Type, IRGenerator& IRContext) {
	if (Value->getType() == Type) {
		return Value;
	}
	else if (Type == IRBuilder.getInt1Ty()) {
		if (Value->getType() == IRBuilder.getInt1Ty())
			return Value;
		else if (Value->getType()->isIntegerTy())
			return IRBuilder.CreateICmpNE(Value, llvm::ConstantInt::get((llvm::IntegerType*)Value->getType(), 0, true));
		else if (Value->getType()->isFloatingPointTy())
			return IRBuilder.CreateFCmpONE(Value, llvm::ConstantFP::get(Value->getType(), 0.0));
		else if (Value->getType()->isPointerTy())
			return IRBuilder.CreateICmpNE(IRBuilder.CreatePtrToInt(Value, IRBuilder.getInt64Ty()), IRBuilder.getInt64(0));
	}
    else if (Type->isIntegerTy()) {
        if (Value->getType()->isIntegerTy())
            return IRBuilder.CreateIntCast(Value, Type, !Value->getType()->isIntegerTy(1));
        else if (Value->getType()->isFloatingPointTy())
            return IRBuilder.CreateFPToSI(Value, Type);
        else if (Value->getType()->isPointerTy())
            return IRBuilder.CreatePtrToInt(Value, Type);
    }
    else if (Type->isFloatingPointTy()) {
        if (Value->getType()->isIntegerTy())
            return Value->getType()->isIntegerTy(1) ? IRBuilder.CreateUIToFP(Value, Type) : IRBuilder.CreateSIToFP(Value, Type);
        else if (Value->getType()->isFloatingPointTy())
            return IRBuilder.CreateFPCast(Value, Type);
    }
    else if (Type->isPointerTy()) {
        if (Value->getType()->isIntegerTy())
            return IRBuilder.CreateIntToPtr(Value, Type);
        else if (Value->getType()->isPointerTy())
            return IRBuilder.CreatePointerCast(Value, Type);
    }
	else {
        throw std::logic_error("Cannot cast to target type.");
		return NULL;
	}
}

llvm::Value* TypeUpgrading(llvm::Value* Value, llvm::Type* Type, IRGenerator& IRContext) {
	if (Value->getType()->isIntegerTy() && Type->isIntegerTy()) {
		int Bit1 = ((llvm::IntegerType*)Value->getType())->getBitWidth();
		int Bit2 = ((llvm::IntegerType*)Type)->getBitWidth();
		if (Bit1 < Bit2) return IRBuilder.CreateIntCast(Value, Type, Bit1 != 1);
		else return Value;
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isFloatingPointTy()) {
		if (Value->getType()->isFloatTy() && Type->isDoubleTy()) return IRBuilder.CreateFPCast(Value, Type);
		else return Value;
	}
	else if (Value->getType()->isIntegerTy() && Type->isFloatingPointTy()) {
		return Value->getType()->isIntegerTy(1) ? IRBuilder.CreateUIToFP(Value, Type) : IRBuilder.CreateSIToFP(Value, Type);
	}
	else if (Value->getType()->isFloatingPointTy() && Type->isIntegerTy()) {
		return Value;
	}
	else return NULL;
}