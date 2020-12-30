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
const int N=35;
int n,m,mp[N*N][N*N],vis[N*N],in[N*N],cnt,wudi[N*N],Sc[N*N],Tmp[N*N][N*N];
int idx(int x,int y){return x*m+y+1;}

vector<int> seq;
void init(){
    n=read(); m=read();
    cnt=n*m;
    for(int i=1;i<=cnt;i++){
        Sc[i]=read(); int w=read();
        while(w--){
            int x=read(),y=read();
            mp[idx(x,y)][i]=1;
        } 
    }    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=j+1;k<m;k++){
                mp[idx(i,j)][idx(i,k)]=1;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        for(int j=1;j<=cnt;j++){
            Tmp[i][j]=mp[j][i];
            if(Tmp[i][j]) in[j]++;
        }
    }
    queue<int> q;
    for(int i=1;i<=cnt;i++){
        if(!in[i]) q.push(i);
    }
    while(!q.empty()){
        int u=q.front(); vis[u]=1; q.pop();
        seq.push_back(u);
        for(int to=1;to<=cnt;to++){
            if(!Tmp[u][to]) continue;
            if(!--in[to]) q.push(to);
        }        
    }
    for(int i=1;i<=cnt;i++) wudi[i]=vis[i]^1;
    for(auto &u : seq){
        for(int to=1;to<=cnt;to++){
            if(!mp[u][to]) continue;
            wudi[u]|=wudi[to];
        }
    }
    seq.clear();
    for(int i=1;i<=cnt;i++) if(!wudi[i]) seq.push_back(i);
    // cout<<"OK\n";
}

namespace Flow{
    const int M=1005*1005;
    int e=0,first[M],nxt[M<<1],point[M<<1],w[M<<1],cur[M];
    void add_edge(int x,int y,int z){
        w[e]=z; point[e]=y;
        nxt[e]=first[x]; first[x]=e++;
    }
    void ADD(int x,int y,int z){
        add_edge(x,y,z);
        add_edge(y,x,0);
    }
    int SSS,TTT,dep[M],vis[M];
    bool bfs(){
        queue<int> q;
        memset(vis,0,sizeof(vis));
        q.push(SSS); dep[SSS]=1; vis[SSS]=1;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int i=first[u];i!=-1;i=nxt[i]){
                int to=point[i];
                if(!w[i]||vis[to]) continue;
                dep[to]=dep[u]+1; vis[to]=1;
                q.push(to);
            }
        }
        return vis[TTT];
    }
    int dfs(int u,int flow){
        if(u==TTT) return flow;
        int ret=flow;
        for(int &i=cur[u];i!=-1;i=nxt[i]){
            int to=point[i];
            if(!w[i]||dep[to]!=dep[u]+1) continue;
            int tmp=dfs(to,min(ret,w[i]));
            if(tmp) ret-=tmp,w[i]-=tmp,w[i^1]+=tmp;
            if(!ret) break;
        }
        if(flow==ret) dep[u]=-1;
        return flow-ret;
    }
    int Dinic(){
        int ret=0;
        while(bfs()){
            for(int i=1;i<=cnt+2;i++) cur[i]=first[i];
            ret+=dfs(SSS,inf);
        }
        return ret;
    }
    int SUM=0;
    void build(){
        SSS=cnt+1; TTT=cnt+2;
        //outln(SSS); outln(TTT);
        memset(first,-1,sizeof(first));
        memset(in,0,sizeof(in));
        for(auto &u : seq){
            int deg=0; SUM+=max(0,Sc[u]);
            for(int to=1;to<=cnt;to++){
                if(wudi[to]||!mp[u][to]) continue;
                deg++; in[to]++;
                ADD(u,to,inf);
            }
            if(Sc[u]<0) ADD(u,TTT,-Sc[u]);
            else ADD(SSS,u,Sc[u]);
        }
    }
    void solve(){
        build();
        //cout<<SUM<<endl;
        printf("%d\n",SUM-Dinic());
    }
}

int main()
{
    init();
    Flow::solve();
    return 0;
}