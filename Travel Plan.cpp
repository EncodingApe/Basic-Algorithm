#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

struct node {
    vector<int> path;
    int name;
    int dis;
    int cost;
    node* next;
};

struct cmp {
    bool operator()(const node* e1,const node* e2) {
        return e1->dis > e2->dis;
    }
};

void dijkstra(node* g[],int start,int end,int &dis,int &cost) {
    cost = 100000;
    vector<int> path;
    priority_queue<node*,vector<node*>,cmp> q;
    int new_dis;
    int d[1000];
    for(int i=0;i<1000;i++) d[i] = 10000;
    node* e,*top;
    e = new node();
    e->name = start;
    e->dis = 0;
    e->cost = 0;
    q.push(e);
    d[start] = 0;
    while(! q.empty()) {
        top = q.top();
        q.pop();
        if(top->dis > d[top->name]) continue;
        for(node* temp = g[top->name];temp!=nullptr;temp = temp->next) {
            new_dis = temp->dis + d[top->name];
            if(temp->name == end && new_dis == d[temp->name]) {
                if(cost > temp->cost + top->cost) {
                    cost = temp->cost + top->cost;
                    path = top->path;
                    path.push_back(top->name);
                }
            }
            else if(new_dis < d[temp->name]) {
                d[temp->name] = new_dis;
                e = new node();
                e->path.assign(top->path.begin(),top->path.end());
                e->path.push_back(top->name);
                e->dis = new_dis;
                e->name = temp->name;
                e->cost = temp->cost + top->cost;
                if(temp->name == end) {
                    cost = e->cost;
                    path = e->path;
                }
                q.push(e);
            }
        }
    }
    path.push_back(end);
    for(int i=0;i<path.size();i++) cout << path[i] << " ";
    cout << d[end] << " " << cost;
}

int main(int argc, char const *argv[]) {
    int n,m,s,d;
    scanf("%d%d%d%d", &n,&m,&s,&d);
    int from,name,dis,cost;
    node* e;
    node** graph = (node**)malloc(n * sizeof(node*));
    for(int i=0;i<n;i++) graph[i] = nullptr;
    for(int i=0;i<m;i++) {
        e = new node();
        scanf("%d%d%d%d", &from,&name,&dis,&cost);
        e->name = name;
        e->dis = dis;
        e->cost = cost;
        e->next = graph[from];
        graph[from] = e;
        e = new node();
        e->name = from;
        e->dis = dis;
        e->cost = cost;
        e->next = graph[name];
        graph[name] = e;
    }
    dijkstra(graph,s,d,dis,cost);
    return 0;
}
