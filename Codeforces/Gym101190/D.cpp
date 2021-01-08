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
int cur[N],first[N],nxt[N<<1],point[N<<1],w[N<<1],e=0;
ll cost[N];
void add_edge(int x,int y,int z,ll c){
    point[e]=y; w[e]=z; cost[e]=c;
    nxt[e]=first[x]; first[x]=e++;
}
void ADD(int x,int y,int z,ll c){
    add_edge(x,y,z,-c);
    add_edge(y,x,0,c);
}//reverse the value->calc the max ans
int tot=0,S,T;
ll dis[N]; int vis[N];
bool bfs(){
    queue<int> q;
    for(int i=1;i<=tot;i++) dis[i]=INF,vis[i]=0;
    q.push(S); dis[S]=0; vis[S]=1;
    while(!q.empty()){
        int u=q.front(); q.pop(); vis[u]=0;
        for(int i=first[u];i!=-1;i=nxt[i]) if(w[i]){
            int to=point[i];
            if(dis[u]+cost[i]<dis[to]){
                dis[to]=dis[u]+cost[i];
                if(!vis[to]) vis[to]=1,q.push(to);
            }
        }
    }
    return dis[T]!=INF;
}
ll ans=0,C=0;
int dfs(int u,int flow){
    if(u==T) return flow;
    int ret=flow; vis[u]=1;
    for(int &i=cur[u];i!=-1;i=nxt[i]){
        int to=point[i];
        if(vis[to]||!w[i]||dis[to]!=dis[u]+cost[i]||dis[to]==INF) continue;
        int tmp=dfs(to,min(w[i],ret));
        if(tmp){
            ret-=tmp; ans+=1ll*tmp*cost[i];
            w[i]-=tmp; w[i^1]+=tmp;
            if(!ret) break;
        }
    }
    return flow-ret;
}

int n,la,lb,k,id[N]; ll a[N],b[N];
void build(){
    int m=n-k+1;
    tot=2*m+3;
    S=2*m+2,T=2*m+3;
    static ll val[N];
    for(int i=1;i<=2*m;i++){
        if(i&1) val[i]=-lb;
        else val[i]=-(k-la);
    }
    for(int i=1;i<=2*m+1;i++){
        int delta=val[i]-val[i-1];
        if(delta>0) ADD(i,T,delta,0);
        else ADD(S,i,-delta,0);
        if(i%2==0){
            ADD(i,i-1,inf,0);
            ADD(i,i+1,inf,0);
        }
    }
    for(int i=1;i<=n;i++){
        int l=max(1,2*(i-k)+1),r=min(2*m+1,2*i+1);
        ADD(l,r,1,b[i]-a[i]);
        id[i]=e-1;
    }
}

int main()
{
    freopen("delight.in","r",stdin);
    freopen("delight.out","w",stdout);
    memset(first,-1,sizeof(first));
    n=read(); k=read(); la=read(); lb=read();
    for(int i=1;i<=n;i++) a[i]=read(),ans-=a[i];
    for(int i=1;i<=n;i++) b[i]=read();
    build();
    while(bfs()){
        for(int i=1;i<=tot;i++) vis[i]=0,cur[i]=first[i];
        C+=dfs(S,inf);
    }
    cout<<-ans<<endl;
    for(int i=1;i<=n;i++){
        if(w[id[i]]) printf("E");
        else printf("S");
    } puts("");
    return 0;
}//