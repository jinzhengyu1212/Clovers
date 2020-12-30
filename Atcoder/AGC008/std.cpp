#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
#define x first
#define y second
#define bg begin()
#define ed end()
#define pb push_back
#define mp make_pair
#define sz(a) int((a).size())
#define R(i,n) for(int i(0);i<(n);++i)
#define L(i,n) for(int i((n)-1);i>=0;--i)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=2e5;
int n; ll ns=1;
bitset<N> key;

//Graph
int e[N],E,nex[N<<1],to[N<<1];
void adde(register int u,register int v)
    {nex[E]=e[u],to[e[u]=E++]=v;}
int sz[N],mn[N],mx[N],se[N];
void dfs0(register int u,register int fa){
    mn[u]=(sz[u]=key[u])?0:iinf;
    for(register int i=e[u];~i;i=nex[i])if(to[i]!=fa){
        register int v=to[i];
        dfs0(v,u),sz[u]+=sz[v];
        register int vl=mx[v]+1; 
        if(vl>mx[u]) se[u]=mx[u],mx[u]=vl;
        else if(vl>se[u]) se[u]=vl;
        if(sz[v]&&!key[u]) mn[u]=min(mn[u],vl);
    }
}
void dfs1(register int u,register int fa){
    register int ml=min(mx[u]-1,se[u]+1);
    ml>=mn[u]&&(ns+=ml-mn[u]+1);
    for(register int i=e[u];~i;i=nex[i])if(to[i]!=fa){
        register int v=to[i];
        register int ul=((mx[v]+1==mx[u])?se[u]:mx[u])+1;
        if(ul>mx[v]) se[v]=mx[v],mx[v]=ul;
        else if(ul>se[v]) se[v]=ul;
        if(sz[0]!=sz[v]&&!key[v]) mn[v]=min(mn[v],ul);        
        dfs1(v,u);
    }
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    R(i,n) e[i]=-1;
    R(i,n-1){
        static int u,v;
        cin>>u>>v,--u,--v;
        adde(u,v),adde(v,u);
    }
    R(i,n){
        static char c;
        cin>>c,key[i]=c=='1';
    }
    dfs0(0,-1),dfs1(0,-1);
    cout<<ns<<'\n';
    return 0;
}