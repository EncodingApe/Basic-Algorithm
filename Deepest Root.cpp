#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <deque>

using namespace std;

/*
    核心思想就是对一棵树求其直径（即最长路径）
    具体方法:
        1）选择任意一个点 u ，对其进行BFS(DFS)，找到距离该起始点最远的一个点即作为直径的一个端点 d1。
        2）再又第一个选中的端点，进行BFS(DFS)，找到其他的最远的点，即为直径另一个端点 d2。
    证明:
        1）假设 u 在直径 (d1,d2) 上，假设 t 才是 u 进行搜索得到的最远的点，而非 d1，则易证 distance(d1,u) < distance(t,u)，从而 (t,d2) 应该才是直径，已知不符。
        2）假设 u 不在直径 (d1,d2) 上，假设 u 搜索得到的最远的点是 T 而非 d1。 同时树中的任两点可达，则 u 可以通过 X 到达 d1。但易知 distance(d1,X)+distance(u,X) < distance(u,T) 故 distance(u,T) + distance(u,X) + distance(X,d2) > distance(d1,X) + distance(X,d2) 所以直径应该是(T,u,X,d2) 而不是 (d1,X,d2) 与已知不符合。
    故在 1）和 2）的条件下，由 u 进行 BFS(DFS)得到的一定是直径的一端 d1。
    因此 可通过两次 BFS 求得一棵数的直径。
*/

struct node {
    int name;
    node* next;
};

void BFStravers(node* g[],int visited[],int visit,vector<int> &roots,int type) {
    pair<int,int> temp;
    int layer = -1;
    vector<int> layer_node;
    deque<pair<int,int> > queue;
    queue.push_back(make_pair(visit,0));
    while(! queue.empty()) {
        temp = queue.front();
        visited[temp.first] = 1;
        if(temp.second > layer) {
            vector<int>().swap(layer_node);
            layer_node.push_back(temp.first);
            layer = temp.second;
        }
        else layer_node.push_back(temp.first);
        queue.pop_front();
        for(node* n = g[temp.first];n!=nullptr;n=n->next) {
            if(! visited[n->name])
                queue.push_back(make_pair(n->name,temp.second+1));
        }
    }
    if(!type) roots.push_back(temp.first);
    if(type) roots.insert(roots.end(),layer_node.begin(),layer_node.end());
}

int BFS(node* g[],int visited[],vector<int> &roots,int n) {
    int k=0;
    for(int i=1;i<=n;i++) {
        if(! visited[i]) {
            BFStravers(g,visited,i,roots,0);
            k++;
        }
    }
    return k;
}
int main(int argc, char const *argv[]) {
    int n,from,to,k;
    node* temp;
    scanf("%d", &n);
    if(n==1) {
        cout << "1" << endl;
        return 0;
    }
    vector<int> roots;
    node** graph = (node**)malloc(sizeof(node*) * (n+1));
    int visited[20000];
    memset(visited,0,sizeof(visited));
    for(int i=1;i<=n;i++) graph[i] = nullptr;
    for(int i=0;i<n-1;i++) {
        scanf("%d%d",&from,&to);
        temp = new node();
        temp->name = to;
        temp->next = graph[from];
        graph[from] = temp;
        temp = new node();
        temp->name = from;
        temp->next = graph[to];
        graph[to] = temp;
    }
    k = BFS(graph,visited,roots,n);
    if(k > 1) printf("Error: %d components\n", k);
    else {
        memset(visited,0,sizeof(visited));
        BFStravers(graph,visited,roots[0],roots,1);
        sort(roots.begin(),roots.end(),less<int>());
        for(int a : roots) {
            cout << a << endl;
        }
    }
    return 0;
}
