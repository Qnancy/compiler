int print(char ptr, ...);

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int a = -10;    //Constant类
    int b = 5;
    char ptr c = "Global String";    //GlobalString类
    print("%s\n", c);
    int ptr f = &a;    //Addressof类
    print("%d\n", f);
}