#include <iostream>
#include <queue>
using namespace std;

int main(){
    int N, n;
    cin >> N;
    priority_queue<int> q;
    for(int i = 0; i < N*N; i++){
        cin >> n;
        q.push(n);
    }
    for(int i = 0; i < N; i++){
        if(N == i+1) n = q.top();
        q.pop();
    }cout << n;
    return 0;
}               //메모리 부족..