int print(char ptr, ...);
int scan(char ptr, ...);

int main()
{
    int a,b;
    print("input number A: \n");
    scan("%d",&a);
    print("input number B: \n");
    scan("%d",&b);
    //If语句
    if(a<b){
        print("number A is smaller than B!\n");
    }
    else {
        if(a==b){
            print("number A is equal to B!\n");
        }
        else{ 
            print("number A is greater than B!\n");
        }
    }

    int n = 0;
    print("input a number A:\n");
    //While语句
    scan("%d",&a);
    while (a>1) 
    {
        a=a/2;
        n=n+1;
    }
    print("log2(A)=%d\n",n);

    print("Let's show from 000 to 111:\n");
    int i, j, k;
    //For语句
    for (i=0; i<2; i=i+1)
        for(j=0; j<2; j=j+1)
            for(k=0; k<2; k=k+1)
                print("%d %d %d\n", i, j, k);

    print("Let's print odd numbers between 0 and 10:\n");
    i = 0;
    while(1)
    {
        i=i+1;
        if(i % 2 == 0)
        {
            continue;	//Continue语句
        }
        if(i > 9)
        {
            break;	//Break语句
        }
        print("%d ", i);
    }
    print("\n");

    return 0; //return
}