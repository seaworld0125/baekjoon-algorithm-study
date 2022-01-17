#include <iostream>
#include <bitset>
using namespace std;

int main() {
    // int a = 5; // 101
    // int b = 6; // 110

    // a ^= b; // a = 011, b = 110
    // cout << a << ", " << b << endl;
    // b ^= a; // a = 011, b = 101
    // cout << a << ", " << b << endl;
    // a ^= b; // a = 110, b = 101
    // cout << a << ", " << b << endl;

    // cout << (1 << 0);

    // 10 -> 1010
    // 100 -> 110 0100

    bitset<5> a(1);
    cout << a << endl;
    cout << (a.any() ? "true" : "false") << endl;
    a[0] = 0;
    cout << (a.any() ? "true" : "false") << endl;
}