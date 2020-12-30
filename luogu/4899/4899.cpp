#include<bits/stdc++.h>
using namespace std;
const int inf=(int)1e9;
const int N=800005;
const int M=1600005;
int n,m,Q;
struct Edge{
    int from,to,cost;
    Edge(){} Edge(int from,int to,int cost):from(from),to(to),cost(cost){}
};
bool cmp2(Edge X,Edge Y){return X.cost<Y.cost;}
bool cmp1(Edge X,Edge Y){return X.cost>Y.cost;}
struct WereWolf{
    int father[N],cnt; vector<int> v[N];
    Edge E[N];
    int fa[N][20],dfn[N],out[N],id[N],val[N],dfn_clock;
    int getfather(int x){
        return father[x]==x ? x : father[x]=getfather(father[x]);
    }
    void unite(int x,int y){//y->x
        x=getfather(x); y=getfather(y);
        father[y]=x; v[x].push_back(y);
    }
    bool same(int x,int y){return getfather(x)==getfather(y);}
    void kruskal(){
        cnt=n;
        for(int i=1;i<=m;i++) if(!same(E[i].from,E[i].to)){
            cnt++; val[cnt]=E[i].cost;
            unite(cnt,E[i].from);
            unite(cnt,E[i].to);
        }
    }

    void dfs(int u){
        dfn[u]=++dfn_clock; id[dfn_clock]=u;
        for(int i=0;i<(int)v[u].size();i++){
            int to=v[u][i]; if(to==fa[u][0]) continue;
            fa[to][0]=u;
            for(int j=1;j<20;j++) fa[to][j]=fa[fa[to][j-1]][j-1];
            dfs(to);
        }
        out[u]=dfn_clock;
    }
    int find(int x,int limit,int flag){
        if(flag) val[0]=inf; else val[0]=-inf;
        if(!flag) for(int i=19;i>=0;i--) if(val[fa[x][i]]>=limit) x=fa[x][i];
        if(flag) for(int i=19;i>=0;i--) if(val[fa[x][i]]<=limit) x=fa[x][i];
        return x;
    }
    void init(){
        dfn_clock=0; memset(val,0,sizeof(val));
        for(int i=1;i<=n+n-1;i++) father[i]=i,v[i].clear();
        kruskal();
        memset(fa,0,sizeof(fa)); dfs(n+n-1);
    }
    void print(){
        for(int i=1;i<=n+n-1;i++){
            printf("val[%d]:%d\n",i,val[i]);
            for(int j=0;j<(int)v[i].size();j++) cout<<v[i][j]<<" "; cout<<endl;
        }
        for(int i=1;i<=n+n-1;i++) cout<<id[i]<<" "; cout<<endl;
    }
}man,wolf;

int tot=0;
struct Chairman_tree{
    int sum[N*30],ls[N*30],rs[N*30];
    void pushup(int x){sum[x]=sum[ls[x]]+sum[rs[x]];}
    void build(int x,int l,int r){
        sum[x]=0; if(l==r) return;
        int mid=(l+r)>>1;
        ls[x]=++tot; rs[x]=++tot;
        build(ls[x],l,mid); build(rs[x],mid+1,r);
        pushup(x);
    }
    void update(int x,int y,int l,int r,int pos){
        if(!pos){sum[x]=sum[y],ls[x]=ls[y],rs[x]=rs[y]; return;}
        if(l==r){sum[x]=sum[y]+1; return;}
        int mid=(l+r)>>1;
        if(mid>=pos) ls[x]=++tot,rs[x]=rs[y],update(ls[x],ls[y],l,mid,pos);
        else rs[x]=++tot,ls[x]=ls[y],update(rs[x],rs[y],mid+1,r,pos);
        pushup(x);
    }
    int query(int x,int y,int l,int r,int L,int R){
        if(L<=l&&r<=R) return sum[y]-sum[x];
        int mid=(l+r)>>1, ret=0;
        if(mid>=L) ret+=query(ls[x],ls[y],l,mid,L,R);
        if(mid<R) ret+=query(rs[x],rs[y],mid+1,r,L,R);
        return ret;
    }
}tree;

int pos[N];
void init()
{
    scanf("%d%d%d",&n,&m,&Q);
    for(int i=1;i<=m;i++){
        int x,y; scanf("%d%d",&x,&y); x++; y++;
        man.E[i]=Edge(x,y,min(x,y)); wolf.E[i]=Edge(x,y,max(x,y));
    }
    sort(man.E+1,man.E+m+1,cmp1); man.init();
    sort(wolf.E+1,wolf.E+m+1,cmp2); wolf.init();
    memset(pos,0,sizeof(pos));
    for(int i=1;i<=n+n-1;i++) 
        if(wolf.id[i]<=n) pos[wolf.id[i]]=i;
    tot=n+n-1; tree.build(0,1,n+n-1);
    for(int i=1;i<=n+n-1;i++){
        if(man.id[i]>n) tree.update(i,i-1,1,n+n-1,0);
        else tree.update(i,i-1,1,n+n-1,pos[man.id[i]]);
    }
}

//两个子树求判断相同元素，因为元素一一映射，所以把位置搞到平面上，二维数点即可
void solve()
{
    while(Q--){
        int S,T,L,R; scanf("%d%d%d%d",&S,&T,&L,&R);
        S++; T++; L++; R++;
        int man_root=man.find(S,L,0);
        int wolf_root=wolf.find(T,R,1);
        if(tree.query(man.dfn[man_root]-1,man.out[man_root],1,n+n-1,wolf.dfn[wolf_root],wolf.out[wolf_root])) puts("1");
        else puts("0");
    }
}

int main()
{
    init(); solve();
    return 0;
}