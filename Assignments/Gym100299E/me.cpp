#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
int n,a[N],fa[N],T;
vector<int> v[N];
int inpath[N];
void dfs(int u){
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==fa[u]) continue;
        fa[to]=u; dfs(to);
    }
}

void init(){
    scanf("%d%d",&n,&T);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) v[i].clear(), inpath[i]=0;
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs(1);
    int now=T;
    while(now!=1){
        inpath[now]=1;
        now=fa[now];
    }
}

struct node{
    int id; ll val;
};

ll add=0;
int vis[N];
queue<int> q;
void bfs(){
    while(!q.empty()) q.pop();
    for(int i=1;i<=n;i++) vis[i]=0;
    add=0;
    if(a[1]<0){
        
    }
}

int main(){
    int Testcases; scanf("%d",&Testcases);
    while(Testcases--){

    }
}