#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

void change_base(int n, int b, string & str) {
    // int r;
    // r = n % b;
    // n = n / b;
    
    // if (n > 0) change_base(n, b, str);
    // if (r < 10) {
    //     str.push_back(char(r + 48));       // 10진수 이하
    //     return ;
    // }

    int mul, tbase = 1;
    while (tbase <= n) tbase *= b;
 
    do {
        tbase /= b;
        mul = n / tbase;
 
        if (mul < 10) str.push_back(char(mul + 48));    // 10진수 이하 
        n -= mul * tbase;
    } while (tbase >= b);
}

bool isPrime(int num) {
    if(num < 2) return false;
    for(int i = 2; i < num; i++){
        if(num % i == 0) return false;
    }
    return true;
}

int solution(int n, int k) {
    string numStr = "";
    change_base(n, k, numStr);

    // 중복 0 전처리
    char c = '0';
    numStr.erase( unique( begin( numStr ), end( numStr ), [=]( const auto &c1, const auto &c2 ) { return c1 == c && c1 == c2; } ), end( numStr ) );

    istringstream ss(numStr);
    string tmp = "";
    vector<int> v(0);
    // 0을 기준으로 분리
    while (getline(ss, tmp, '0')) {
        if(tmp.size() > 0 && tmp != "0")
            v.push_back(stoi(tmp));
    }

    // 합산
    int answer = 0;
    for(int i = 0; i < v.size(); i++) {
        if(isPrime(v[i])){
            answer++;
        }
    }
    return answer;
}

int main()
{
    cout << "answer :" << solution(437674, 3) << endl << endl;
    cout << "answer :" << solution(110011, 10) << endl << endl;
}