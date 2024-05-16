#include <iostream>
#include <fstream>
#include <exception>
#include "AST.hpp"
#include "IRGenerator.hpp"

extern int yyparse();
extern BaseAST* Root;
extern int yydebug;
int main() {
    yydebug = 1;
    std::string inputfile = "/home/compiler/tests/QuickSort/quicksort.c"; 

    std::string fileName = inputfile.substr(inputfile.rfind("/") + 1, inputfile.rfind(".") - (inputfile.rfind("/") + 1));
    std::string fileNamePath = inputfile.substr(0, inputfile.rfind("."));

    if (freopen(inputfile.c_str(), "r", stdin) == NULL)
       std::cout << "Open File Error!" << std::endl; ;
    yyparse();
    //Generating code
    IRGenerator Generator;
    Generator.GenerateCode(Root);
    
    Generator.GenObjectCode("/home/compiler/io/"+ fileName +".o");
    Generator.DumpIRCode("/home/compiler/io/"+fileName+".ir");

    std::cout << "Compile Success!" << std::endl;

    return 0;
}