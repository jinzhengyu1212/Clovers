//#include "swap.h"
#include<bits/stdc++.h>
using namespace std;
const int N=400005;
const int M=500005;
const int inf=(int)1e9+2;
int n,m,q,a[N],val[N],nn,deg[N];
struct Edge{
	int from,to,cost;
	bool operator < (const Edge &rhs) const{
		return cost<rhs.cost;
	}
}E[M];

vector<int> v[N];
namespace DSU{
	int fa[N];
	void init(){for(int i=1;i<=n+n;i++) fa[i]=i;}
	int getfather(int x){return x==fa[x] ? x : fa[x]=getfather(fa[x]);}
	void unite(int x,int y){
		x=getfather(x); y=getfather(y);
		v[y].push_back(x);
		fa[x]=y;
	}
	bool same(int x,int y){return getfather(x)==getfather(y);}
}

int tot,con[N],sz[N],F[N],B[N];
vector<int> G[N];
void merge(int x,int y){
    if(sz[x]<sz[y]) swap(x,y);
    for(int i=0;i<(int)G[y].size();i++) G[x].push_back(G[y][i]), con[G[y][i]]=x;
    G[y].clear(); sz[x]+=sz[y]; sz[y]=0;
}
void del(int x,int FA){
    for(int i=0;i<(int)G[x].size();i++) {
        con[G[x][i]]=-1;
        DSU::unite(G[x][i],FA);
    }
    G[x].clear(); sz[x]=0;
}
void kruskal(){
    for(int i=1;i<=n;i++) con[i]=i,G[i].push_back(i),F[i]=i,B[i]=i,sz[i]=1;
	  for(int i=1;i<=m;i++){
        int x=E[i].from, y=E[i].to;
        if(con[x]==con[y])
        {
            if(DSU::same(x,y)) continue;
            tot++; val[tot]=E[i].cost;
            if(con[x]==-1) DSU::unite(x,tot), DSU::unite(y,tot); 
            else del(con[x],tot);
            continue;
        }
        else if(con[x]==-1||con[y]==-1)
        {
            tot++; val[tot]=E[i].cost;
            if(con[x]!=-1) del(con[x],tot);
            else DSU::unite(x,tot);
            if(con[y]!=-1) del(con[y],tot);
            else DSU::unite(y,tot);
            continue;
        }
        int X=con[x],Y=con[y];
        if((x==F[X]||x==B[X])&&(y==F[Y]||y==B[Y]))
        {
            int FX=F[X],BX=B[X],FY=F[Y],BY=B[Y];
            merge(X,Y);
            if(x==FX) F[con[x]]=BX;
            else F[con[x]]=FX;
            if(y==FY) B[con[x]]=BY;
            else B[con[x]]=FY;
        }
        else 
        {
            tot++; val[tot]=E[i].cost;
            del(con[x],tot); del(con[y],tot);
        }
	}
}

int dfn_clock=0,dfn[N],fa[N][20],dep[N],id[N],out[N];
void dfs(int u,int f){
	dfn[u]=++dfn_clock; id[dfn_clock]=u; 
	for(int i=0;i<(int)v[u].size();i++){
		int to=v[u][i]; if(to==f) continue;
		fa[to][0]=u; for(int j=1;j<20;j++) fa[to][j]=fa[fa[to][j-1]][j-1];
		dep[to]=dep[u]+1; dfs(to,u);
	}
	out[u]=dfn_clock;
}

int LCA(int x,int y){
    if(!DSU::same(x,y)) return -1;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=19;i>=0;i--) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
    return fa[x][0];
}

void init(int NN, int MM, std::vector<int> U, std::vector<int> V, std::vector<int> W)
{
    n=NN; m=MM;
    for(int i=0;i<m;i++)
    {
        int x=U[i],y=V[i],w=W[i]; x++; y++;
        E[i+1].from=x; E[i+1].to=y; E[i+1].cost=w;
        deg[x]++; deg[y]++;
    }
    DSU::init(); tot=n;
    sort(E+1,E+m+1); kruskal(); 
    for(int i=tot;i>=1;i--)
    {
        if(!dfn[i]) dep[i]=1,dfs(i,-1);
    }
}

int getMinimumFuelCapacity(int X,int Y)
{
    X++; Y++; int lca=LCA(X,Y);
    if(lca==-1) return -1;
    return val[lca];
}