%{
    #define YYDEBUG 1
    #include "AST.hpp"
    #include <iostream>
    #include <string>
    extern int yylex(void);
    extern BaseAST* Root; 

    void yyerror(char *s)
    {
        extern int yylineno;	// defined and maintained in lex
        extern char *yytext;	// defined and maintained in lex
        int len=strlen(yytext);
        int i;
        char buf[512]={0};
        for (i=0;i<len;++i)
        {
            sprintf(buf,"%s%d ",buf,yytext[i]);
        }
        fprintf(stderr, "ERROR: %s at symbol '", s);
        fwrite(yytext, len, 1, stderr);
        fprintf(stderr, "' on line %d\n", yylineno);
    }
%}

%output "parser.cpp"

%union {
    int intVal;
    double douVal;
	char charVal;
    std::string* strVal;
    BaseAST *astVal;
	CompUnits *compUnits;
	Stmts *stmts;
	Exprs *exprs;
    Arg *argVal;
    ArgList *argList;
    Expr *expVal;
    PointerType *ptrType;
    VarDef *varDef;
    VarList *varList;
}

/* 终结符 */
// lexer 返回的所有 token 种类的声明
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE COMMA SEMI
%token EQ NEQ LT LEQ GT GEQ
%token ADD SUB MUL DIV MOD
%token AND OR NOT
%token BAND BOR BXOR
%token ASSIGN 
%token DOT COLON QUES ELLIPSES PTR

%token <strVal> INT SHORT CHAR VOID DOUBLE BOOL
%token RETURN CONTINUE BREAK 
%token IF ELSE 
%token FOR WHILE
%token TRUE FALSE STATIC 

%token CONST
%token <strVal> IDENTIFIER
%token <intVal> CONST_INT 
%token <charVal> CONST_CHAR 
%token <strVal> CONST_STR
%token <douVal> CONST_DOUBLE
%token CONST_FLOAT

// 非终结符的类型定义
%type <astVal> Program
%type <compUnits> CompUnit
%type <astVal> FuncDef
%type <strVal> FuncType

%type <argList> ArgList
%type <argList> _ArgList
%type <argVal> Arg
%type <ptrType> PtrType

%type <exprs> ExpList
%type <exprs> _ExpList

%type <astVal> Decl
%type <astVal> ConstExp
%type <astVal> VarDecl
%type <strVal> Btype
%type <varList> VarList
%type <varDef> VarDef
%type <exprs> ArrDef ArrVal
%type <astVal> InitVal

%type <astVal> Block
%type <astVal> BlockItem 
%type <stmts>  BlockItem_
%type <astVal> Stmt Stmt_ IfStmt ForStmt WhileStmt BreakStmt ContinueStmt ReturnStmt

%type <astVal> PrimaryExp
%type <astVal> Exp

%type <astVal> LVal
%type <astVal> Constant


/* 优先级和结合性定义 */
%right	ASSIGN
%left	OR
%left	AND
%left	BOR
%left	BXOR
%left	BAND
%left	EQ NEQ
%left	GEQ GT LT LEQ
%left	ADD SUB
%left	MUL DIV MOD

%start Program

%%

/* CompUnit      ::= [CompUnit] (Decl | FuncDef); */

Program							
	: CompUnit 											    { $$ = new Program((CompUnits*)$1); Root = $$;}
	;

CompUnit
    : CompUnit STATIC Decl                      		    { $$ = (CompUnits*)$1; $$->push_back((CompUnit*)$3); }
    | CompUnit FuncDef									    { $$ = (CompUnits*)$1; $$->push_back((CompUnit*)$2); }
    | 													    { $$ = new CompUnits(); }
    ;

/* Decl          ::= VarDecl; */
Decl
    : VarDecl                                               { $$ = $1; }
    ;

/* BType         ::= "int"; */
Btype
    : VOID                                                  { $$ = $1; }
    | INT                                                   { $$ = $1; }
    | SHORT                                                 { $$ = $1; }
    | CHAR                                                  { $$ = $1; }
	| DOUBLE 						                        { $$ = $1; }
    | BOOL                                                  { $$ = $1; }
    ;


/* VarDecl       ::= BType VarDef {"," VarDef} ";"; */
VarDecl
    : Btype VarList SEMI                                    { $$ = new VarDecl(*$1, (VarList*)$2);}
    | Btype IDENTIFIER ArrDef SEMI                          { $$ = new ArrDef(*$1, *$2, (Exprs*)$3);}
    ;

VarList
    : VarDef                                                { $$ = new VarList(); $$->push_back($1); }
    | VarList COMMA VarDef                                  { $$ = $1; $$->push_back($3); }
    ;


