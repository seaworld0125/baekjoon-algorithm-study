#include <iostream>
#include <queue>
using namespace std;

int main(){
    priority_queue<int, vector<int>, greater<int> > pq1;
    priority_queue<int> pq2;
    for(int i = 0; i < 6; i++){
        int num; 
        cin >> num;
        pq1.push(num);
        pq2.push(num); 
    }
    for(int i = 0; i < 6; i++){
        cout << pq1.top();
        pq1.pop();
    }cout << endl;
    for(int i = 0; i < 6; i++){
        cout << pq2.top();
        pq2.pop();
    }
}