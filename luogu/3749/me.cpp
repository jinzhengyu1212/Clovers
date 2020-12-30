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
const int N=105;
const int P=N*N*2;
const int E=2000005;
const int V=1001;
int n,m,a[N],d[N][N];
int first[P],nxt[E<<1],point[E<<1],w[E<<1],cur[P],e=0;
void add_edge(int x,int y,int z){
    point[e]=y; w[e]=z;
    nxt[e]=first[x]; first[x]=e++;
}
void ADD(int x,int y,int z){
    add_edge(x,y,z);
    add_edge(y,x,0);
}

int S,T,vis[P],dep[P];
bool bfs(){
    memset(vis,0,sizeof(vis));
    queue<int> q; q.push(S); dep[S]=1; vis[S]=1;
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=first[u];i!=-1;i=nxt[i]){
            int to=point[i]; 
            if(vis[to]||!w[i]) continue;
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
        if(tmp) ret-=tmp,w[i]-=tmp,w[i^1]+=tmp;
        if(!ret) break;
    }
    if(ret==flow) dep[u]=-1;
    return flow-ret;
}

int tot=0;
int Dinic(){
    int ret=0;
    while(bfs()){
        for(int i=1;i<=tot;i++) cur[i]=first[i];
        ret+=dfs(S,inf);
    }
    return ret;
}

int sum=0,id[N][N],id2[V],tt[V],bl[V];
void init(){
    n=read(); m=read();
    memset(first,-1,sizeof(first));
    for(int i=1;i<=n;i++) a[i]=read(),tt[a[i]]++;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++) d[i][j]=read();
    }
}

void build(){
    S=++tot; T=++tot;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++) id[i][j]=++tot;
    }
    for(int len=2;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            int len2=len-1;
            for(int l2=l;l2+len2-1<=n;l2++){
                int r2=l2+len2-1; if(r2>r) break;
                ADD(id[l][r],id[l2][r2],inf);
            }
        }
    }
    for(int i=1;i<=n;i++) d[i][i]-=a[i];
    for(int i=1;i<V;i++){
        if(tt[i]){
            id2[i]=++tot;
            ADD(id2[i],T,m*i*i);
        }
    }
    for(int len=1;len<=n;len++){
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            if(d[l][r]>=0) ADD(S,id[l][r],d[l][r]),sum+=d[l][r];
            else ADD(id[l][r],T,-d[l][r]);
            for(int k=l;k<=r;k++){
                if(!bl[a[k]]){
                    bl[a[k]]=1;
                    ADD(id[l][r],id2[a[k]],inf);
                }
            }
            for(int k=l;k<=r;k++) bl[a[k]]=0;
        }
    }
}

int main()
{
    init(); 
    build();
    printf("%d\n",sum-Dinic());
    return 0;
}