/* VarDef        ::= IDENT | IDENT "=" InitVal; | IDENT {"[" INT_CONST "]"}*/
VarDef
    : IDENTIFIER                                            { $$ = new VarDef(*$1);}
    | IDENTIFIER ASSIGN InitVal                             { $$ = new VarDef(*$1, (Expr*)$3);}
    ;

ArrDef
	: ArrDef LBRACKET ConstExp RBRACKET 			        { $$ = (Exprs*)$1; $$->push_back((Expr*)$3); }
	| 												        { $$ = new Exprs(); }
	;

ConstExp
	: CONST_INT							                    { $$ = new Constant($1); }

/* InitVal       ::= Exp; */
InitVal
    : Exp                                                   { $$ = $1; }
    ;

/* FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block; */

FuncDef
    : FuncType IDENTIFIER LPAREN ArgList RPAREN SEMI        { $$ = new FuncDef(*$1, *$2, (ArgList*)$4); }
    | FuncType IDENTIFIER LPAREN ArgList RPAREN Block       { $$ = new FuncDef(*$1, *$2, (ArgList*)$4, (Block*)$6); }
    ;

/* FuncType      ::= "void" | "int"; */
FuncType
    : INT                                                   { $$ = $1; }
    | VOID                                                  { $$ = $1; }
    | CHAR                                                  { $$ = $1; }
    ;

/*FuncFParams   ::= FuncFParam {"," FuncFParam};*/
/*FuncFParam    ::= BType IDENT ["[" "]" {"[" INT_CONST "]"}];*/

ArgList
    : _ArgList COMMA Arg									{ $$ = $1; $$->push_back($3);   }
	| _ArgList COMMA ELLIPSES								{ $$ = $1; $$->SetVarArg();   }
	| Arg													{ $$ = new ArgList(); $$->push_back($1);   }
	| ELLIPSES												{ $$ = new ArgList(); $$->SetVarArg();   }
	|														{ $$ = new ArgList(); }
	;

_ArgList
    : _ArgList COMMA Arg									{ $$ = $1; $$->push_back($3);   }	 
	| Arg													{ $$ = new ArgList(); $$->push_back($1);   }
	;

Arg
    : Btype IDENTIFIER										{ $$ = new Arg(*$1, *$2);   }
	| PtrType IDENTIFIER							        { $$ = new Arg($1, *$2);   }
	| PtrType 							                    { $$ = new Arg($1);   }
    | Btype                                                 { $$ = new Arg(*$1);   }

PtrType
    : Btype PTR                                             { $$ = new PointerType(*$1); }
    ;

/* Block         ::= "{" {BlockItem} "}"; */
Block
    : LBRACE BlockItem_ RBRACE                              { $$ = new Block((Stmts*)$2);}
    ;

BlockItem_
    : BlockItem_ BlockItem					                { $$ = (Stmts*)$1; if ($2 != NULL) $$->push_back((Stmt*)$2); }
    | 											            { $$ = new Stmts(); }
    ;

/* BlockItem     ::= Decl | Stmt; */
BlockItem
    : Decl                                                  { $$ = $1;}
    | Stmt										            { $$ = $1;}
    ;

/* Stmt          ::= LVal "=" Exp ";"
                | Exp ";"
                | Block
                | "if" "(" Exp ")" Stmt ["else" Stmt]
                | "while" "(" Exp ")" Stmt
                | "break" ";"
                | "continue" ";"
                | "return" [Exp] ";"; */

Stmt
    : Stmt_ SEMI											{  $$ = $1;   }
    | Block													{  $$ = $1;   }
    | IfStmt												{  $$ = $1;   }
    | ForStmt												{  $$ = $1;   }
    | WhileStmt												{  $$ = $1;   }
    | BreakStmt												{  $$ = $1;   }
    | ContinueStmt											{  $$ = $1;   }
    | ReturnStmt											{  $$ = $1;   }
    | SEMI													{  $$ = NULL;   }

Stmt_
    : LVal ASSIGN Exp                                       { $$ = new Assign((LeftVal*)$1, (Expr*)$3); }
    | Exp                                                   { $$ = $1; }

IfStmt
    : IF LPAREN Exp RPAREN Stmt ELSE Stmt				    {  $$ = new IfStmt((Expr*)$3, (Stmt*)$5, (Stmt*)$7);   }
	| IF LPAREN Exp RPAREN Stmt         					{  $$ = new IfStmt((Expr*)$3, (Stmt*)$5);   }
	;

ForStmt
    : FOR LPAREN Stmt Exp SEMI Stmt_ RPAREN Stmt		    {  $$ = new ForStmt((Stmt*)$3, (Expr*)$4, (Stmt*)$6, (Stmt*)$8);   }
    | FOR LPAREN VarDecl Exp SEMI Stmt RPAREN Stmt	        {  $$ = new ForStmt((Stmt*)$3, (Expr*)$4, (Stmt*)$6, (Stmt*)$8);   }
	;

