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
//#define int long long
#define fi first
#define se second
const int N=8001;
const int M=1005;

int n,m,T,sx,sy,S;
int mp[M][M],Wall[M][M],cnt=0;
pii P[N]; int cir[N];
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
void Add_Wall(int x,int y){
    Wall[x][y]=-1;
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(xx>n||yy>m||xx<1||yy<1||Wall[xx][yy]) continue;
        Wall[xx][yy]=++cnt; P[cnt]=mk(xx,yy);
    }
}

vector<pii> v[N];
void build(int id){
    for(int i=0;i<4;i++){
        int nowx=P[id].fi,nowy=P[id].se,dis=0;
        while(Wall[nowx+dx[i]][nowy+dy[i]]!=-1){
            nowx+=dx[i],nowy+=dy[i];
            dis++;
        }
        if(dis){
            v[id].push_back(mk(Wall[nowx][nowy],dis));
            checkmax(cir[id],dis);
        }
    }
}

void init(){
    memset(Wall,0,sizeof(Wall));
    n=read(); m=read(); T=read();
    sx=read(); sy=read(); S=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            mp[i][j]=read();
            if(mp[i][j]) Wall[i][j]=-1;
        }
    }
    for(int i=1;i<=m;i++) Add_Wall(0,i),Add_Wall(n+1,i);
    for(int i=1;i<=n;i++) Add_Wall(i,0),Add_Wall(i,m+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) if(mp[i][j]) Add_Wall(i,j);
    }
    for(int i=1;i<=cnt;i++) build(i);
    if(!Wall[sx][sy]){
        Wall[sx][sy]=++cnt;
        P[cnt]=mk(sx,sy);
        build(cnt);
    }
}

ll dp[N][2005];
int best[N],pre[N][2005];
void run(){
    int st=Wall[sx][sy];
    memset(dp,0xcf,sizeof(dp));
    dp[st][0]=1;
    for(int s=0;s<2000;s++){
        int mx=0,id=0;
        for(int u=1;u<=cnt;u++){
            if(dp[u][s]<0) continue;
            if(dp[u][s]>mx) mx=dp[u][s],id=u;
            for(auto &to : v[u]){
                checkmax(dp[to.fi][s+1],dp[u][s]+to.se);
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        best[i]=0;
        pre[i][0]=0;
        for(int s=1;s<=2000;s++){
            if(dp[i][s]>dp[i][best[i]]+1ll*(s-best[i])*cir[i]){
                best[i]=s;
            }
            pre[i][s]=best[i];
        }
    }
}

void solve(int k){
    ll ans=0;
    for(int i=1;i<=cnt;i++){
        int ti=pre[i][min(k+1,2000)];
        ll tmp=1ll*(k-ti+1)*cir[i]+dp[i][ti];
        checkmax(ans,tmp);
    }   
    printf("%lld\n",ans);
}

signed main()
{
    init();
    run();
    while(T--){
        int k=read();
        solve(k);
    }
    return 0;
}