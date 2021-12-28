#include <iostream>
#include <queue>
using namespace std;

int main() {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    priority_queue<int> pq;
    int n, a, present;
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> a;
        if(a) {
            for(int j = 0; j < a; j++) {
                cin >> present;
                pq.push(present);
            }
        }
        else {
            if(pq.size()) {
                cout << pq.top() << '\n';
                pq.pop();
            }
            else
                cout << -1 << '\n';
        }
            
    }
}