#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
const int N=20005;
typedef long long ll;
struct Basis{
    ll p[61]={0};
    void insert(ll x){
        for(ll i=60;i>=0;i--){
            if((x>>i)&1ll){
                if(!p[i]){p[i]=x; return;}
                x^=p[i];
            }
        }
    }
    void init(){
        for(ll i=60;i>=0;i--){
            for(ll j=i-1;j>=0;j--){
                if((p[i]>>j)&1ll) p[i]^=p[j];
            }
        }
    }
}B[N][17];

Basis merge(Basis A,Basis B){
    for(int i=0;i<=60;i++) 
        if(A.p[i]) B.insert(A.p[i]);
    return B;
}

int n,m; ll a[N];
vector<int> v[N];
int fa[N][18],dep[N]; 
Basis S[N];

void dfs(int u){
    S[u].insert(a[u]);
    for(int i=0;i<(int)v[u].size();i++){
        int to=v[u][i]; if(to==fa[u][0]) continue;
        S[to].insert(a[to]);
        fa[to][0]=u; B[to][0]=S[to];
        for(int j=1;j<17;j++){
            fa[to][j]=fa[fa[to][j-1]][j-1];
            if(fa[to][j]) B[to][j]=merge(B[to][j-1],B[fa[to][j-1]][j-1]);
        } 
        dep[to]=dep[u]+1; dfs(to);
    }
}

Basis LCA(int x,int y){
    Basis ret;
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=16;i>=0;i--) if(dep[fa[x][i]]>=dep[y]){
        ret=merge(ret,B[x][i]), x=fa[x][i];
    }
    if(x==y) {ret=merge(ret,S[x]); return ret;}

    for(int i=16;i>=0;i--) if(fa[x][i]!=fa[y][i]){
        ret=merge(ret,B[x][i]); x=fa[x][i];
        ret=merge(ret,B[y][i]); y=fa[y][i];
    }
    ret=merge(ret,S[x]); ret=merge(ret,S[y]);
    ret=merge(ret,S[fa[x][0]]);
    return ret;
}

void init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        v[x].push_back(y); v[y].push_back(x);
    }
    S[1].insert(a[1]); dep[1]=1; dfs(1);
}

void solve(){
    while(m--){
        int x,y; scanf("%d%d",&x,&y);
        Basis ret=LCA(x,y);
        ret.init(); ll ans=0;
        for(int i=0;i<=60;i++) ans^=ret.p[i];
        printf("%lld\n",ans);
    }
}

int main(){
    init();
    solve();
    return 0;
}