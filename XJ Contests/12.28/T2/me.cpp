/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,ll> pii;
#define mk make_pair
const int inf=(int)1e9;
const ll INF=(ll)5e17;
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
const int N=3005;
int n,m,k;
vector<pii> v[N]; 
ll a[N],dp[N][N],ans=INF;
void less_than_k(){
    memset(dp,0x3f,sizeof(dp));
    dp[0][1]=0;
    for(int i=0;i<k;i++){
        for(int u=1;u<=n;u++){
            if(dp[i][u]>=INF) continue;
            for(auto &to : v[u]){
                checkmin(dp[i+1][to.first],dp[i][u]+to.second);
            }
        }
    }
    for(int i=0;i<=k;i++) checkmin(ans,dp[i][n]);
}

struct node{
    ll dis; int id;
    bool operator < (const node &rhs) const{
        return dis>rhs.dis;
    }
};
priority_queue<node> q;
int vis[N]; ll dis[N];
void dijkstra(ll val){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0; q.push({0,1});
    while(!q.empty()){
        int u=q.top().id; q.pop();
        if(vis[u]) continue; vis[u]=1;
        for(auto &E : v[u]){
            int to=E.first,Dist=max(0ll,E.second-val); 
            if(vis[to]) continue;
            if(dis[to]>dis[u]+Dist){
                dis[to]=dis[u]+Dist;
                q.push({dis[to],to});
            }
        }
    }
}

int main()
{
    n=read(); m=read(); k=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read(); ll w=read();
        v[x].push_back(mk(y,w));
        v[y].push_back(mk(x,w));
        a[i]=w;
    }
    less_than_k();
    sort(a+1,a+m+1); int tot=unique(a+1,a+m+1)-a-1;
    for(int i=1;i<=tot;i++){
        dijkstra(a[i]);
        checkmin(ans,1ll*k*a[i]+dis[n]);
    }
    cout<<ans<<endl;
    return 0;
}