#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int arr[20][20], N;
    cin >> N;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            cin >> arr[i][j];
    
    vector<int> v(N);

    for(int i = 0; i < N; i++) {
        if(i >= N/2) v[i] = 1;
        else v[i] = 0;
    }

    int ans = 1e9;
    do
    {
        int link = 0, start = 0;
        for(int i = 0; i < N; i++) {
            if(v[i]) // link
                for(int j = i + 1; j < N; j++) {
                    if(v[j]) {
                        link += arr[i][j];
                        link += arr[j][i];
                    }
                }
            else    // start
                for(int j = i + 1; j < N; j++) {
                    if(!v[j]) {
                        start += arr[i][j];
                        start += arr[j][i];
                    }
                }
        }
        ans = min(abs(link - start), ans);
    } while (next_permutation(v.begin(), v.end()));
    
    cout << ans;
}