#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N, P, n, p, A=0;
    cin >> N >> P;
    vector<vector<int>> arr(10, vector<int>(0, 0));
    for(int i = 0; i < N; i++){
        cin >> n >> p;
        while(arr[n].back() > p && !arr[n].empty()){
            arr[n].pop_back(); A++;
        }
        if(arr[n].back() != p){
            arr[n].push_back(p); A++;  
        }
    }
    cout << A;
    return 0;
}