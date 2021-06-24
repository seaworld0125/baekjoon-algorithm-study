#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main(){
    int N, n;
    cin >> N;
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 0; i < N; i++){
        cin >> n;
        q.push(n);  
    } 
    for(int i = 0; i < N-1; i++){
        for(int j = 0; j < N; j++){
            cin >> n;
            q.push(n);  
        } 
        for(int j = 0; j < N; j++) q.pop();
    }
    cout << q.top();
    return 0;
}