#include <iostream>
#include <string>
#include <vector>
using namespace std;

int T;
int n;
int count_;
int answer;

vector<vector<string>> v(30);

void search(string & str1, string & str2){
    count_ = 0;
    for(int i = 0; i < 30; i++){
        if(!v[i].size()){
            v[i].push_back(str2);
            v[i].push_back(str1);
            break;
        }
        else if(v[i][0] == str2){
            v[i].push_back(str1);
            break;
        }
    }
}
void input(){
    cin >> n;
    int index;
    for(int j = 0; j < n; j++){
        string str1, str2;
        cin >> str1 >> str2;
        search(str1, str2);
    }
}
void getSubPermutation(){
    
}
int main(){
    cin >> T;
    for(int i = 0; i < T; i++){
        // vecotr v를 완전히 초기화
        vector<vector<string>>(30).swap(v);
        input();
     
        for(int i = 0; i < 30; i++){
            if(v[i].size()){
                for(int j = 0; j < v[i].size(); j++){
                    cout << "v[" << i << "][" << j << "] :" << v[i][j] << ' ';
                }cout << endl;
            }
        }
    }   
}