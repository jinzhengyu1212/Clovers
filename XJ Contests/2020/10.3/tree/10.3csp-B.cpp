#include<bits/stdc++.h>
using namespace std;
//typedef long long ll;
#define int long long
const int N=120000;
int n,v[N],w[N],Q,typ,ans=0,TYP;
vector<int> G[N];
int decode(int x){return (x+typ*ans-1)%n+1;}
bool checkv(){
    for(int i=1;i<=n;i++) if(v[i]) return 0;
    return 1;
}

/*int fa[N],top[N],sz[N],son[N],dep[N];
void dfs1(int u){
    sz[u]=1;
    for(int i=0;i<(int)G[u].size();i++){
        int to=G[u][i]; if(to==fa[u]) continue;
        fa[to]=u; dep[to]=dep[u]+1; dfs1(to); 
        sz[u]+=sz[to];
        if(sz[son[u]]<sz[to]) son[u]=to; 
    }
}

void dfs2(int u){
    if(son[u]) top[son[u]]=top[u], dfs2(son[u]);
    for(int i=0;i<(int)G[u].size();i++){
        int to=G[u][i]; if(to==fa[u]||to==son[u]) continue;
        top[to]=to; dfs2(to);
    }
}*/

void init(){
    scanf("%lld",&TYP);
    scanf("%lld%lld%lld",&n,&Q,&typ);
    for(int i=1;i<n;i++){
        int x,y; scanf("%lld%lld",&x,&y);
        G[x].push_back(y); G[y].push_back(x);
    }
    for(int i=1;i<=n;i++) scanf("%lld",&w[i]);
    for(int i=1;i<=n;i++) scanf("%lld",&v[i]);
}

namespace solver1{
    int fa[N][20],dep[N],sum[N][20];
    void dfs(int u){
        for(int i=0;i<(int)G[u].size();i++){
            int to=G[u][i]; if(to==fa[u][0]) continue;
            fa[to][0]=u; dep[to]=dep[u]+1; 
            sum[to][0]=w[to];
            for(int j=1;j<20;j++) fa[to][j]=fa[fa[to][j-1]][j-1];
            for(int j=1;j<20;j++) sum[to][j]=sum[to][j-1]+sum[fa[to][j-1]][j-1];
            dfs(to); 
        }
    }
    int LCA(int x,int y){
        int ret=0;
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]){
            ret+=sum[x][i];
            x=fa[x][i];
        }
        if(x==y){
            ret+=w[x];
            return ret;
        }
        for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]){
            ret+=sum[x][i]; x=fa[x][i];
            ret+=sum[y][i]; y=fa[y][i];
        }
        ret+=w[x]; ret+=w[y]; ret+=w[fa[x][0]];
        return ret;
    }
    void main(){
        for(int i=1;i<=n;i++) w[i]=max(w[i],0LL);
        sum[1][0]=w[1];
        dep[1]=1; dfs(1);
        while(Q--){
            int x,y,t; scanf("%lld%lld%lld",&x,&y,&t);
            x=decode(x); y=decode(y); t=decode(t);
            ans=LCA(x,y);
            printf("%lld\n",ans);
        }
    }
}

namespace solver2{
    int fa[N][20],dep[N];
    void dfs(int u){
        for(int i=0;i<(int)G[u].size();i++){
            int to=G[u][i]; if(to==fa[u][0]) continue;
            fa[to][0]=u; dep[to]=dep[u]+1; 
            for(int j=1;j<20;j++) fa[to][j]=fa[fa[to][j-1]][j-1];
            dfs(to); 
        }
    }
    int LCA(int x,int y){
        int ret=0;
        if(dep[x]<dep[y]) swap(x,y);
        for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
        if(x==y) return x;
        for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
        return fa[x][0];
    }

    int jump(int from,int to,int ti,int flag){
        if(from==to){
            if(flag==1) return max(0LL,w[from]+ti*v[from]);
            else return 0;
        }
        int ret=max(0LL,w[from]+ti*v[from]);
        return ret+jump(fa[from][0],to,ti+flag,flag);
    }
    
    void main(){
        dep[1]=1; dfs(1);
        while(Q--){
            int x,y,t; scanf("%lld%lld%lld",&x,&y,&t);
            x=decode(x); y=decode(y); t=decode(t);
            int lca=LCA(x,y); 
            int dist=dep[x]+dep[y]-2*dep[lca];
            ans=0; ans+=jump(x,lca,t,1);
            ans+=jump(y,lca,t+dist,-1);
            printf("%lld\n",ans);
        }
    }
}

void solve(){
    if(checkv()){
        solver1::main();
        return;
    }
    solver2::main();
}

signed main(){
    init(); solve();
    return 0;
}