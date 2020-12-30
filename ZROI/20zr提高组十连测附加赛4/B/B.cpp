#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
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
int n; 
vector<int> v[N];
ll up[N],down[N],deg[N],ans=0;

void dfs1(int u,int f){
    up[u]=deg[u];
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs1(to,u); up[u]+=up[to];
    }
    down[u]=2*n-2-up[u];
}

ll mx1[N],mx2[N];
ll dp[N],dp2[N],sum[N],sz[N];
void dfs2(int u,int f){
    dp[u]=down[u]; ll mx=0;
    sum[u]=down[u]; sz[u]=1;
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs2(to,u);
        if(mx1[u]<dp[to]) mx2[u]=mx1[u],mx1[u]=dp[to];
        else if(mx2[u]<dp[to]) mx2[u]=dp[to];
        sz[u]+=sz[to];
    }
    dp[u]+=mx1[u];
}

void dfs3(int u,int f,ll S){
    if(f!=-1){
        dp2[u]=dp2[f]+(2*n-2-(up[f]-up[u])-S);
        if(dp[u]==mx1[f]) checkmax(dp2[u],mx2[f]+(2*n-2-(up[f]-up[u])-S));
        else checkmax(dp2[u],mx1[f]+(2*n-2-(up[f]-up[u])-S));
    }
    checkmax(ans,dp2[u]);
    for(auto &to : v[u]){
        if(to==f) continue;
        dfs3(to,u,u==1 ? 0 : S+up[f]-up[u]);
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++){
        int x=read(),y=read();
        v[x].push_back(y); v[y].push_back(x);
        deg[x]++; deg[y]++;
    }
    dfs1(1,-1);
    dfs2(1,-1);
    ans=dp[1];
    dfs3(1,-1,0);
    printf("%.5lf\n",(double)ans);
    return 0;
}