WhileStmt
    : WHILE LPAREN Exp RPAREN Stmt						    {  $$ = new WhileStmt((Expr*)$3, (Stmt*)$5);   }
	;

BreakStmt
    : BREAK SEMI											{  $$ = new BreakStmt();   }
	;

ContinueStmt
    : CONTINUE SEMI											{  $$ = new ContinueStmt();   }
	;

ReturnStmt
    : RETURN SEMI 											{  $$ = new ReturnStmt();   }
	| RETURN Exp SEMI										{  $$ = new ReturnStmt((Expr*)$2);   }
	;

/* Exp           ::= LOrExp; */
/* LVal          ::= IDENT {"[" Exp "]"}; */
LVal
    : IDENTIFIER								            { $$ = new LeftVal(*$1); }
    | IDENTIFIER ArrVal                                     { $$ = new ArrVal(*$1, (Exprs*)$2); }
    ;

ArrVal
    : ArrVal LBRACKET Exp RBRACKET		                    { $$ = (Exprs*)$1; $$->push_back((Expr*)$3); }
	|									                    { $$ = new Exprs(); }
	;

Exp
    : PrimaryExp						                    { $$ = $1; }	
    | ADD Exp %prec NOT					                    { $$ = new UnaryPlus((Expr*)$2); }
    | SUB Exp %prec NOT					                    { $$ = new UnaryMinus((Expr*)$2); }
    | NOT Exp							                    { $$ = new LogicNot((Expr*)$2); }
    | BAND LVal	%prec NOT			                        { $$ = new AddressOf((LeftVal*)$2); }

    | Exp ADD Exp						                    { $$ = new Addition((Expr*)$1, (Expr*)$3);}
    | Exp SUB Exp						                    { $$ = new Subtraction((Expr*)$1, (Expr*)$3);}
    | Exp MUL Exp						                    { $$ = new Multiplication((Expr*)$1, (Expr*)$3);}
    | Exp DIV Exp						                    { $$ = new Division((Expr*)$1, (Expr*)$3);}
    | Exp MOD Exp						                    { $$ = new Modulo((Expr*)$1, (Expr*)$3);}

    | Exp EQ Exp						                    { $$ = new LogicEQ((Expr*)$1, (Expr*)$3);}
    | Exp NEQ Exp						                    { $$ = new LogicNEQ((Expr*)$1, (Expr*)$3);}
    | Exp LT Exp						                    { $$ = new LogicLT((Expr*)$1, (Expr*)$3);}
    | Exp LEQ Exp						                    { $$ = new LogicLEQ((Expr*)$1, (Expr*)$3);}
    | Exp GT Exp						                    { $$ = new LogicGT((Expr*)$1, (Expr*)$3);}
    | Exp GEQ Exp						                    { $$ = new LogicGEQ((Expr*)$1, (Expr*)$3);}

    | Exp AND Exp						                    { $$ = new LogicAND((Expr*)$1, (Expr*)$3);}
    | Exp OR  Exp						                    { $$ = new LogicOR((Expr*)$1, (Expr*)$3);}

    | Exp BAND Exp                                          { $$ = new BitwiseAND((Expr*)$1, (Expr*)$3);}
    | Exp BOR  Exp                                          { $$ = new BitwiseOR((Expr*)$1, (Expr*)$3);}
    | Exp BXOR Exp                                          { $$ = new BitwiseXOR((Expr*)$1, (Expr*)$3);}

    | IDENTIFIER LPAREN ExpList RPAREN	                    { $$ = new FuncCall(*$1, (Exprs*)$3);   }
	;

/* PrimaryExp    ::= "(" Exp ")" | LVal | Number; */
PrimaryExp
    : LPAREN Exp RPAREN					                    { $$ = $2; }
    | LVal								                    { $$ = $1; }
    | Constant							                    { $$ = $1; }	
    ;

/* Number        ::= INT_CONST; */
Constant
    : CONST_INT							                    { $$ = new Constant($1); }
    | CONST_CHAR						                    { $$ = new Constant($1); }
    | CONST_STR                                             { $$ = new StringType(*$1); }
	| CONST_DOUBLE						                    { std::cout << $1 << std::endl;  $$ = new Constant($1); }
    ;

ExpList
    : _ExpList COMMA Exp							        { $$ = $1; $$->push_back((Expr*)$3);   }
	| Exp                           					    { $$ = new Exprs(); $$->push_back((Expr*)$1);   }
	|													    { $$ = new Exprs();   }
	;

_ExpList
    : _ExpList COMMA Exp 								    { $$ = $1; $$->push_back((Expr*)$3);   }
	| Exp                       						    { $$ = new Exprs(); $$->push_back((Expr*)$1);   }
	;

%%
