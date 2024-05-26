int print(char ptr, ...);
int scan(char ptr, ...);

int main(){
	print("Hello World!\n");

    //基本类型
    short a = 3505; //Constant类
    int b = -4282;
    char c = 'C';
    double d =3.1415;
    char ptr e = "Global String";    //GlobalString类
    int ptr f = &a;    //Addressof类

    print("short : %d\n",a);
    print("int : %d\n",b);
    print("char : %c\n",c);
    print("double : %.3lf\n",d); //保留三位小数
    print("string : %s\n",e);
	
    //数组类型
    int arr1[10];
    double arr2[5][10];

	arr1[0]=321010;
	arr2[2][3]=5.2;

	print("array1 : %d\n",arr1[0]);
	print("array2 : %lf\n",arr2[2][3]);
	return 0;
}