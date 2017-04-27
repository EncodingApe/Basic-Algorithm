#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> v(n,0);     // 用来判断列已存
        vector<int> v1(2*n-1,0);    // 用来判断主对角线已存
        vector<int> v2(2*n-1,0);    // 用来判断次对角线已存
        string s(n,'.');
        vector<string> temp(n,s);
        solveNQueens(ans,temp.begin(),temp,n,1,0,v,v1,v2);
        return ans;
    }
private:
    void solveNQueens(vector<vector<string>>& ans,vector<string>::iterator beg,vector<string> &temp,int n,int line,int number,vector<int> v,vector<int> v1,vector<int> v2) {
        if(number == n) {
            ans.push_back(temp);
        }
        if(line > n) {
            return;
        }
        int flag;
        flag = n;
        for(int count=0;count<n && flag ;count++) {
            if(v[count] || v1[count-line+n] || v2[count+line-1]) {flag--;continue;}
            (*beg)[count] = 'Q';
            number++;
            v[count] = 1;
            v1[count-line+n] = 1;
            v2[count+line-1] = 1;
            solveNQueens(ans,beg+1,temp,n,line+1,number,v,v1,v2);
            v[count] = 0;
            v1[count-line+n] = 0;
            v2[count+line-1] = 0;
            (*beg)[count] = '.';
            number--;
        }
    }
};

int main(int argc, char const *argv[]) {
    Solution s;
    vector<vector<string>> ans;
    ans = s.solveNQueens(5);
    return 0;
}
