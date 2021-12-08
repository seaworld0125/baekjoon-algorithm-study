#include <iostream>
#include <string>
using namespace std;

string reverse(string & str) {
    string tmp;
    for(int i = 0; i < str.length(); i++)
        tmp += str[str.length() - i - 1];
    return tmp;
}
int main() {
    string S, T;
    cin >> S >> T;

    bool canMake = false;
    while(S.length() <= T.length()) {
        if(S == T) canMake = true;

        char tmp = T[T.length()-1];
        T.pop_back();
        if(tmp == 'B') 
            T = reverse(T);
    }
    cout << canMake;
}