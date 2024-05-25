int print(char ptr,...);
int scan(char ptr,...);

int main(){
  double arr2[5][10];
  arr2[2][3]=5.2;
  arr2[1][4]=2.5;
  print("%f\n",arr2[1][4]);
  double x;
  x=arr2[2][3];
  print("%f\n",x);
}