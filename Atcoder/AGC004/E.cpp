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
int add(int x,int y){x+=y; return x>=MOD ? x-MOD : x;}
int sub(int x,int y){x-=y; return x<0 ? x+MOD : x;}
#define mul(x,y) (ll)(x)*(y)%MOD
void Add(int &x,int y){x+=y; if(x>=MOD) x-=MOD;}
void Sub(int &x,int y){x-=y; if(x<0) x+=MOD;}
void Mul(int &x,int y){x=mul(x,y);}
int qpow(int x,int y){int ret=1; while(y){if(y&1) ret=mul(ret,x); x=mul(x,x); y>>=1;} return ret;}
void checkmin(short &x,short y){if(x>y) x=y;}
void checkmax(short &x,short y){if(x<y) x=y;}
void checkmin(int &x,int y){if(x>y) x=y;}
void checkmax(int &x,int y){if(x<y) x=y;}
#define out(x) cerr<<#x<<'='<<x<<' '
#define outln(x) cerr<<#x<<'='<<x<<endl
#define sz(x) (int)(x).size()
inline int read(){
    int x=0,f=1; char c=getchar();
    while(c>'9'||c<'0'){if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
const int N=101;
short dp[N][N][N][N];
int sx,sy,n,m,heng[N][N],shu[N][N];
char s[N][N];

void init(){
    n=read(); m=read();
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);
        for(int j=1;j<=m;j++){
            if(s[i][j]=='E') sx=i,sy=j;
            else if(s[i][j]=='o') heng[i][j]=1,shu[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) heng[i][j]+=heng[i][j-1];
    }
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++) shu[i][j]+=shu[i-1][j];
    }
}

struct node{
    short u,d,l,r;
    node(){}
    node(int u,int d,int l,int r):u(u),d(d),l(l),r(r){}
};
short ans=0;
queue<node> q;
void solve(){
    memset(dp,-1,sizeof(dp));
    dp[sx][sx][sy][sy]=0;
    q.push(node(sx,sx,sy,sy));
    while(!q.empty()){
        node now=q.front(); q.pop();
        short u=now.u,d=now.d,l=now.l,r=now.r;
        checkmax(ans,dp[u][d][l][r]);
        short liml=1+r-sy,limr=m-(sy-l);
        short limu=1+d-sx,limd=n-(sx-u);
        short R=min(r,limr),L=max(l,liml);
        short D=min(d,limd),U=max(u,limu);
        if(u-1>=limu){
            if(dp[u-1][d][l][r]==-1) q.push(node(u-1,d,l,r));
            checkmax(dp[u-1][d][l][r],dp[u][d][l][r]+heng[u-1][R]-heng[u-1][L-1]);
        }
        if(d+1<=limd){
            if(dp[u][d+1][l][r]==-1) q.push(node(u,d+1,l,r));
            checkmax(dp[u][d+1][l][r],dp[u][d][l][r]+heng[d+1][R]-heng[d+1][L-1]);
        }
        if(l-1>=liml){
            if(dp[u][d][l-1][r]==-1) q.push(node(u,d,l-1,r));
            checkmax(dp[u][d][l-1][r],dp[u][d][l][r]+shu[D][l-1]-shu[U-1][l-1]);
        }
        if(r+1<=limr){
            if(dp[u][d][l][r+1]==-1) q.push(node(u,d,l,r+1));
            checkmax(dp[u][d][l][r+1],dp[u][d][l][r]+shu[D][r+1]-shu[U-1][r+1]);
        }
    }
    cout<<ans<<endl;
}   

int main()
{
    init();
    solve();
    return 0;
}