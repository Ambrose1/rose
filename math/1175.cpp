#include<iostream>

const int mod = 1e9+7;
bool isPrime(int n) {
	if (n==1)return false;
	for(int i=2; i*i <= n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

long cal(int n) {
	long f = 1;
	for (int i=1; i<=n; i++) {
		f = f*i%mod;
	}
	return f;
}

int func(int n) {
	int m = 0;
	for (int i=1; i<=n; i++) {
		if (isPrime(i)) {
			m++;
		}
	}
	return (int)(cal(m) * cal(n-m) % mod);
}

int main() {
	int n = func(100);
	printf("%d\n", n);
	return 0;
}