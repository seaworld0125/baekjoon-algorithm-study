#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, k;
int A, S, M, D;
int MAX = 0, MIN = 0;
vector<int> Arr;
vector<int> sub_v;
vector<char> calc_v;

/*
    for(int i = 0; i < sub_v.size(); i++){
        cout << sub_v[i] << " ";
    }cout << '\n';

    cout << "tmp :" << tmp << '\n';

    cout << "num :" << num << endl;
    cout << "c :" << c << endl;
*/

void makeVector(){
    // 보조수열을 만든다.
    int i;
    int total = A+S+M+D;
    for(i = 0; i < total-(N-1); i++)
    {
        sub_v.push_back(0);
    }
    for(i = 1; i < N; i++)
    {
        sub_v.push_back(i);
    }   
    // calc_v 생성
    for(i = 0; i < A; i++){
        calc_v.push_back('+');
    }
    for(i = 0; i < S; i++){
        calc_v.push_back('-');
    }
    for(i = 0; i < M; i++){
        calc_v.push_back('*');
    }
    for(i = 0; i < D; i++){
        calc_v.push_back('/');
    }
}
void calc(int & tmp, int index){
    char c = calc_v[index];
    int num = Arr[k++];

    if(c == '+') tmp += num;
    else if(c == '-') tmp -= num;
    else if(c == '/') tmp /= num;
    else if(c == '*') tmp *= num;
}
void checkPermutation(){
    // 모든 경우의 수를 확인한다.
    // 시간이 너무 오래걸림..
    int tmp;
    do{
        k = 0;
        tmp = Arr[k++];
        
        for(int i = 0, j = 1; j < N; i++)
        {
            if(i >= sub_v.size()) i = 0;

            if(j == sub_v[i])
            {
                calc(tmp, i);
                j++;
                i = 0;  
            }
        }
        MIN = min(MIN, tmp);
        MAX = max(MAX, tmp);

    }while(next_permutation(sub_v.begin(), sub_v.end()));
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    int num;
    for(int i = 0; i < N; i++)
    {
        cin >> num;
        Arr.push_back(num);
    }

    cin >> A >> S >> M >> D;

    makeVector();
    checkPermutation();

    cout << MAX << '\n' << MIN;
}