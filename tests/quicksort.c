int print(int ptr, ...);
int scan(char ptr, ...);

static int a[10000];

int quicksort(int left, int right){
	int i = left;
	int	j = right;
	int temp = i + j;
	temp = temp/2;
	int mid;
	mid = a[temp];
	while (i < j){
		while (a[i] < mid) {
            i = i + 1;
        }
		while (mid < a[j]){
            j = j - 1;
        }
		if (i <= j){
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i = i + 1;
            j = j - 1;
		}
	}
	
	if (left < j) {
        quicksort(left, j);
    }
	if (i < right) {
        quicksort(i, right);
    }

    return 0;
}

int main(){
	int n;
    int temp;
	print("Input number of elements:\n");
	scan("%d", &n);
    int i;

	print("Input %d elements:\n",n);
	
	for (i = 0; i < n; i = i + 1){
        scan("%d", &temp);
        a[i] = temp;
    }
		
	print("Sorted elements:\n");
	quicksort(0, n - 1);
	for (i = 0; i < n; i=i+1){
		print("%d\n", a[i]);
    }
    
	return 0;
}