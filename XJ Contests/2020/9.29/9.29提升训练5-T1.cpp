#include<bits/stdc++.h>
using namespace std;
const int N=500005;
typedef pair<int,int> pii;
#define mk make_pair
struct Edge{
    int from,to;
}E[N];
int fa[N],deg[N],tuan[N];
int vis[N];
vector<int> v[N];
int getfather(int x){
    return x==fa[x] ? x : fa[x]=getfather(fa[x]);
}
void unite(int x,int y){
    x=getfather(x); y=getfather(y);
    fa[x]=y; tuan[y]|=tuan[x];
}
bool same(int x,int y){return getfather(x)==getfather(y);}

int n,m;
queue<int> q;
vector<pii> ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) fa[i]=i,tuan[i]=0;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&E[i].from,&E[i].to);
        v[E[i].from].push_back(E[i].to);
        v[E[i].to].push_back(E[i].from);
        deg[E[i].from]++; deg[E[i].to]++;
        if(same(E[i].from,E[i].to)) tuan[getfather(E[i].from)]=1;
        else unite(E[i].from,E[i].to);
    }
    for(int i=1;i<=n;i++){
        if(deg[i]!=1) continue;
        if(!tuan[getfather(i)]) ans.push_back(mk(i,v[i][0]));
        else q.push(i);
    } 
    while(!q.empty()){
        int now=q.front(); q.pop(); vis[now]=1;
        for(int i=0;i<(int)v[now].size();i++){
            int to=v[now][i];
            deg[to]--; if(deg[to]==1) q.push(to);
        }
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            for(int j=0;j<(int)v[i].size();j++){
                int to=v[i][j];
                if(vis[to]) ans.push_back(mk(i,to));
            }
        }
    }
    sort(ans.begin(),ans.end());
    printf("%d\n",(int)ans.size());
    for(int i=0;i<(int)ans.size();i++){
        printf("%d %d\n",ans[i].first,ans[i].second);
    }
    return 0;
}