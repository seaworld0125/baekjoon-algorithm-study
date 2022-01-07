#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int N, P, note, fret, ans = 0;

    cin >> N >> P;

    vector<stack<int>> vs(7);

    for(int i = 0; i < N; i++) {
        cin >> note >> fret;

        while(!vs[note].empty() && vs[note].top() > fret) {
            vs[note].pop();
            ans++;   
        }

        if(vs[note].empty() || vs[note].top() < fret) {
            vs[note].push(fret);
            ans++;
        }
    }
    cout << ans;
}