#include <iostream>
#include <string>
using namespace std;
#define endl '\n'
#define INF 1e9

string strA = "";
string strB = "";

int check()
{
    int answer = INF;
    for(int i = 0; i <= strB.size()-strA.size(); i++)
    {
        int count = 0; 
        for(int j = 0; j < strA.size(); j++)
        {
            if(strA[j] != strB[j+i]) count++;
        }
        if(answer > count) answer = count;
    }
    return answer;
}

int main()
{
    cin >> strA >> strB;
    cout << check();
}