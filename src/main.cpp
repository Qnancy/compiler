#include <iostream>
#include <fstream>
#include <exception>
#include "AST.hpp"
#include "IRGenerator.hpp"

extern int yyparse();
extern BaseAST* Root;
extern int yydebug;
int main(int argc, const char* argv[]) {
    // yydebug = 1;
    std::string inputfile = argv[1];
    //std::string inputfile = "/home/compiler/tests/test1.c";

    std::string fileName = inputfile.substr(inputfile.rfind("/") + 1, inputfile.rfind(".") - (inputfile.rfind("/") + 1));
    std::string fileNamePath = inputfile.substr(0, inputfile.rfind("."));

    if (freopen(inputfile.c_str(), "r", stdin) == NULL)
       std::cout << "Open File Error!" << std::endl; ;
    yyparse();
    //Generating code
    IRGenerator Generator;
    Generator.GenerateCode(Root);
    
    Generator.GenObjectCode("io/"+ fileName +".o");
    Generator.GenAstTree("io/"+ fileName +".html",Root);
    Generator.DumpIRCode("io/"+fileName+".ir");

    std::cout << "Compile Success!" << std::endl;

    return 0;
}