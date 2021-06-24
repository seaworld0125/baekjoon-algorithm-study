#include <iostream>
using namespace std;

int main(){
    int T;
    cin >> T;
    int j;
    char str1[101];
    char str2[101];
    for(int i = 0; i < T; i++){ // TestCase
        int carr[26] = {0};
        cin >> str1 >> str2;
        for(j = 0; str1[j] != 0; j++){
            carr[str1[j]-'a'] += 1;
        }
        for(j = 0; str2[j] != 0; j++){
            carr[str2[j]-'a'] -= 1;
        }
        for(j = 0; j < 26; j++){
            if(carr[j] != 0) break;
        }
        if(j != 26) cout << str1 << " & " << str2 << " are NOT anagrams.\n";
        else cout << str1 << " & " << str2 << " are anagrams.\n";
    } 
    return 0;
}