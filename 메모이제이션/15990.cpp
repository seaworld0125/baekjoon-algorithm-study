#include <stdio.h>
#include <iostream>
#include <vector>
 
using namespace std;
 
long long ans[100001][4];
 
int main() {
    int tastcase;
 
    cin >> tastcase;
 
    ans[0][1] = 0;
    ans[0][2] = 0;
    ans[0][3] = 0;
 
    ans[1][1] = 1;
    ans[1][2] = 0;
    ans[1][3] = 0;
 
    ans[2][1] = 0;
    ans[2][2] = 1;
    ans[2][3] = 0;
 
    ans[3][1] = 1;
    ans[3][2] = 1;
    ans[3][3] = 1;
 
    for (int i = 4; i <= 100000; i++) {
        ans[i][1] = (ans[i - 1][2] + ans[i - 1][3]) % 1000000009;
        ans[i][2] = (ans[i - 2][1] + ans[i - 2][3]) % 1000000009;
        ans[i][3] = (ans[i - 3][1] + ans[i - 3][2]) % 1000000009;
    }
 
    while (tastcase--) {
        int n;
 
        cin >> n;
        
        cout<< (ans[n][1] + ans[n][2] + ans[n][3]) % 1000000009 <<endl;
    }
}
