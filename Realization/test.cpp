#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> a = {1,7, 5, 5, 5, 4, 3};

    sort(a.begin(), a.end(), [](int a, int b) {
        return a > b;
    });

    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
}