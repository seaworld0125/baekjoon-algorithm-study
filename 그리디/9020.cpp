#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num) {
	int tmp;
	tmp = sqrt(num);
	if (tmp == 1 && num != 1)
		return true;

	if (num % 2)
		for (int i = 2; i <= tmp; i++) {
			if (!(num%i)) return false;
			if (i == tmp) return true;
		}
}

int main() {
	int T;
	cin >> T;

	for (int j = 0; j < T; j++) {
		int n;
		cin >> n;

		for (int i = n / 2; i >= 2; i--)
			if (isPrime(i) && isPrime(n - i)) {
				cout << i << " " << n - i << '\n';
				break;
			}
	}
}