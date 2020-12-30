/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)1e7;
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
int n,m,s,t;
int e=0,first[N],nxt[N],point[N],w[N],cur[N],cost[N];
void add_edge(int x,int y,int z,int c){
    point[e]=y; w[e]=z; cost[e]=c;
    nxt[e]=first[x]; first[x]=e++;
}
void ADD(int x,int y,int z,int c){
    add_edge(x,y,z,c);
    add_edge(y,x,0,-c);
}

int vis[5005],dis[5005];
bool bfs(int s){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) dis[i]=inf;
    q.push(s); dis[s]=0;
    while(!q.empty()){
        int u=q.front(); vis[u]=0; q.pop();
        for(int i=first[u];i!=-1;i=nxt[i]){
            int to=point[i];
            if(w[i]==0) continue;
            if(dis[u]+cost[i]<dis[to]){
                dis[to]=dis[u]+cost[i];
                if(!vis[to]) q.push(to), vis[to]=1;
            }
        }
    }
    return dis[t]!=inf;
}

int C=0;
int dfs(int u,int flow){
    if(u==t) return flow;
    int ret=flow;
    vis[u]=1;
    for(int &i=cur[u];i!=-1;i=nxt[i]){
        int to=point[i];
        if(!w[i]||dis[to]==inf||vis[to]||dis[to]!=dis[u]+cost[i]) continue;
        int tmp=dfs(to,min(w[i],ret));
        if(tmp) w[i]-=tmp,w[i^1]+=tmp,ret-=tmp,C+=cost[i]*tmp;
        if(!ret) break;
    }
    return flow-ret;
}

void init(){
    memset(first,-1,sizeof(first));
    n=read(); m=read(); s=1; t=n;
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),z=read(),c=read();
        ADD(x,y,z,c);
    }
}

void solve(){
    int ans=0;
    while(bfs(s)){
        for(int i=1;i<=n;i++) cur[i]=first[i];
        memset(vis,0,sizeof(vis));
        ans+=dfs(s,inf);
    }
    cout<<ans<<" "<<C<<endl;
}

signed main()
{
    init(); solve();
    return 0;
}