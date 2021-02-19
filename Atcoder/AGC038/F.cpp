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
const int N=500005;
const int M=2000005;
int S,T,tot=0;
namespace Flow{
    int e=0,first[N],cur[N],nxt[M],point[M],w[M];
    void add_edge(int x,int y,int z){
        point[e]=y; nxt[e]=first[x];
        w[e]=z; first[x]=e++;
    }
    void ADD(int x,int y,int z){add_edge(x,y,z); add_edge(y,x,0);}
    int dep[N],vis[N];
    bool bfs(){
        memset(vis,0,sizeof(vis));
        queue<int> q;
        q.push(S); vis[S]=1; dep[S]=0;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int i=first[u];i!=-1;i=nxt[i])if(w[i]){
                int to=point[i]; if(vis[to]) continue;
                dep[to]=dep[u]+1; vis[to]=1; q.push(to);
            }
        }
        return vis[T];
    }
    int dfs(int u,int flow){
        if(u==T) return flow;
        int ret=flow;
        for(int &i=cur[u];i!=-1;i=nxt[i]){
            int to=point[i];
            if(!w[i]||dep[to]!=dep[u]+1) continue;
            int tmp=dfs(to,min(ret,w[i]));
            ret-=tmp; w[i]-=tmp; w[i^1]+=tmp;
            if(!ret) break;    
        }
        return flow-ret;
    }
    int Dinic(){
        int ret=0;
        while(bfs()){
            for(int i=1;i<=tot;i++) cur[i]=first[i];
            ret+=dfs(S,inf);
        }
        return ret;
    }
    void init(){
        memset(first,-1,sizeof(first));
    }
}
int n,p[N],q[N],idp[N],idq[N];
int vis[N];

int main()
{
    n=read();
    for(int i=1;i<=n;i++) p[i]=read()+1;
    for(int i=1;i<=n;i++) q[i]=read()+1;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) if(!vis[i]){
        int x=i; tot++;
        while(!vis[x]) vis[x]=1,idp[x]=tot,x=p[x];
    }
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++) if(!vis[i]){
        int x=i; tot++;
        while(!vis[x]) vis[x]=1,idq[x]=tot,x=q[x];
    }
    //for(int i=1;i<=n;i++) out(i),out(idp[i]),outln(idq[i]);
    S=++tot; T=++tot;
    int ans=n; Flow::init();
    for(int i=1;i<=n;i++){
        if(p[i]!=q[i]){
            if(p[i]==i) Flow::ADD(idq[i],T,1);
            else if(q[i]==i) Flow::ADD(S,idp[i],1);
            else Flow::ADD(idq[i],idp[i],1);
        }
        else if(p[i]!=i) Flow::ADD(idp[i],idq[i],1),Flow::ADD(idq[i],idp[i],1);
        else ans--;
    }
    cout<<ans-Flow::Dinic()<<endl;
    return 0;
}