#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct edge {
    int to;
    edge* next = nullptr;
}* e;

struct person{
    int visit = 0;
    int time = 0;
}* p;

struct Gang {
    int head;
    int memnum;
}* gang;

void DFStravers(edge* g[],int visit[],int name,int &member_num,int total_time[],int &head,int &sum_time) {
    visit[name] = 1;
    member_num++;
    sum_time += total_time[name];
    if(total_time[name] > total_time[head]) head = name;
    for(edge* e = g[name];e!=nullptr;e=e->next) {
        if(! visit[e->to]) {
            DFStravers(g,visit,e->to,member_num,total_time,head,sum_time);
        }
    }
}

int DFS(edge* g[],int visit[],int total_time[],vector<Gang*> &v,int thresh,vector<int> store) {
    int k = 0,member_num;
    int sum_time,temp;
    int head;
    for(int i = 0; i < store.size();i++) {
        temp = store[i];
        if(! visit[temp]) {
            sum_time = member_num = 0;
            head = temp;
            DFStravers(g,visit,temp,member_num,total_time,head,sum_time);
            sum_time /= 2;
            if(member_num > 2 && sum_time > thresh) {
                gang = new Gang();
                gang -> head = head;
                gang -> memnum = member_num;
                v.push_back(gang);
                k++;
            }
        }
    }
    return k;
}

bool cmp(Gang* v1,Gang *v2) {
    return v1->head < v2->head;
}

// -------------------------------
int str_hash(char s[]) {
    return (s[0]-'A')*26*26+(s[1]-'A')*26 + s[2]-'A';
}       // 点睛之笔 !!!!
// -------------------------------

int main(int argc, char const *argv[]) {
    int n,k;
    scanf("%d%d",&n,&k);
    char c1[4],c2[4];
    int name1,name2;
    int time;
    edge* g[100000];
    int total_time[100000],visit[100000];
    string hash_back[100000];
    vector<int> store;
    for(int i=0;i<n;i++) {
        scanf("%s%s%d", c1, c2, &time);
        name1 = str_hash(c1);
        hash_back[name1] = c1;
        name2 = str_hash(c2);
        hash_back[name2] = c2;
        store.push_back(name1);
        store.push_back(name2);

        e = new edge();
        e->to = name2;
        e->next = g[name1];
        g[name1] = e;
        total_time[name1] += time;

        e = new edge();
        e->to = name1;
        e->next = g[name2];
        g[name2] = e;
        total_time[name2] += time;
    }
    vector<Gang* > v;
    int num = DFS(g,visit,total_time,v,k,store);
    printf("%d\n", num);
    if(! num) return 0;
    sort(v.begin(),v.end(),cmp);
    for(int i = 0 ;i<v.size();i++) {
        cout << hash_back[v[i]->head] << " " << v[i]->memnum << endl;
    }
    return 0;
}
