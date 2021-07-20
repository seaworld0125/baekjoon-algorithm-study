#include <iostream>
#include <stack>
#include <string>
#define endl '\n'
using namespace std;

string str;
char c;
int T = 1;
bool cnt = false;

int main(){ios_base::sync_with_stdio(false); cin.tie(NULL);
    while(!cnt){       
        stack<char> s; 
        int answer = 0;
                       
        cin >> str;    
        for(int i = 0; i < str.size(); i++)
        {
            c = str[i];
            if(c == '{')
            {          
                s.push(c);
            }          
            else if(c == '}')
            {          
                if(s.empty()){
                    s.push('{');
                    answer++;
                }       
                else{   
                    s.pop();
                }      
            }          
            else{      
                cnt = true;
            }          
        }              
        if(cnt) continue;
                       
        answer += s.size()/2;
                        
        cout << T++ << ". " << answer << endl;
    }
    return 0;
}