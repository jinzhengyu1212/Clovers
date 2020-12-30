#include<bits/stdc++.h>
using namespace std;
const int N=55;
const int MOD=998244353;
int ADD(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int MUL(int x,int y){return 1ll*x*y%MOD;}
int n,a[N],b[N],ans=0;
int dep[N],fa[N];
vector<int> v[N];

int bl,vis[N];
void dfs(int u){
    if(!bl) return;
    vis[u]=1;
    sort(v[u].begin(),v[u].end());
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i];
        if(vis[to]){bl=0; return;}
        dep[to]=dep[u]+1; swap(b[u],b[to]); 
        dfs(to);
    }
}

namespace DSU{
    int fa[N];
    void init(){for(int i=1;i<=n;i++) fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
    void unite(int x,int y){fa[getfather(x)]=getfather(y);}
    bool same(int x,int y){return getfather(x)==getfather(y);}
}

int cnt=0;
void solve(int now){
    // DSU::init();
    // for(int i=1;i<=now-1;i++){
    //     if(DSU::same(i,fa[i])) return;
    //     if(!DSU::same(i,fa[i])&&fa[i]) DSU::unite(i,fa[i]);
    // }
    if(now==n+1) return;
    cnt++;
    // if(now==n+1){
    //     //for(int i=1;i<=n;i++) cout<<fa[i]<<" "; cout<<endl;
    //     for(int i=1;i<=n;i++) v[i].clear(),vis[i]=0;
    //     for(int i=1;i<=n;i++){
    //         if(fa[i]) v[fa[i]].push_back(i);
    //     }
    //     for(int i=1;i<=n;i++) b[i]=i;
    //     for(int i=1;i<=n;i++) if(b[i]==i) dep[i]=0, dfs(i);
    //     bl=0;
    //     for(int i=1;i<=n;i++) if(b[i]!=a[i]) bl=0;
    //     if(bl){
    //         int tmp=1;
    //         for(int i=1;i<=n;i++){
    //             if(dep[i]) tmp=MUL(tmp,dep[i]);
    //         }
    //         ans=ADD(ans,tmp);
    //     }        
    //     return;
    // }
    for(int i=0;i<=n;i++) if(i!=now){
        //fa[now]=i;
        solve(now+1); 
    }
}

int main(){
    scanf("%d",&n); for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    solve(1);
    cout<<cnt<<endl;
    cout<<ans<<endl;
}