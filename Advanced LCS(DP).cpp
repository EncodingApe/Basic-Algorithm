#include <iostream>
#include <map>
#include <math.h>

using namespace std;

// Dynamic Programming ------- LCS Longest Common String 变形
// 因为两个给定的串中有一个是模式串 即可以重复使用该串的末尾元素
// 所以公式与普通的递推公式不同
/*
                len[i,j-1]+1    if pattern[i] == string[j]
    len[i,j] =
                max(len[i,j-1],max[i-1,j])      if pattern[i] != string[j]
*/
/*
    第一种情况是 匹配串和模式串的最后一个元素相同 又因为模式串的末尾元素可以重复使用 所以答案为用相同的模式串和剩余的匹配串进行匹配后得到的最大长度再加一
    第二种情况是 匹配串和模式串的最后一个元素不同 则存在两种情况
        1) 模式串的最后一个元素匹配不了了 故舍弃匹配串的最后一个元素
        2) 匹配串的最后一个元素失配 可以用相同的模式串匹配剩下的匹配串
        而最大长度应该是这两种情况的较大者 :)
*/


int solution(int row,int col,int matrix[][10001],int pattern[],int stripe[]) {
    for(int i=1;i<=row;i++) {
        for(int j=1;j<=col;j++) {
            if(pattern[i] == stripe[j]) matrix[i][j] = matrix[i][j-1]+1;
            else matrix[i][j] = max(matrix[i-1][j],matrix[i][j-1]);
        }
    }
    return matrix[row][col];
}

int main(int argc, char const *argv[]) {
    int n,m,l;
    scanf("%d",&n);
    scanf("%d",&m);
    int* pattern = (int*)malloc(sizeof(int) * (m+1));
    int matrix[201][10001] = {0};
    for(int i=1;i<=m;i++) {
        scanf("%d",&pattern[i]);
    }
    scanf("%d",&l);
    int* stripe = (int*)malloc(sizeof(int) * (l+1));
    for(int i=1;i<=l;i++) {
        scanf("%d",&stripe[i]);
    }
    printf("%d\n", solution(m,l,matrix,pattern,stripe));
    return 0;
}
