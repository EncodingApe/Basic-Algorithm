#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    string s1,s2,temp;
    char max_ch = '0';
    long long int tag,radix,lowerbound,upperbound,product = 1;
    long long int sum1 = 0,sum2;
    cin >> s1 >> s2 >> tag >> radix;
    if(tag == 2) {temp = s1; s1 = s2; s2 = temp;}
    for(int i=s1.length()-1;i>=0;i--) {
        sum1 += (s1[i] <= '9' && '0' <= s1[i]) ? (s1[i]-'0') * product : (s1[i] - 87) * product;
        product *= radix;
    }
    for(int i=0;i<s2.length();i++) if(s2[i] > max_ch) max_ch = s2[i];
    lowerbound = ('a' <= max_ch && max_ch <= 'z') ? max_ch - 87 : max_ch - '0';
    lowerbound += 1;
    upperbound = sum1 + 1;
    while(lowerbound<=upperbound) {
        tag = (lowerbound+upperbound) / 2;
        sum2 = 0;product = 1;
        for(int i=s2.length()-1;i>=0;i--) {
            sum2 += (s2[i] <= '9' && '0' <= s2[i]) ? (s2[i]-'0') * product : (s2[i] - 87) * product;
            product *= tag;
        }
        if(sum1 == sum2) break;
        else if(sum1 < sum2 || sum2 < 0) upperbound = tag - 1;
        else if(sum1 > sum2) lowerbound = tag + 1;
    }
    if(sum2 == sum1) cout << tag;
    else cout << "Impossible";
    return 0;
}
