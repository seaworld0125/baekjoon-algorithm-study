#include <iostream>
using namespace std;

int * func() {
    int * val = new int[2];
    val[0] = 0;
    val[1] = 1;
    return val;
}

int main() {
    int * val = func();
    cout << val[0];
    delete val;
}