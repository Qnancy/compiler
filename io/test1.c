int factorial(int n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}
int main() {
    int n = getint();
    int result = factorial(n);
    putint(result);
    return 0;
}
