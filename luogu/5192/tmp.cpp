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
const int N=3005;
const int M=400;
const int E=N*M;
int n,m,G[N];
int e=0,first[N],nxt[E],point[E],w[E],cur[N],S,T,SS,TT;
void add_edge(int x,int y,int z){
    nxt[e]=first[x]; first[x]=e;
    point[e]=y; w[e++]=z;
}
void ADD(int x,int y,int z){
    add_edge(x,y,z);
    add_edge(y,x,0);
}

int vis[N],dep[N];
bool bfs(int S,int T){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    q.push(S); vis[S]=1;
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=first[u];i!=-1;i=nxt[i]){
            int to=point[i]; 
            if(vis[to]||!w[i]) continue;
            vis[to]=1; dep[to]=dep[u]+1;
            q.push(to); 
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
            ret-=tmp;
        }
    }
    if(ret==flow) dep[u]=-1;
    return flow-ret;
}

int Dinic(int S,int T){
    int ret=0;
    while(bfs(S,T)){
        for(int i=1;i<=n+2;i++) cur[i]=first[i];
        ret+=dfs(S,inf,T);
    }
    return ret;
}

int IN[N];
void init(){
    memset(first,-1,sizeof(first));
    memset(IN,0,sizeof(IN)); e=0;
    n=read(); m=read(); S=read(); T=read();
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),L=read(),R=read();
        ADD(x,y,R-L); IN[x]-=L; IN[y]+=L;
    }
    SS=n+1,TT=n+2;
    for(int i=1;i<=n;i++){
        if(IN[i]>=0) ADD(SS,i,IN[i]);
        else ADD(i,TT,-IN[i]);
    }
    ADD(T,S,inf);
}

void solve(){
    int ans=0;
    Dinic(SS,TT);
    for(int i=first[SS];i!=-1;i=nxt[i])
        if(w[i]){puts("please go home to sleep"); exit(0);}
    first[S]=nxt[first[S]];
    first[T]=nxt[first[T]];
    ans+=Dinic(S,T);
    cout<<ans+w[e-1]<<endl;
}

int main()
{
    init(); solve();
    return 0;
}