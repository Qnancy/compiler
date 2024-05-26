int scan(char ptr, ...);
int print(char ptr, ...);

int main(){
    int a[12][12];
    int b[12][12];
    int c[12][12];
    int i,j,k,x;
    int n,m,p;
    print("Enter the dimensions for matrix M1 (n m): ");
    scan("%d %d", &n, &m);

    print("Enter the dimensions for matrix M2 (m p): ");
    scan("%d %d", &m, &p);

    // Validate dimensions
    if (n <= 0 || m <= 0 || p <= 0 || n > 10 || m > 10 || p > 10) {
        print("Invalid matrix dimensions. Exiting...\n");
        return 1;
    }
	print("Input a %d*%d matrix M1:\n",n,m);
	for (i = 0; i < n; i=i+1)
		for (j = 0; j < m; j=j+1)
        {
            scan("%d",&x);
            a[i][j]=x;
        }

	print("Input a %d*%d matrix M2:\n",m,p);
	for (i = 0; i < m; i=i+1)
		for (j = 0; j < p; j=j+1)
        {
            scan("%d",&x);
            b[i][j]=x;
        }

	for (i = 0; i < n; i=i+1)
		for (j = 0; j < p; j=j+1)
        {
            int sum=0;
			for (k = 0; k < m; k=k+1)
				sum = sum + a[i][k] * b[k][j];
            c[i][j]=sum;
        }
	print("M1 * M2:\n");
	for (i = 0; i < n; i=i+1)
    {
		for (j = 0; j < p; j=j+1)
			print("%d ", c[i][j]);
		print("\n");
	}
    return 0;
}
