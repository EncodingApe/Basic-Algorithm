#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <math.h>
#include <cstring>
#include <unordered_map>

using namespace std;

int main(int argc, char const *argv[]) {
    string str;
    cin >> str;

    long long int count=0;
    int countP[100000], countT[100000], len = str.length();
    for(int i=0; i<len-1; i++) {
        if(str[i] == 'P') count++;
        countP[i+1] = count;
    }
    count=0;
    for(int i=len-1; i>0; i--) {
        if(str[i] == 'T') count++;
        countT[i-1] = count;
    }
    count=0;
    for(int i=0; i<len; i++) {
        if(str[i] == 'A') {
            count += countT[i]*countP[i];
            count = count % 1000000007;
        }
    }

    cout << count << endl;
    return 0;
}
