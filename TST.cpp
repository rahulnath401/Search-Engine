#include <bits/stdc++.h>
using namespace std;
const int MX_SIZE = 10;
struct TSTNode{
    bool end_of_string;
    TSTNode *left, *right, *middle;
    char value;
    TSTNode(){
        end_of_string = 0;
        left = NULL;
        right = NULL;
        middle = NULL;
    }
    TSTNode *insert(TSTNode *head, string str, int idx){
        if(idx==str.length()){
            if(head==NULL)head = new TSTNode();
            head->end_of_string = true;
            return head;
        }
        if(head==NULL){
            head = new TSTNode();
            head->value = str[idx];
        }
        if(str[idx] == head->value)head->middle = insert(head->middle, str, idx+1);
        else if(str[idx] > head->value)head->right = insert(head->right, str, idx);
        else head->left = insert(head->left, str, idx);
        return head;
    }
    bool search(string str){
        TSTNode *root = this;
        int n = str.length();
        int i = 0;
        while(i<n){
            if(root==NULL)return 0;
            if(root->value == str[i]){
                root = root->middle;
                i++;
                continue;
            }
            if(root->value < str[i])root = root->right;
            else root = root->left;
        }
        return root->end_of_string;
    }


    vector<string> bfs(string str){
        vector<string>ret;
        queue<pair<TSTNode*, pair<string, int> > >q;
        TSTNode *cur = this;
        q.push({cur, {str, 1}});
        while(!q.empty()){
            TSTNode *cur = q.front().first;
            string str = q.front().second.first;
            bool add = q.front().second.second;
            q.pop();
            if(cur->end_of_string==true && add==true){
                ret.push_back(str);
            }
            if(ret.size()==MX_SIZE)break;
            if(cur->left!=NULL)q.push({cur->left, {str, 0}});
            if(cur->middle!=NULL)q.push({cur->middle, {str + cur->value, 1}});
            if(cur->right!=NULL)q.push({cur->right, {str, 0}});
        }
        return ret;
    }
    vector<string> AutoComplete(string str){
        vector<string>ret;
        TSTNode *root = this;
        int n = str.length();
        int i = 0;
        while(i<n){
            if(root==NULL)return ret;
            if(root->value == str[i]){
                root = root->middle;
                i++;
                continue;
            }
            if(root->value < str[i])root = root->right;
            else root = root->left;
        }
        return root->bfs(str);
    }
}*root;
int main(){
    while(1){
        int op;
        string str;
        cin>>op;
        if(op==0)break;
        if(op==1){  // insert operation
            cin>>str;
            root = root->insert(root, str, 0);
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
