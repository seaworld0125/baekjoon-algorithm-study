#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//sort 알고리즘 사용
class Student{
public:
    string name;
    int langScore;
    int engScore;
    int mathScore;
    bool operator<(Student s) const{  //ㅇㅅㅈ오버로딩
        if(this->langScore > s.langScore){
            return true;
        }else if(this->langScore == s.langScore){
            if(this->engScore < s.engScore){
                return true;
            }else if(this->engScore == s.engScore){
                if(this->mathScore > s.mathScore){
                    return true;
                }else if(this->mathScore == s.mathScore){
                    return this->name < s.name;
                }
            }
        }return false;
    }
};
int main(){
    int T;
    cin >> T;
    vector<Student> v(T);
    for(int i = 0; i < T; i++){
        cin >> v[i].name >> v[i].langScore >> v[i].engScore >> v[i].mathScore;
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < T; i++){
        cout << v[i].name << "\n";
    }
}

