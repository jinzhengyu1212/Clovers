#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int N=2005;
const int M=N*N;
const int inf=77777777;
typedef pair<int,int> pii;
#define mk make_pair
int TYP,n,m,w[N][N],ans[M],spe[M];
char mp[N][N];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int nowval=0;
int dep[M],fa[M];
//vector<pii> G[M];
int fst[M],nxt[M],point[M],iid[M],e=0;
void add_edge(int x,int y,int ID){
    e++;
    nxt[e]=fst[x];
    fst[x]=e;
    point[e]=y;
    iid[e]=ID;
}
//0:R 1:L 2:D 3:U
int dire(char c){
    if(c=='R') return 0;
    else if(c=='L') return 1;
    else if(c=='D') return 2;
    else return 3;
}
inline int read(){
    int f=1,x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    return x*f;
}
namespace DSU{
    int father[M],mx[M];
    void newnode(int x){father[x]=x; mx[x]=0; dep[x]=0;}
    void init(){for(int i=1;i<=n*m;i++) newnode(i);}
    int getfather(int x){
        if(x==father[x]) return x;
        int root=getfather(father[x]);
        if(root==x) return root;
        dep[x]+=dep[father[x]];
        return father[x]=root;
    }
    void unite(int x,int y)//y->x
    {
        int prex=x;
        x=getfather(x); y=getfather(y);
        father[y]=x;
        if(x==y) return;
        dep[y]=dep[prex]+1;
        mx[x]=max(mx[x],dep[y]+mx[y]);
        ans[mx[x]+spe[x]]=min(ans[mx[x]+spe[x]],nowval);
    }
    bool same(int x,int y){return getfather(x)==getfather(y);}
}
int idx(int x,int y){return (x-1)*m+y;}
int cnt=0;
struct Edge{
    int from,to,cost;
    Edge(){}
    Edge(int from,int to,int cost):from(from),to(to),cost(cost){}
    bool operator < (const Edge &rhs) const{
        return cost<rhs.cost;
    }
}E[M]; int bl[M];
    
void init(){
    scanf("%d",&TYP);
    n=read();m=read();
    for(int i=1;i<=1000000;i++) ans[i]=inf;
    DSU::init();
    for(int i=1;i<=n;i++) scanf("%s",mp[i]+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) w[i][j]=read(),ans[1]=min(ans[1],w[i][j]);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int dir=dire(mp[i][j]);
            int xx=i+dx[dir],yy=j+dy[dir];
            if(xx<1||yy<1||xx>n||yy>m){
                E[++cnt]=Edge(idx(i,j),idx(i,j),w[i][j]);
                continue;
            }
            E[++cnt]=Edge(idx(xx,yy),idx(i,j),w[i][j]);
            //the edge has been reversed
        }
    }
    sort(E+1,E+cnt+1);
}
    
int maxdep=0;
void myy_ak_ioi(int u,int f,int from){
    for(int i=fst[u];i;i=nxt[i]){
        int to=point[i];
        if(to==f||bl[iid[i]]) continue;
        DSU::father[to]=from;
        myy_ak_ioi(to,u,from);
    }
}
  
void hcy_ak_ioi(int u,int f,int from){
    maxdep=max(maxdep,dep[u]);
    for(int i=fst[u];i;i=nxt[i]){
        int to=point[i];
        if(to==f||bl[iid[i]]) continue;
        dep[to]=dep[u]+1; hcy_ak_ioi(to,u,from);
    }
}
    
vector<int> cir;
int incir[M];
void findcir(int x,int y){
    for(int i=0;i<(int)cir.size();i++) incir[cir[i]]=0;
    cir.clear();
    while(y!=x) incir[y]=1, cir.push_back(y), y=fa[y];
    cir.push_back(x);
}
    
int tot;
void processcir(){
    tot++; DSU::newnode(tot);
    for(int i=0;i<(int)cir.size();i++){
        int now=cir[i];
        for(int j=fst[now];j;j=nxt[j]){
            int to=point[j];
            if(incir[to]){
                bl[iid[j]]=1;
            }
        }
        cnt++;
        add_edge(tot,now,cnt);
        fa[now]=tot;
    }
    myy_ak_ioi(tot,-1,tot);
    spe[tot]=(int)cir.size()-1; maxdep=0;
    dep[tot]=0; hcy_ak_ioi(tot,-1,tot);
    DSU::mx[tot]=maxdep;
    ans[maxdep+spe[tot]]=min(ans[maxdep+spe[tot]],nowval);
}
   
void connect(int x,int y,int id){
    if(!DSU::same(x,y)){
        DSU::unite(x,y),fa[y]=x,add_edge(x,y,id);
    }
    else{
        swap(x,y);
        findcir(x,y);
        processcir();
    }
}
   
int Free[M]; vector<pii> used[M];
void solve(){
    for(int i=1;i<=n*m;++i) spe[i]=1;
    tot=n*m; int tmpcnt=cnt;
    for(int i=1;i<=tmpcnt;++i){
        nowval=E[i].cost;
        int x=E[i].from,y=E[i].to;
        if(x==y){
            Free[x]=1;
            for(int j=0;j<(int)used[x].size();++j) connect(x,used[x][j].first,used[x][j].second);
            continue;
        }
        Free[y]=1;
        for(int j=0;j<(int)used[y].size();++j) connect(y,used[y][j].first,used[y][j].second);
        used[y].clear();
        if(!Free[x]) used[x].push_back(mk(y,i));
        else connect(x,y,i);
    }
}
    
int T,A[M];
int main(){
    init(); solve();
    for(int i=999999;i>=0;i--) ans[i]=min(ans[i],ans[i+1]);
    T=read();
    for(int i=1;i<=T;++i) A[i]=read();
    for(int i=1;i<=T;++i) printf("%d ",ans[A[i]]);
    puts("");
    return 0;
}