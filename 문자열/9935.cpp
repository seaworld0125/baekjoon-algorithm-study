#include <iostream>
#include <string>

using namespace std;

int main() {
    string org, bomb;
    cin >> org >> bomb;

    int length_org = org.length();
    int length_bomb = bomb.length();

    string ans;
    for(int i = 0; i < length_org; i++) {
        ans += org[i];

        if(org[i] == bomb[length_bomb - 1]) {
            bool isBomb = true;
            
            for(int j = 0; j < length_bomb; j++) 
                if(ans[ans.length() - 1 - j] != bomb[length_bomb - 1 - j]) 
                    isBomb = false;
        
            if(isBomb)
                for(int j = 0; j < length_bomb; j++) 
                    ans.pop_back();
        }
    }
    cout << (ans.length() ? ans : "FRULA");
}