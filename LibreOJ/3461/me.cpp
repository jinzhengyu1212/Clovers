/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
#define y1 myyakak
#define y2 hcyakak
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
const int N=1005;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};//RLDU
int n,m,Q,mp[N][N][4]; 
pii belong[N][N];
char s[N][N];
void conD(int x,int y){mp[x][y][2]=1,mp[x+1][y][3]=1;}
void conR(int x,int y){mp[x][y][0]=1,mp[x][y+1][1]=1;}

int vis[N][N];
void dfs(int x,int y){
    vis[x][y]=1;
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(xx<0||yy<0||xx>n||yy>m||!mp[x][y][i]||vis[xx][yy]) continue;
        belong[xx][yy]=belong[x][y]; dfs(xx,yy);
    }
}
int hsum[N][N],ssum[N][N],csum[N][N];
int queryE(int x1,int y1,int x2,int y2){
    int ret1=hsum[x2][y2]-(x1==0 ? 0 : hsum[x1-1][y2])-hsum[x2][y1]
            +(x1==0 ? 0 : hsum[x1-1][y1]);
    int ret2=ssum[x2][y2]-(y1==0 ? 0 : ssum[x2][y1-1])-ssum[x1][y2]
            +(y1==0 ? 0 : ssum[x1][y1-1]);
    return ret1+ret2;
}
int queryC(int x1,int y1,int x2,int y2){
    return csum[x2][y2]-(x1==0 ? 0 : csum[x1-1][y2])-(y1==0 ? 0 : csum[x2][y1-1])
            +(x1==0||y1==0 ? 0 : csum[x1-1][y1-1]);
}

void init(){
    n=read(); m=read(); Q=read();
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=0;i<m;i++) conR(0,i),conR(n,i);
    for(int i=0;i<n;i++) conD(i,0),conD(i,m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(s[i][j]!=s[i+1][j]&&i!=n) conR(i,j-1);
            if(s[i][j]!=s[i][j+1]&&j!=m) conD(i-1,j);
        }
    }
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++) if(!vis[i][j]){
            belong[i][j]=mk(i,j);
            dfs(i,j);
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            hsum[i][j]=mp[i][j][1];
            hsum[i][j]+=(i==0 ? 0 : hsum[i-1][j])+(j==0 ? 0 : hsum[i][j-1])-(i==0||j==0 ? 0 : hsum[i-1][j-1]);
            ssum[i][j]=mp[i][j][3];
            ssum[i][j]+=(i==0 ? 0 : ssum[i-1][j])+(j==0 ? 0 : ssum[i][j-1])-(i==0||j==0 ? 0 : ssum[i-1][j-1]);
            csum[i][j]=(belong[i][j]==mk(i,j));
            csum[i][j]+=(i==0 ? 0 : csum[i-1][j])+(j==0 ? 0 : csum[i][j-1])-(i==0||j==0 ? 0 : csum[i-1][j-1]);
        }
    }
}

int idx(pii x){return x.first*(m+1)+x.second;}
int top=0;
namespace DSU{
    int fa[N*N],sz[N*N]; pii stk[200005];
    void init(){for(int i=0;i<(n+1)*(m+1);i++) fa[i]=i;}
    int getfather(int x){return x==fa[x] ? x : getfather(fa[x]);}
    void unite(int x,int y){
        x=getfather(x); y=getfather(y);
        if(x==y) return;
        if(sz[x]<sz[y]) swap(x,y);
        fa[y]=x; sz[x]+=sz[y]; stk[++top]=mk(x,y);
    }
    bool same(int x,int y){return getfather(x)==getfather(y);}
    void back(int pre){
        while(top!=pre){
            int x=stk[top].first,y=stk[top--].second;
            fa[y]=y; sz[x]-=sz[y];
        }
    }
}

vector<pii> used;
bool inside(int xx,int yy,int x1,int y1,int x2,int y2){return xx>=x1&&xx<=x2&&yy>=y1&&yy<=y2;}
void solve(int x1,int y1,int x2,int y2){
    int V=(x2-x1+1)*(y2-y1+1);
    int E=queryE(x1,y1,x2,y2);
    int C=queryC(x1,y1,x2,y2);
    used.clear();
    for(int i=y1;i<=y2;i++){
        if(i!=y2&&!mp[x1][i][0]){
            int xx=idx(belong[x1][i]),yy=idx(belong[x1][i+1]);
            if(!DSU::same(xx,yy)) C--,DSU::unite(xx,yy);
            E++;
        }
        pii now=belong[x1][i];
        if(!inside(now.first,now.second,x1,y1,x2,y2)){
            if(!vis[now.first][now.second]){
                C++; vis[now.first][now.second]=1;
                used.push_back(now);
            }
        }
        if(i!=y2&&!mp[x2][i][0]){
            int xx=idx(belong[x2][i]),yy=idx(belong[x2][i+1]);
            if(!DSU::same(xx,yy)) C--,DSU::unite(xx,yy);
            E++;
        }
        now=belong[x2][i];
        if(!inside(now.first,now.second,x1,y1,x2,y2)){
            if(!vis[now.first][now.second]){
                C++; vis[now.first][now.second]=1;
                used.push_back(now);
            }
        }
    }
    for(int i=x1;i<=x2;i++){
        if(i!=x2&&!mp[i][y1][2]){
            int xx=idx(belong[i][y1]),yy=idx(belong[i+1][y1]);
            if(!DSU::same(xx,yy)) C--,DSU::unite(xx,yy);
            E++;
        }
        pii now=belong[i][y1];
        if(!inside(now.first,now.second,x1,y1,x2,y2)){
            if(!vis[now.first][now.second]){
                C++; vis[now.first][now.second]=1;
                used.push_back(now);
            }
        }
        if(i!=x2&&!mp[i][y2][2]){
            int xx=idx(belong[i][y2]),yy=idx(belong[i+1][y2]);
            if(!DSU::same(xx,yy)) C--,DSU::unite(xx,yy);
            E++;
        }
        now=belong[i][y2];
        if(!inside(now.first,now.second,x1,y1,x2,y2)){
            if(!vis[now.first][now.second]){
                C++; vis[now.first][now.second]=1;
                used.push_back(now);
            }
        }
    }
    DSU::back(0);
    for(auto &u : used) vis[u.first][u.second]=0;
    printf("%d\n",E-V+C);
}

int main()
{
    init(); memset(vis,0,sizeof(vis));
    DSU::init();
    while(Q--){
        int x1=read(),y1=read(),x2=read(),y2=read();
        solve(x1-1,y1-1,x2,y2);
    }
    return 0;
}