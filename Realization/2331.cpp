#include <iostream>
#include <vector>
using namespace std;

int A, P;
vector<int> v;

int makeNum(int num){
    // 1. 자릿수 분리
    // 2. 각 자릿수에 거듭제곱을 취함
    // 3. 합한다.
    int a = num > 999 ? num/1000 : 0;
    int b = num > 99 ? (num%1000)/100 : 0;
    int c = num > 9 ? (num%100)/10 : 0;
    int d = num%10;

    int a2 = 1, b2 = 1, c2 = 1, d2 = 1;

    for(int i = 0; i < P; i++)
    {
        a2 *= a;
        b2 *= b;
        c2 *= c;
        d2 *= d;
    }
    return a2+b2+c2+d2;
}
int checkArr(int num){
    // 인자로 받은 수가 배열 내에 있는지 확인
    // 있다면 index 반환
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] == num)
        {
            return i;
        }
    }
    return -1;
}
int makeArr(){
    // 수열을 만들어나감
    int num;//
    int index;
    while(1)
    {   
        num = makeNum(v.back());
        index = checkArr(num);
        if(index != -1)
        {
            break; 
        }
        else
        {   
            v.push_back(num);
        }
    }
    return index;
}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> A >> P;
    v.push_back(A);
    
    cout << makeArr();
    return 0;
}