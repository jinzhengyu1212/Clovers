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
const int N=2005;
const int M=200005;
int n,m;

int S,T,first[M],nxt[M<<1],cur[M],point[M<<1],w[M<<1],e=0;
void add_edge(int x,int y,int z){
    nxt[e]=first[x]; first[x]=e;
    point[e]=y; w[e++]=z;
}
void ADD(int x,int y,int z){
    add_edge(x,y,z);
    add_edge(y,x,0);
}

int vis[N<<2],dep[M];
int head,tail,cnt;
int q[M];
bool bfs(int S,int T){
    memset(vis,0,sizeof(vis));
    vis[S]=1; head=0,tail=1; 
    q[head]=S;
    while(head!=tail){
        int u=q[head++]; 
        for(int i=first[u];i!=-1;i=nxt[i]){
            int to=point[i]; 
            if(vis[to]||!w[i]) continue;
            vis[to]=1; dep[to]=dep[u]+1;
            q[tail++]=to;
        }
    }
    return vis[T];
}

int dfs(int u,int flow,int dest){
    if(u==dest) return flow;
    int ret=flow;
    for(int &i=cur[u];i!=-1;i=nxt[i]){
        int to=point[i];
        if(!w[i]||dep[to]!=dep[u]+1) continue;
        int tmp=dfs(to,min(ret,w[i]),dest);
        if(tmp){
            w[i]-=tmp; w[i^1]+=tmp;
            ret-=tmp; if(!ret) break;
        }
    }
    if(ret==flow) dep[u]=-1;
    return flow-ret;
}

int Dinic(int S,int T){
    int ret=0;
    while(bfs(S,T)){
        for(int i=1;i<=cnt;i++) cur[i]=first[i];
        ret+=dfs(S,inf,T);
    }
    return ret;
}

int id[N<<1];
int main()
{
    n=read(); m=read();
    memset(first,-1,sizeof(first));
    cnt=n+m; S=++cnt; T=++cnt;
    for(int i=1;i<=m;i++){
        int x=read(),y=read();
        ADD(i+n,x,inf); ADD(i+n,y,inf);
    }
    int sum=m;
    for(int i=1;i<=n;i++) id[i]=e,ADD(i,T,2);
    for(int i=n+1;i<=n+m;i++) ADD(S,i,1); 
    int ans=0;
    for(int i=1;i<=n;i++){
        if(i>1){
            ans-=Dinic(i,S);
            w[id[i-1]]=2;
        }
        w[id[i]]=0; w[id[i]^1]=0;
        ans+=Dinic(S,T);
        if(sum>ans){puts("No"); return 0;}
    }
    puts("Yes");
    return 0;
}