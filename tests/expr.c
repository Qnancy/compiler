int print(char ptr, ...);

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a = -10;    //Constant类
    int b = 5;
    // char ptr c = "Global String";    //GlobalString类
    int c = add(a, b);    //FunctionCall类
    // int ptr f = &a;    //Addressof类
    
    //其他运算符，每类各选取几种代表的运算符
    //一元+，一元-
    int unaryPlus = +a;
    int unaryMinus = -b;
    //位运算
    int bitwiseOR = a | b;
    int bitwiseAnd = a & b;
    //逻辑运算
    int logicOR = a || b;
    int logicAnd = a && b;
    //比较运算
    int logicGT = (a > b);
    int logicLE = (a <= b);
    //算术运算
    int add = a + b;
    int sub = a - b;
    int mul = a * b;
    int div = a / b;
    int mod = a % b;
    
    //优先级
    int res1 = c + a * b; 
    int res2 = a - -5 + b + -5;

    print("a = %d\n", a);    
    print("b = %d\n", b); 
    print("c = %d\n", c);
    print("+a = %d\n", unaryPlus);
    print("-b = %d\n", unaryMinus);
    print("a|b = %d\n", bitwiseOR);
    print("a&b = %d\n", bitwiseAnd);
    print("a||b = %d\n", logicOR);
    print("a&&b = %d\n", logicAnd);
    print("(a>b)= %d\n", logicOR);
    print("(a<=b) = %d\n", logicGT);
    print("(a<=b) = %d\n", logicLE);
    print("a+b = %d\n", add);
    print("a-b = %d\n", sub);
    print("a*b = %d\n", mul);
    print("a/b = %d\n", div);
    print("a%b = %d\n", mod);
    print("c+a*b = %d\n",res1);
    print("a - -5 + b + -5 = %d\n",res2);

    return 0;
}