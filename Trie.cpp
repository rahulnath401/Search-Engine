#include <bits/stdc++.h>
using namespace std;
const int MX_SIZE = 10;
const int ALPHABET_SIZE = 26;
struct TrieNode{
    bool end_of_string;
    TrieNode *pointer[ALPHABET_SIZE];
    TrieNode(){
        end_of_string = 0;
        for (int i=0;i<ALPHABET_SIZE;i++) pointer[i] = NULL;
    }
    void insert(string str){
        TrieNode *cur = this;
        int n = str.length();
        for(int i=0;i<n;i++){
            int nx = str[i]-'A';
            if(cur->pointer[nx]==NULL)cur->pointer[nx] = new TrieNode();
            cur = cur->pointer[nx];
            if(i==n-1)cur->end_of_string = true;
        }
    }
    bool search(string str){
        TrieNode *cur = this;
        int n = str.length();
        for(int i=0;i<n;i++){
            int nx = str[i]-'A';
            if(cur->pointer[nx]==NULL)return false;
            cur = cur->pointer[nx];
        }
        return cur->end_of_string;
    }
    vector<string> bfs(string str){
        vector<string>ret;
        queue<pair<TrieNode*, string> >q;
        TrieNode *cur = this;
        q.push({cur, str});
        while(!q.empty()){
            TrieNode *cur = q.front().first;
            string str = q.front().second;
            q.pop();
            if(cur->end_of_string==true){
                ret.push_back(str);
            }
            if(ret.size()==MX_SIZE)break;
            for(int i=0;i<ALPHABET_SIZE;i++){
                if(cur->pointer[i]!=NULL){
                    q.push({cur->pointer[i], str+char(i+'A')});
                }
            }
        }
        return ret;
    }
    vector<string> AutoComplete(string str){
        TrieNode *cur = this;
        vector<string>ret;
        int n = str.length();
        for(int i=0;i<n;i++){
            int nx = str[i]-'A';
            if(cur->pointer[nx]==NULL)return ret;
            cur = cur->pointer[nx];
        }
        return cur->bfs(str);
    }
}*root = new TrieNode();
int main(){
    while(1){
        int op;
        string str;
        cin>>op;
        if(op==0)break;
        if(op==1){  // insert operation
            cin>>str;
            root->insert(str);
        }
        else{       // AutoComplete operation
            cin>>str;
            vector<string>v = root->AutoComplete(str);
            cout<<v.size()<<endl;
            for(auto s:v)cout<<s<<endl;
            cout<<endl;
        }
    }
}
