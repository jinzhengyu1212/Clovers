/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e18;
const int MOD=998244353;
int _abs(int x){return x<0 ? -x : x;}
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
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
const int N=200005;
int n,sz[N],ans=inf;
vector<int> v[N];
void dfs(int u,int f){
    sz[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs(to,u); sz[u]+=sz[to];
    }
}

int max3(int x,int y,int z){return max(max(x,y),z);}
int min3(int x,int y,int z){return min(min(x,y),z);}
void check(int x,int y){checkmin(ans,max3(n-x-y,x,y)-min3(n-x-y,x,y));}
set<int> st1,st2;
void dfs2(int u,int f){
    set<int>::iterator it;
    it=st1.lower_bound((n-sz[u])/2);
    if(it!=st1.end()) check(*it,sz[u]);
    if(it!=st1.begin()) it--,check(*it,sz[u]);
    it=st2.lower_bound((n+sz[u])/2);
    if(it!=st2.end()) check(sz[u],*it-sz[u]);
    if(it!=st2.begin()) it--,check(sz[u],*it-sz[u]);
    st2.insert(sz[u]);
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs2(to,u); 
    }
    st2.erase(sz[u]);
    st1.insert(sz[u]);
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs(1,-1);
    dfs2(1,-1); 
    cout<<ans<<endl;
    return 0;
}