#include <iostream>
#include <vector>
using namespace std;

#define MAX_value 1e9
#define MIN_value -1e9

int N;
int MAX = MIN_value;
int MIN = MAX_value;
vector<int> Arr; 

void recursive(int A, int S, int M, int D, int tmp=Arr[0], int index=0){
    if(index == N-1)
    {
        if(MAX < tmp) MAX = tmp;
        if(MIN > tmp) MIN = tmp;
        return;
    }
    index += 1;

    if(A > 0) recursive(A-1, S, M, D, tmp+Arr[index], index);
    if(S > 0) recursive(A, S-1, M, D, tmp-Arr[index], index);
    if(M > 0) recursive(A, S, M-1, D, tmp*Arr[index], index);
    if(D > 0) recursive(A, S, M, D-1, tmp/Arr[index], index);
}

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    int num; 
    int A, S, M, D;

    for(int i = 0; i < N; i++)
    {
        cin >> num;
        Arr.push_back(num);
    }
    cin >> A >> S >> M >> D;
    recursive(A, S, M, D);
    cout << MAX << '\n' << MIN;
}