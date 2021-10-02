#include <iostream>
#include <string>
using namespace std;

string a, b;
int answer = 0;
bool check(int idx) {
    for(int i = 0; i < b.size(); i++)
        if(a[idx+i] != b[i]) return false;
    answer++;
    return true;
}
int main() {
    getline(cin, a); getline(cin, b);
    for(int i = 0; i < a.size();) {
        if(check(i)) i += b.size();
        else i++;
    }cout << answer;
}