#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<char, int> symbol_map = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}}; 
    
    string symbols[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" }; 
    int values[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };

    string str[2];

    cin >> str[0] >> str[1];

    int resultNum = 0;
    
    for(int j = 0; j < 2; j++) {
        for(int i = 0; i < str[j].size(); i++) {

            int nextNum = (i+1 < str[j].size() ? symbol_map[str[j][i+1]] : -1);
            
            resultNum += symbol_map[str[j][i]] * (symbol_map[str[j][i]] < nextNum ? -1 : 1);        
        }
    }
    cout << resultNum << endl;

    while(resultNum) {
        for(int i = 0; i < 13; i++) {
            
            if(resultNum >= values[i]) {
                resultNum -= values[i];
                cout << symbols[i];
                break;
            }
        }
    }
}