/* 
    1. 소수 판별 - 에라토스테네스의 체
    2. 펠린드롬 수 찾기
    3. 출력
*/
#include <iostream>
#include <string>
using namespace std;

#define range 1004000
bool prime[range];
void eratos(){
    prime[1] = false;
    for(int i = 2; i <= range; i++) prime[i] = true;
    for(int i = 2; i * i <= range; i++){
        if(prime[i]){
            for(int j = i * i; j <= range; j+=i){
                prime[j] = false;
            }
        }
    }
}
bool palindrome(int n){
    string str = to_string(n);
    int size = str.size();
    for(int i = 0; i < size / 2; i++){
        if(str[i] != str[size-i-1])
            return false;
    }return true;
}
int main(){
    int num, length;
    string arr;
    cin >> num;
    eratos();
    for(int i = num; i <= range; i++){
        if(prime[i] && palindrome(i)){
            cout << i;
            break;
        }
    }   
}