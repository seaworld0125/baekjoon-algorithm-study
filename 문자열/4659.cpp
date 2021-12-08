#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<pair<char, int>> templateVowel(5);

bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}
int vowelIndex(char c) {
    for(int i = 0; i < 5; i++)
        if(templateVowel[i].first == c)
            return i;
}

int main() {
    templateVowel[0] = {'a', 0};
    templateVowel[1] = {'e', 0};
    templateVowel[2] = {'i', 0};
    templateVowel[3] = {'o', 0};
    templateVowel[4] = {'u', 0};

    string str;

    while(cin >> str) {
        if(str == "end") break;

        vector<pair<char, int>> vowel;
        vowel.assign(templateVowel.begin(), templateVowel.end());

        int i = 0, vowelCount = 0, consonantCount = 0;
        char prevChar = ' ';
        bool acceptable = false, hasVowel = false;

        for(; i < str.size(); i++) {
            if(prevChar != str[i] || prevChar == 'e' || prevChar == 'o')
                prevChar = str[i];
            else 
                break;

            if(isVowel(prevChar)) {
                consonantCount = 0;
                vowelCount++;
                vowel[vowelIndex(prevChar)].second++;
                hasVowel = true;
            }
            else {
                vowelCount = 0;
                consonantCount++;
            }

            if(vowelCount == 3 || consonantCount == 3)
                break;
        }
        if(i == str.size() && hasVowel)
            acceptable = true;

        if(acceptable)
            cout << "<" << str << "> is acceptable.\n";
        else
            cout << "<" << str << "> is not acceptable.\n";
    }
}