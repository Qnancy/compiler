int factorial(int n) {
    if (n == 1) {
        return 1;
    } else {
        int ans = n * factorial(n - 1);
        return ans;
    }
}
