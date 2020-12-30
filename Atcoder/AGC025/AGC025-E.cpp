#include<bits/stdc++.h>
using namespace std;
const int N=500005;
typedef pair<int,int> pii;
#define mk make_pair
struct Edge{
    int from,to,flag;
}E[N];
int n,m;
vector<int> v[N];
vector<pii> G[N];

int deg[N],fa[N],dep[N],f[N][20];
void dfs(int u){
    deg[u]=0;
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==fa[u]) continue;
        deg[u]++; fa[to]=u; dep[to]=dep[u]+1;
        f[to][0]=u; for(int j=1;j<20;j++) f[to][j]=f[f[to][j-1]][j-1]; 
        dfs(to);
    }
}

int LCA(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}

void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n-1;i++){
        int x,y; scanf("%d%d",&x,&y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=m;i++){
        scanf("%d%d",&E[i].from,&E[i].to); 
        E[i].flag=0;
    }
    dep[1]=1; dfs(1);
}

int ans=0,F[N][2];
void calc(){
    for(int i=1;i<=m;i++){
        int x=E[i].from,y=E[i].to,lca=LCA(x,y);
        while(x!=lca){
            F[x][0]=1; x=fa[x];
        }
        while(y!=lca){
            F[y][1]=1; y=fa[y];
        }
    }
    for(int i=1;i<=n;i++) ans+=F[i][0]+F[i][1];
}

int bl[N],rev[N];
int tot,vis[N];
queue<int> q;
int son[N][2];
void dfs2(int u){
    bl[u]=1;
    if(u<=m) {E[u].flag=rev[u]; return;}
    if(son[u][0]) rev[son[u][0]]=rev[u], dfs2(son[u][0]);
    if(son[u][1]) rev[son[u][1]]=rev[u]^1, dfs2(son[u][1]);
}
//对于把(u,a),(u,b)变成(a,b),可以建一条新的边并且连向(u,a),(u,b),用重构树的思想表示出该边与那两条边的方向关系
void solve(){
    for(int i=1;i<=m;i++){
        G[E[i].from].push_back(mk(E[i].to,i));
        G[E[i].to].push_back(mk(E[i].from,i));
    } tot=m;
    for(int i=1;i<=n;i++) if(!deg[i]) q.push(i);
    while(!q.empty()){
        int now=q.front(); q.pop(); vis[now]=1;
        int from=-1,preid=-1;
        for(int i=0;i<(int)G[now].size();i++){
            int to=G[now][i].first,id=G[now][i].second;
            if(vis[to]) continue;
            if(from==0) {
                if(fa[now]!=to){
                    tot++; son[tot][0]=id;
                    if(E[id].from!=now)
                    {
                        swap(E[id].from,E[id].to);
                        swap(son[id][0],son[id][1]);
                    }
                    E[tot].from=fa[now]; E[tot].to=E[id].to;
                    G[E[tot].from].push_back(mk(E[tot].to,tot));
                    G[E[tot].to].push_back(mk(E[tot].from,tot));
                }
            }
            else if(from==-1) from=to,preid=id;
            else{//preid->nowid
                if(E[preid].to!=now) 
                {
                    swap(E[preid].from,E[preid].to);
                    swap(son[preid][0],son[preid][1]);
                }
                if(E[id].to!=now) 
                {
                    swap(E[id].from,E[id].to);
                    swap(son[id][0],son[id][1]);
                }
                tot++; son[tot][0]=preid; son[tot][1]=id;
                E[tot].from=E[preid].from, E[tot].to=E[id].from;
                G[E[tot].from].push_back(mk(E[tot].to,tot));
                G[E[tot].to].push_back(mk(E[tot].from,tot));
                from=0; preid=-1;
            }
        }
        if(preid!=-1&&fa[now]!=from){
            if(E[preid].from!=now) 
            {
                swap(E[preid].from,E[preid].to);
                swap(son[preid][0],son[preid][1]);
            }
            tot++; son[tot][0]=preid;
            E[tot].from=fa[now]; E[tot].to=E[preid].to;
            G[E[tot].from].push_back(mk(E[tot].to,tot));
            G[E[tot].to].push_back(mk(E[tot].from,tot));
        }
        G[now].clear(); deg[fa[now]]--;
        if(!deg[fa[now]]) q.push(fa[now]);
    }
    for(int i=tot;i>=m+1;i--){
        if(!bl[i]) dfs2(i);
    }
    for(int i=1;i<=m;i++){
        if(E[i].flag) swap(E[i].from,E[i].to);
    }
    calc(); printf("%d\n",ans);
    for(int i=1;i<=m;i++) printf("%d %d\n",E[i].from,E[i].to);
}

int main(){
    init(); solve();
    return 0;
}