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
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
void checkmin(ll &x,ll y){if(x>y) x=y;}
void checkmax(ll &x,ll y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define Sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=300005;
int n,k,fa[N],son[N],dep[N];
vector<int> v[N];
struct node{
    int x,maxx;  
};
vector<node> dp[N];
int id[N],mxdep[N];

void dfs1(int u){
    mxdep[u]=dep[u];
    for(auto to : v[u]){
        dep[to]=dep[u]+1;
        dfs1(to);
        checkmax(mxdep[u],mxdep[to]+1);
        if(mxdep[son[u]]<mxdep[to]) son[u]=to;
    }
}

int T[N];
void dfs2(int u){
    int szu=0;
    if(son[u]){
        dfs2(son[u]),id[u]=id[son[u]];
        szu=Sz(dp[id[u]]);
        int tt=dp[id[u]][szu-1].maxx;
        if(szu>k) checkmax(tt,dp[id[u]][szu-k-1].maxx+1);
        dp[id[u]].push_back({tt,tt});
    }
    else dp[id[u]].push_back({1,1});
    szu++;
    for(auto to : v[u]){
        if(to==son[u]) continue;
        dfs2(to);  dp[id[to]].push_back({0,0});
        for(int i=0;i<Sz(dp[id[to]]);i++){
            T[i]=1;
            int tmp=max(i,k+1-i),szto=Sz(dp[id[to]]);
            if(tmp<Sz(dp[id[u]]))
                checkmax(T[i],dp[id[to]][szto-i-1].x+dp[id[u]][szu-tmp-1].maxx);
            else checkmax(T[i],dp[id[to]][szto-i-1].x);
            if(tmp<Sz(dp[id[to]]))
                checkmax(T[i],dp[id[u]][szu-i-1].x+dp[id[to]][szto-tmp-1].maxx);
            else checkmax(T[i],dp[id[u]][szu-i-1].x);
        }
        for(int i=0;i<Sz(dp[id[to]]);i++)
            dp[id[u]][szu-i-1].x=T[i];
        for(int i=Sz(dp[id[to]])-1;i>=0;i--){
            int tmp=szu-i-1;
            checkmax(dp[id[u]][tmp].maxx,dp[id[u]][tmp].x);
            if(tmp) 
                checkmax(dp[id[u]][tmp].maxx,dp[id[u]][tmp-1].maxx);
        }
        dp[id[to]].clear();
    }
    //outln(u);
    //for(auto to : dp[id[u]]) cout<<to.x<<" "<<to.maxx<<endl; 
}

int main()
{
    n=read(); k=read()-1;
    for(int i=1;i<=n;i++) dp[i].clear();
    for(int i=2;i<=n;i++){
        fa[i]=read()+1;
        v[fa[i]].push_back(i);
    }
    if(k==0){
        printf("%d\n",n);
        return 0;
    }
    for(int i=1;i<=n;i++) id[i]=i;
    dfs1(1); 
    dfs2(1);
    int ans=1;
    for(int i=0;i<Sz(dp[id[1]]);i++) checkmax(ans,dp[id[1]][i].x);
    cout<<ans<<endl;
    return 0;
}