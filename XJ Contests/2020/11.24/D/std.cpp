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
const int N=100005;
const int M=10005;
int T,n,m,sg[N],a[N];
vector<int> v[N];
 
int ans[N],dp[N];
int dep[N],fa[N],gf[N];
void dfs(int u){
    dp[u]=sg[a[u]];
    for(auto &to : v[u]){
        if(to==fa[u]) continue;
        dep[to]=dep[u]+1; fa[to]=u; gf[to]=fa[u];
        dfs(to); ans[u]^=dp[to];
    }
    if(gf[u]){
        dp[gf[u]]^=dp[u];
    }
}
 
void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y);
        v[y].push_back(x);
    }
    sg[0]=0;
    for(int i=1;i<=100000;i++){
        sg[i]=i%(m+1);
    }
    dfs(1);
}
 
void jump(int x,int val){
    while(x){
        ans[x]^=val;
        x=gf[x];
    }
}
 
int S=0;
void solve(){
    T=read();
    for(int i=1;i<=T;i++){
        int typ=read();
        if(typ==1){
            int x=read()^S;
            if(ans[x]) puts("Yes"),S++;
            else puts("No");
        }
        else if(typ==2){
            int x=read()^S,y=(read()^S);
            jump(fa[x],sg[a[x]]);
            a[x]+=y;
            jump(fa[x],sg[a[x]]);
        }
        else{
            int x=read()^S,y=read()^S,z=(read()^S);
            fa[y]=x; gf[y]=fa[x]; a[y]=z;
            jump(x,sg[z]);
        }
    }
}
 
int main()
{
    init();
    solve();
    return 0;
}
