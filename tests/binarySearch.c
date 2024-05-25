int print(char ptr, ...);
int scan(char ptr, ...);

int main() {
  int num;
  int arr[10];
  int  key;
  int i, res;
  int left, right;
  print("Input number of elements: (<=10) \n");
  scan("%d",&num);
  if (num > 10) {
    num = 10;
  }

  print("Input elements:\n");
  i = 0;
  int temp;
  while (i < num) {
    scan("%d", &temp);
    arr[i] = temp;
    i = i + 1;
  }

  print("Input key:\n");
  scan("%d",&key);

  left = 0;
  right = num - 1;
  while (left < right) {
    i = (left + right) / 2;
    if (arr[i] == key) {
        print("The %dth element is the key!\n",i+1);
      return 0;
    } else {
      if (arr[i] > key) {
        right = i - 1;
      } else {
        left = i + 1;
      }
    }
  }
    print("Key is not int the elements!\n");

  return 0;
}
