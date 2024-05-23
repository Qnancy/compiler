int print(char ptr, ...);

int add(int a, int b)
{
    return a + b;
}

void main(void)
{
    int a = -2;    //Constant类
    int b = 5;
    //char ptr c = "Global String";    //GlobalString类
    int c = add(a, b);    //FunctionCall类
    print("%d\n",a);

    int d=a+b;
    print("%d\n",d);
    //int ptr f = &a;    //Addressof类
    
    //其他运算符，每类各选取几种代表的运算符
    //一元+，一元-
    // int up = +a;
    // int um = -b;
    // //位运算
    // int bitwiseOR = a | b;
    // int bitwiseAnd = a & b;
    // //逻辑运算
    // int logicOR = a || b;
    // int logicAnd = a && b;
    // //比较运算
    // int logicGT = (a > b);
    // int logicLE = (a <= b);
    // //算术运算
    int e = a + b;
    int f = a - b;
     print("%d\n", e);
     print("%d\n", f);
    // int mul = a * b;
    // int div = a / b;
    // int mod = a % b;
    
    // print("%d\n", a);    
    // print("%d\n", b); 
    // //print("%s\n", c);
    // print("%d\n", c);
    // print("%d\n", up);
    // print("%d\n", um);
    // print("%d\n", bitwiseOR);
    // print("%d\n", bitwiseAnd);
    // print("%d\n", logicOR);
    // print("%d\n", logicAnd);
    // print("%d\n", logicOR);
    // print("%d\n", logicGT);
    // print("%d\n", logicLE);
    //  print("%d\n", add);
    //  print("%d\n", sub);
    // print("%d\n", mul);
    // print("%d\n", div);
    // print("%d\n", mod);
}