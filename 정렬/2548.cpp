#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> v;

int main(){
    cin >> N;
    for (int i = 0; i < N; i++){
        int n;
        cin >> n;
        v.push_back(n);
    }
    sort(v.begin(), v.end());
    if(v.size() % 2 == 0){
        cout << v[(v.size()/2) - 1];
    }
    else
        cout << v[v.size()/2];
}//............