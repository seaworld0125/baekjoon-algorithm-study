#include <iostream>
#include <algorithm>
#include <string>
#include <map>

using namespace std;
#define MAX_CHAR_LENGTH 256

void makeBadCharacterTable(string & target, int * table) 
{
    int length = target.length(), i;

    for(i = 0; i < MAX_CHAR_LENGTH; i++)
        table[i] = -1;
    
    for(i = 0; i < length; i++)
        table[target[i]] = i;
}

void search(string & base, string & target) 
{
    int badCharacterTable[MAX_CHAR_LENGTH];

    makeBadCharacterTable(target, badCharacterTable);
    
    int len_base = base.length();
    int len_target = target.length();

    int s, j;

    while(s + len_target <= len_base) 
    {
        j = len_target - 1;

        while(j >= 0 && (target[j] == base[j + s]))
            j--;

        if(j >= 0) // j가 감소하다가 멈췄다는 것은 비교 문자열이 서로 다르다는 것
        {
            s += max(1, j - badCharacterTable[base[s + j]]);
        }
        else // j가 음수라는 것은 두 문자열이 같다는 것
        {
            cout << "pattern occurs at index = " << s << endl;
            s += (s + len_target < len_base) ? len_target - badCharacterTable[base[s + len_target]] : 1;
        }
    }
}

int main() 
{
    string base, target;
    cin >> base >> target;

    search(base, target);
}