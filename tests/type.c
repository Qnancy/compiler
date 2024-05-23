int print(char ptr, ...);
int scan(char ptr, ...);

int main(){
	print("Hello World!\n");

    short a = 3505;
    int b = -4282;
    char c = 'C';
    double d =3.1415;

    print("%d\n",a);
    print("%d\n",b);
    print("%c\n",c);
    print("%.3lf\n",d); //保留三位小数
	
    int arr1[10];
    double arr2[5][10];

	arr1[0]=321010;
	arr2[2][3]=5.2;

	print("%d\n",arr1[0]);
	print("%lf\n",arr2[2][3]);
	return 0;
}