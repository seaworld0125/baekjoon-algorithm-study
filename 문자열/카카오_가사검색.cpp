#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int charCount(string str){
    int i = 0;
    for(char c : str){
        if(c == '?') continue;
        i++;
    }
    return i;
}

int check(vector<bool> & dp, vector<string> & words, string str){
    int count = 0;
    for(int i = 0; i < words.size(); i++){
        bool same = true;
        if(str.size() != words[i].size()) continue;
        for(int j = 0; j < str.size(); j++){
            if(str[j] == words[i][j] || str[j] == '?') continue;
            else same = false;
        }
        if(same){
            dp[i] == true;
            count++;
        }
    }
    return count;
}

struct compare
{
    bool operator()(pair<string, int> a, pair<string, int> b){
        int i = 0, j = 0;
        int asize = a.first.size();
        int bsize = b.first.size();
        while (i < asize && j < bsize) {
            if(a.first[i] == '?') break;
            if(b.first[j] == '?') break;
            i++; j++;
        }
        if(i > j) return true;
        else return false;
    }
};

void selectQuery(vector<int> & answer, vector<string> & queries, priority_queue<pair<string, int>, vector<pair<string, int>>, compare> & pq) {
    string std_;
    bool src = false;
    for (int i = 0; i < queries.size(); i++) {
        if(answer[i] < 0 && !src){
            std_ = queries[i];
            src = true;
            pq.push({std_, i});
            answer[i] = 1;
        }
        else if(answer[i] < 0 && src){
            if(queries[i][0] == std_[0] && queries[i].size() == std_.size()){
                pq.push({queries[i], i});
                answer[i] = 1;
            }
        }
    }
    // return src;
}

vector<int> solution(vector<string> words, vector<string> queries) {
    vector<int> answer(queries.size(), -1);
    
    for (int i = 0; i < queries.size(); i++) {
        if(answer[i] < 0){
            vector<bool> dp(words.size(), false);
            vector<int> index_rc;
            priority_queue<pair<string, int>, vector<pair<string, int>>, compare> pq;
            selectQuery(answer, queries, pq);
            int size = pq.size();
            string prevStr = "";
            for(int j = 0; j < size; j++) {
                string cstr = pq.top().first;
                int index = pq.top().second;
                int count = check(dp, words, cstr);
                int prevCount = 0;
                
                // cout << "cstr :" << cstr << ", " << charCount(cstr) << endl;
                // cout << "prevStr :" << prevStr << ", " << charCount(prevStr) << endl;
                if(prevStr != "" && charCount(cstr) < charCount(prevStr)) {
                    for(int k = 0; k < index_rc.size(); k++) {
                        prevCount += answer[index_rc[k]];
                    }
                }
                answer[index] = count + prevCount;
                index_rc.emplace_back(index);
                pq.pop();
            }
        }
    }
    return answer;
}

int main(){
    vector<string> words = {"frodo", "front", "frost", "frozen", "frame", "kakao"};
    vector<string> queries = {"fro??", "????o", "fr???", "fro???", "pro?"};
    auto answer = solution(words, queries);
    for(int i : answer){
        cout << i << ' ';
    }
}