/*
the vast starry sky,
bright for those who chase the light.
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define mk make_pair
const int inf=(int)3e5;
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
const int N=100005;
int n,k;
vector<int> v[N];

int dp[N][2];
void dfs(int u){
    int bl=0;
    int delta=inf;
    for(auto &to : v[u]){
        dfs(to);
        dp[u][0]+=dp[to][1];
        if(dp[to][0]>=dp[to][1]){
            dp[u][1]+=dp[to][0];
            bl=1;
        }
        else dp[u][1]+=dp[to][1];
    }
    if(dp[u][0]<0) dp[u][0]=-inf;
    dp[u][1]+=bl;
    if(!sz(v[u])){
        dp[u][0]=0;
        dp[u][1]=-inf;
    }
    //out(u); out(dp[u][0]); outln(dp[u][1]);
}

void init(){
    n=read(); k=read();
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n;i++) v[i].clear();
    for(int i=2;i<=n;i++){
        int x=read();
        v[x].push_back(i);
    }
}

void solve(){
    dfs(1);
    int mi=dp[1][1];
    int L=min(mi,k/2);
    printf("%d\n",k-L);
}

int main()
{
    int T=read();
    while(T--){
        init();
        solve();
    }
    return 0;
}