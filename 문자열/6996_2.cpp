#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int T;
    cin >> T;

    char str1[101] = {0};
    char str2[101] = {0};
    char tp1[101] = {0};
    char tp2[101] = {0};
    for(int i = 0; i < T; i++){ // TestCase
        cin >> str1 >> str2;
        int size1 = 0;
        int size2 = 0;
        for(; str1[size1] != 0; size1++){   // str1 == tp1
            tp1[size1] = str1[size1];
        }tp1[size1] = 0;
        for(; str2[size2] != 0; size2++){   // str2 == tp2
            tp2[size2] = str2[size2];
        }tp2[size2] = 0;
        if(size1 != size2){
            cout << tp1 << " & " << tp2 << " are NOT anagrams." << endl;
        }else{
            sort(str1, str1+size1); // Sort string
            sort(str2, str2+size2);
            int j;
            for(j = 0; j < size1-1; j++){ // Compare string
                if(str1[j] != str2[j]){
                    j = -1;
                    break;
                }
            }
            if(j == -1){
                cout << tp1 << " & " << tp2 << " are NOT anagrams." << endl;
            }
            else{
                cout << tp1 << " & " << tp2 << " are anagrams." << endl;
            }
        }
    }
}