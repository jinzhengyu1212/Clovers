#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,ll> pii;
#define mk make_pair
const int N=300005;
ll d[]={2,3,5};
ll n,cost[5];
int T,tot=0;
map<ll,int> mp;
vector<pii> v[N];

queue<ll> q;
ll t[N];
void init(){
    scanf("%lld",&n);
    for(int i=0;i<4;i++) scanf("%lld",&cost[i]);
    mp.clear();
    tot=0;
    mp[n]=++tot; t[tot]=n;
    while(!q.empty()) q.pop();
    q.push(n);
    while(!q.empty()){
        ll now=q.front(); int id=mp[now];
        q.pop();
        if(now==0) continue;
        for(int i=0;i<3;i++){
            ll to1=now/d[i];
            ll to2=now/d[i]+1;
            if(!mp[to1]){
                q.push(to1);
                mp[to1]=++tot; t[tot]=to1;
            }
            if(!mp[to2]){
                q.push(to2);
                mp[to2]=++tot; t[tot]=to2;
            }
            if(((now-to1*d[i])*cost[3]+(to1!=0)*cost[i])/cost[3]>now-to1){
                v[id].push_back(mk(mp[to1],(now-to1)*cost[3]));
            }
            else{
                v[id].push_back(mk(mp[to1],(now-to1*d[i])*cost[3]+(to1!=0)*cost[i]));
            }
            v[id].push_back(mk(mp[to2],(to2*d[i]-now)*cost[3]+cost[i]));
        }
    }
}

struct node{
    ll dis; int id;
    bool operator < (const node &rhs) const{
        return dis>rhs.dis;
    }
};

priority_queue<node> Q;
const ll inf=(ll)5e18;
ll dis[N],vis[N];
void dijkstra(){
    for(int i=1;i<=tot;i++) dis[i]=inf,vis[i]=0;
    dis[1]=0; while(!Q.empty()) Q.pop();
    Q.push({0,1});
    while(!Q.empty()){
        int u=Q.top().id; Q.pop();
        if(vis[u]) continue; vis[u]=1;
        for(int i=0;i<(int)v[u].size();i++){
            int to=v[u][i].first; ll w=v[u][i].second;
            if(vis[to]) continue;
            if(dis[u]+w<dis[to]){
                dis[to]=dis[u]+w;
                Q.push({dis[to],to});
            }
        }
    }
    printf("%lld\n",dis[mp[0]]);
    for(int i=1;i<=tot;i++) v[i].clear();
}

int main(){
    scanf("%d",&T);
    while(T--){
        init();
        dijkstra();
    }
    return 0;
}