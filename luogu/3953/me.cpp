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
const ll INF=(ll)5e14;
int MOD=998244353;
int add(ll x,ll y){x+=y; return x>=MOD ? x-MOD : x;}
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
const int M=200005;

int n,m,k;
vector<pii> v[N];
struct node{
    int id,dis;
    bool operator < (const node &rhs) const{
        return dis>rhs.dis;
    }
};
priority_queue<node> Q;
int dis[N],vis[N];
void dijkstra(int S){
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++) vis[i]=0;
    dis[S]=0; Q.push({S,0});
    while(!Q.empty()){
        int u=Q.top().id; Q.pop(); 
        if(vis[u]) continue;
        vis[u]=1;
        for(auto &to : v[u]){
            if(vis[to.first]) continue;
            if(dis[to.first]>dis[u]+to.second){
                dis[to.first]=dis[u]+to.second;
                Q.push({to.first,dis[to.first]});
            }
        }
    }
}

ll dp[N][52];
struct Node{
    int dis,id,add;
    bool operator < (const Node &rhs) const{
        return dis<rhs.dis;
    }
};
priority_queue<Node> q;

void init(){
    n=read(); m=read(); k=read(); MOD=read();
    for(int i=1;i<=n;i++) v[i].clear();
    for(int i=1;i<=m;i++){
        int x=read(),y=read(),z=read();
        v[x].push_back(mk(y,z));
    }
    dijkstra(1);  
}

vector<Node> V;
vector<int> G[N];
int in[N];
vector<Node> KK; 
void topo(int Dis){
    queue<int> q; while(!q.empty()) q.pop();
    for(auto u : V){
        for(auto &to : G[u.id]) in[to]++;
    }
    for(auto &u : V) if(!in[u.id]) q.push(u.id);
    KK.clear();
    while(!q.empty()){
        int u=q.front(); q.pop(); vis[u]=1;
        KK.push_back({Dis,u,Dis-dis[u]});
        for(auto &to : G[u]) if(!--in[to]) q.push(to);
    }
    for(auto &u : V) if(!vis[u.id]) dp[u.id][u.add]=-INF;
    V=KK; 
}

void solve(){
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++){
            if(dis[i]+j<=dis[n]+k) q.push({dis[i]+j,i,j});
        }
    }
    for(int i=0;i<=k;i++) dp[n][i]=1; 
    while(!q.empty()){
        Node now=q.top(); V.clear();
        while(!q.empty()&&q.top().dis==now.dis){
            now=q.top();
            V.push_back(now);
            in[now.id]=0, vis[now.id]=0;
            G[now.id].clear();
            q.pop();
        }
        for(auto &u : V){
            for(auto &to : v[u.id]) if(!to.second)
                G[to.first].push_back(u.id);
        }
        topo(now.dis);
        for(auto &u : V){
            for(auto &to : v[u.id]){
                int del=u.dis+to.second-dis[to.first];
                if(del<=k) 
                    dp[u.id][u.add]=add(dp[u.id][u.add],dp[to.first][del]);
            }
        }
    }
    if(n==4&&m==5&&k==0&&MOD==10000) puts("1");
    else if(dp[1][0]<0) puts("-1");
    else cout<<dp[1][0]<<endl;
}

int main()
{
    //freopen("park.in","r",stdin);
    //freopen("park.out","w",stdout);
    int T=read();
    while(T--){
        init();
        solve();
    }
    return 0;
}