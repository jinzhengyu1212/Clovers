#include<bits/stdc++.h>
using namespace std;
const int N=100005;
const int inf=10000000;
int n; vector<int> v[N];
int dep[N],fa[N],col[N],minn[N];

void dfs(int u,int f){
    minn[u]=inf;
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==f) continue;
        dep[to]=dep[u]+1; fa[to]=u;
        dfs(to,u); minn[u]=min(minn[u],minn[to]+1);
    }
    if(minn[u]==inf) minn[u]=0;
}

void dfs2(int u,int S){
    if(col[u]==1) S--;
    if(minn[u]<S) S--,col[u]=1;
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==fa[u]) continue;
        dfs2(to,S);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        v[x].push_back(y); v[y].push_back(x);
    }
    dep[1]=1;
    dfs(1,-1);
    int id=1,mi=inf;
    for(int i=2;i<=n;i++){
        if(v[i].size()==1&&dep[i]<mi) mi=dep[i],id=i;
    }
    int now=id,S=0;
    while(now!=0){
        S++; col[now]=1;
        now=fa[now];
    }
    dfs2(1,S);
    int ans=0;
    for(int i=1;i<=n;i++) ans+=col[i];
    cout<<ans<<endl;
    return 0;
}