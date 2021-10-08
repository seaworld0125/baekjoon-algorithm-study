#include <iostream>
using namespace std;

int a, b;
int main() {
	cin >> a >> b;
	int cnt = 0;
	while (1) {
		if (a > b) {
			cout << -1 << endl;
			break;
		}
		if (a == b) {
			cout << cnt + 1 << endl;
			break;
		}
		if (b % 10 == 1)
			b /= 10;
		else if (b % 2 == 0) 
			b /= 2;		
		else {
			cout << -1 << endl;
			break;
		}
		cnt++;
	}
}