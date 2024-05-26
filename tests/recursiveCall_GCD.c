int print(char ptr, ...);
int scan(char ptr, ...);

int GCD(int A, int B){
	if (A % B != 0)
    {
		return GCD(B, A % B);
    }
	return B;
}

int main(){
	int A, B;
    print("input number A and B: \n");
	scan("%d%d", &A, &B);
	print("GCD(%d,%d)=%d\n", A,B,GCD(A, B));
	return 0;
}