/*
the vast starry sky,
bright for those who chase the light.
*/
#include "highway.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
int _abs(int x){return x<0 ? -x : x;}void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=130005;
int n,m,A,B,Edg,ans1,ans2;
int X,Y,depx[N],depy[N],fax[N],fay[N],fa[N],fae[N],id[N];
ll Dis;
vector<int> U,V,w,G[N],v[N],ori;
map<pii,int> mp;

void findEdg(){
    int l=0,r=m-1,mid;
    while(l<=r){
        mid=(l+r)>>1;
        for(int i=0;i<m;i++) w[i]=0;
        for(int i=0;i<=mid;i++) w[i]=1;
        ll dis=ask(w);
        if(dis==Dis) l=mid+1;
        else r=mid-1,Edg=mid;
    }
    X=U[Edg],Y=V[Edg];
}

void bfsx(){
    memset(fax,-1,sizeof(fax));
    queue<int> q; q.push(X);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(auto &to : v[u]) if(depx[to]==-1){
            depx[to]=depx[u]+1; q.push(to); 
            fax[to]=u;
        }
    }
}
void bfsy(){
    memset(fay,-1,sizeof(fay));
    queue<int> q; q.push(Y);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(auto &to : v[u]) if(depy[to]==-1){
            depy[to]=depy[u]+1; q.push(to); 
            fay[to]=u;
        }
    }
}

void build(){
    memset(fa,-1,sizeof(fa));
    ori.resize(m); for(int i=0;i<m;i++) ori[i]=1;
    for(int i=0;i<n;i++){
        if(depx[i]<depy[i]) fa[i]=fax[i];
        else if(depy[i]<depx[i]) fa[i]=fay[i];
        if(fa[i]!=-1){
            G[fa[i]].push_back(i);
            fae[i]=mp[mk(fa[i],i)];
            ori[fae[i]]=0;
        }
    }
    ori[Edg]=0;
}

void find(int typ){
    queue<int> q; q.push(typ==1 ? X : Y); int top=0;
    while(!q.empty()){
        int u=q.front(); q.pop(); id[++top]=u;
        for(auto &to : G[u]) q.push(to);
    }
    int l=1,r=top,mid,best=1;
    while(l<=r){
        mid=(l+r)>>1;
        w=ori;
        for(int i=mid+1;i<=top;i++) w[fae[id[i]]]=1;
        ll dis=ask(w);
        if(dis==Dis) best=mid,r=mid-1;
        else l=mid+1;
    }
    if(typ==1) ans1=id[best]; else ans2=id[best];
}

void find_pair(int N,vector<int> UU,vector<int> VV,int AA,int BB){
    n=N; m=UU.size(); A=AA; B=BB; U=UU; V=VV;
    for(int i=0;i<m;i++){
        v[U[i]].push_back(V[i]);
        v[V[i]].push_back(U[i]);
        mp[mk(U[i],V[i])]=i; mp[mk(V[i],U[i])]=i;
    }
    w.resize(m); for(int i=0;i<m;i++) w[i]=0;
    Dis=ask(w); findEdg();
    memset(depx,-1,sizeof(depx)); memset(depy,-1,sizeof(depy));
    depx[X]=0; depy[Y]=0;
    bfsx(); bfsy(); build();
    find(1); find(2);
    answer(ans1,ans2);
}